// Problem: E - Moat
// Contest: AtCoder - Sciseed Programming Contest 2021（AtCoder Beginner Contest 219）
// URL: https://atcoder.jp/contests/abc219/tasks/abc219_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
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
int a[16];
int dp[1<<16];

bool good(int x, int y){
	return x<4&&y<4&&x>=0&&y>=0;
}

bool good(int mask){
	set<int> b;
	F0R(i, 16){
		if (mask&(1<<i)) b.insert(i);
	}
	if (!sz(b)) return 0;
	bool vis[16] = {};
	queue<int> q;
	vis[*b.begin()] =1;
	q.push(*b.begin());
	int cnt = 0;
	while(sz(q)){
		int v =q.front(); q.pop();
		cnt++;
		int c = v%4, r = v/4;
		F0R(i, 4){
			int nr = r + dx[i], nc = c + dy[i];
			if (good(nr, nc)&&!vis[nr*4+nc]&&b.count(nr*4+nc)){
				q.push(nr*4+nc);
				vis[nr*4+nc] = 1;
			}
		}
	}
	if (cnt!=sz(b)) return 0;
	F0R(i, 16){
		if (mask&(1<<i)) continue;
		int r = i/4, c = i%4;
		if (r==0||r==3||c==0||c==3) q.push(i), vis[i] = 1;
	}
	while(sz(q)){
		int v =q.front(); q.pop();
		int c = v%4, r = v/4;
		F0R(i, 4){
			int nr = r + dx[i], nc = c + dy[i];
			if (good(nr, nc)&&!vis[nr*4+nc]){
				q.push(nr*4+nc);
				vis[nr*4+nc] = 1;
			}
		}
	}
	F0R(i, 16){
		if (!(mask&(1<<i))&&!vis[i]){
			return 0;
		}
	}
	return 1;
}

void solve()
{
	ll ans = 0;
	F0R(i, 16)cin >> a[i], ans += a[i]*(1<<i);
	FOR(mask, 1, 1<<16){
		if (good(mask)){
			for (int s = mask; s; s= (s-1)&mask){
				dp[s]++;
			}
		}
	}
	cout << dp[ans]<<"\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}