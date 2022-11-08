// Problem: Problem 3. Multiplayer Moo
// Contest: USACO - USACO 2018 US Open Contest, Silver
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=836
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2021 Youngmin Park. All rights reserved.
// #pragma GCC optimize("O3")
// #pragma GCC target("avx2")
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

const int MN = 250;
int n, cc, grid[MN][MN], component[MN][MN], cnt;
vi nodeSZ;
bool vis[MN][MN];
map<pii, map<int,vi>> g;
int ans1, ans2;

bool good(int r, int c){
	return !(r<0||c<0||r>=n||c>=n);
}

void dfsInit(int r, int c, int val, int comp){
	if (!good(r, c)) return;
	if (vis[r][c]||grid[r][c]!=val) return;
	vis[r][c] = 1, component[r][c] = comp;
	cnt++;
	for (int i=0;i<4;i++){
		int nr = r + dx[i], nc = c + dy[i];
		dfsInit(nr, nc, val, comp);
	}
}

void solve()
{
	cin >> n;
	for (int i=0;i<n;i++) for (int j=0;j<n;j++){
		cin >> grid[i][j];
	}
	for (int i=0;i<n;i++) for (int j=0;j<n;j++){
		if (vis[i][j]) continue;
		cnt = 0;
		dfsInit(i, j, grid[i][j], cc++);
		nodeSZ.pb(cnt);
		ckmax(ans1, cnt);
	}
	for (int i=0;i<n;i++) for (int j=0;j<n;j++){
		for (int k=0;k<4;k++){
			int ni = i + dx[k], nj = j + dy[k];
			if (good(ni, nj)&&component[i][j]!=component[ni][nj]){
				int mi = min(grid[i][j], grid[ni][nj]);
				int mx = max(grid[i][j], grid[ni][nj]);
				g[make_pair(mi, mx)][component[i][j]].pb(component[ni][nj]);
				g[make_pair(mi, mx)][component[ni][nj]].pb(component[i][j]);
			}
		}
	}
	for (auto&e:g){
		auto mp = e.se;
		set<int> vvv;
		int cur = 0;
		function<void(int)> dfs = [&](int u){
			vvv.insert(u);
			cur += nodeSZ[u];
			for (auto&v:mp[u]){
				if (!vvv.count(v)) dfs(v);
			}
		};
		for (auto&[v, adj]:mp){
			if (vvv.count(v)) continue;
			cur = 0;
			dfs(v);
			ckmax(ans2, cur);
		}
	}
	cout << ans1 << endl;
	cout << ans2 << endl;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    #ifndef LOCAL
    	setIO("multimoo");
    #endif
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}