// Problem: D. Book of Evil
// Contest: Codeforces - Codeforces Round #196 (Div. 2)
// URL: https://codeforces.com/contest/337/problem/D
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
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;
using pl = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pl>;
using ld = long double;

#define all(v) (v).begin(), (v).end()
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound

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
#define dbg(...)
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
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

void solve()
{
	int n, m, d;
	cin >> n >> m >> d;
	vector<vi> g(n+1);
	vector<bool> mark(n+1, false);
	vi up(n+1, -1), down(n+1, -1), id(n+1);
	vector<vi> l(n+1), r(n+1);
	for (int i=1;i<=m;++i){int t;cin >> t;mark[t]=1;}
	for (int i=1;i<=n-1;++i){
		int u,v;
		cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	function<void(int,int)> dfs1 = [&](int u, int pu){
		vi c;
		down[u] = (mark[u]? 0: -1);
		for (int v:g[u]){
			if (v!=pu){dfs1(v,u), c.pb(v); if(down[v]>=0) ckmax(down[u], down[v]+1);}
		}
		dbg(c);
		l[u].assign(sz(c), -1), r[u].assign(sz(c), -1);
		dbg(l[u], r[u]);
		for (int i=0;i<sz(c);++i){
			int child = c[i];
			id[child] = i;
			if (i) l[u][i] = l[u][i-1];
			if (down[child]>=0) ckmax(l[u][i], down[child]);
		}
		for (int i=sz(c)-1;i>=0;--i){
			int child = c[i];
			if (i+1<sz(c)) r[u][i] = r[u][i+1];
			if (down[child]>=0) ckmax(r[u][i], down[child]);
		}
		
	};
	function<void(int,int)> dfs2 = [&](int u, int pu){
		up[u] = -1;
		if (pu&&up[pu]>=0) ckmax(up[u], up[pu]+1);
		if (mark[pu]) ckmax(up[u], 1);
		if (pu){
			int k = id[u];
			dbg(u, k, up[u]);
			if (k&&l[pu][k-1]>=0) ckmax(up[u], l[pu][k-1]+2);
			if (k+1<sz(r[pu])&&r[pu][k+1]>=0) ckmax(up[u], r[pu][k+1]+2);
		}
		for (int v:g[u]){
			if (v!=pu)dfs2(v,u);
		}
	};
	dfs1(1,0);
	dfs2(1,0);
	int ans = 0;
	for (int i=1;i<=n;++i){
		dbg(up[i], down[i]);
		if (up[i]<=d&&down[i]<=d) ans++;
	}
	cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}