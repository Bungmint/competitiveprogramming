// Problem: C. Uncle Bogdan and Country Happiness
// Contest: Codeforces - Codeforces Round #660 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1388/C
// Memory Limit: 256 MB
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

void solve()
{
	int n, m;
	cin >> n>>m;
	vi a(n+1), h(n+1), subtree(n+1);
	vector<vi> g(n+1);
	FOR(i, 1, n+1) cin >> a[i];
	FOR(i, 1, n+1) cin >> h[i];
	F0R(i, n-1){
		int x, y;
		cin >> x >> y;
		g[x].pb(y), g[y].pb(x);
	}
	function<pii(int, int)> dfs = [&](int v, int pv)->pii{
		pii res = {0, 0};
		subtree[v] = a[v];
		for (auto u: g[v]){
			if (u!=pv){
				pii p = dfs(u, v);
				if (p.fi==-1){
					return {-1, -1};
				}
				subtree[v] += subtree[u];
				res.fi += p.fi, res.se += p.se;
			}
		}
		if (subtree[v]==a[v]){
			if (a[v]%2!=abs(h[v])%2) return {-1, -1};
			else if (a[v]<h[v]||h[v]<-a[v]) return {-1,-1};
			res.fi = (h[v]+a[v])/2, res.se = (a[v]-h[v])/2;
		}else{
			if (subtree[v]%2!=abs(h[v])%2) return {-1, -1};
			else if (subtree[v]<h[v]||h[v]<-subtree[v]) return {-1, -1};
			int g = (subtree[v]+h[v])/2, b = (subtree[v]-h[v])/2;
			if (g-res.fi>=0&&g-res.fi<=a[v]+res.se) res = {g, b};
			else return {-1, -1};
			
		}
		dbg(res);
		return res;
	};
	pii ans = dfs(1, 0);
	if (ans.fi!=-1) cout << "YES"<<"\n";
	else cout << "NO\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    cin >> testcase;
    for (int i=0;i<testcase;++i)
    {
        solve();
    }
}