// Problem: Problem 3. Build Gates
// Contest: USACO - USACO 2016 January Contest, Silver
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=596
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2021 Youngmin Park. All rights reserved.
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
using ld = long double;

#define all(v) (v).begin(), (v).end()
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define REP(a) F0R(_, a)

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v)
{
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}
void dbg_out()
{
    cerr << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

struct chash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
    size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

bool vis[2010][2010];
set<ar<int,4>> fence;
int minX = 0, maxX = 0, minY = 0, maxY = 0;

void dfs(int i, int j){
	if (i<minX||j<minY||i>=maxX||j>=maxY)return;
	if (vis[i-minX][j-minY]) return;
	vis[i-minX][j-minY] = 1;
	F0R(k, 4){
		int ni = i + dx[k], nj = j + dy[k];
		if (ni<minX||nj<minY||ni>=maxX||nj>=maxY) continue;
		if (ni==i){
			int maxj = max(j, nj);
			if (!fence.count({i, maxj, i+1, maxj})) dfs(ni, nj);
		}else{
			int maxi = max(i, ni);
			if (!fence.count({maxi, j, maxi, j+1})) dfs(ni, nj);
		}
	}
}

void solve()
{
	int n;
	cin >> n;
	string s;
	cin >> s;
	map<char,int> mp = {{'E', 0}, {'N', 1}, {'W', 2}, {'S', 3}};
	int cX = 0, cY = 0;
	for (auto&c:s){
		int ncX = cX + dx[mp[c]], ncY = cY + dy[mp[c]];
		ckmax(maxX, ncX), ckmax(maxY, ncY);
		ckmin(minX, ncX), ckmin(minY, ncY);
		fence.insert({cX, cY, ncX, ncY});
		fence.insert({ncX, ncY, cX, cY});
		swap(cX, ncX), swap(cY, ncY);
	}
	int cnt = 0;
	dbg(minX, maxX, minY, maxY);
	minX-=1, maxX+=1, minY-=1, maxY+=1;
	FOR(r, minX, maxX){
		FOR(c, minY, maxY){
			if (!vis[r-minX][c-minY]){
				cnt++;
				dfs(r, c);
			}
		}	
	}
	cout << cnt-1;
	
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    #ifndef LOCAL
    	setIO("gates");
    #endif
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}