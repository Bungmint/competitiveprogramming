// Problem: Coin Collector
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1686
// Memory Limit: 512 MB
// Time Limit: 1000 ms
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

const int N=1e5+1;
vi order, comp, g[N], revg[N];
bool vis1[N], vis2[N];
int root[N];
vi condense[N];
ll a[N], sum[N], dp[N];

void dfs1(int v){
	vis1[v] = 1;
	for (int e:g[v]) if (!vis1[e]) dfs1(e);
	order.pb(v);
}
void dfs2(int v){
	vis2[v] = 1;
	comp.pb(v);
	for (int e:revg[v]) if (!vis2[e]) dfs2(e);
}
void dfs3(int v){
	vis1[v] = 1;
	for (int e:condense[v]) if (!vis1[e]) dfs3(e);
	order.pb(v);
}

void solve()
{
	int n, m;
	cin >>n >>m;
	for (int i=1;i<=n;++i) cin >> a[i];
	for (int i=0;i<m;++i){
		int u,v;
		cin >> u >> v;
		g[u].pb(v);
		revg[v].pb(u);
	}
	for (int i=1;i<=n;++i){
		if (!vis1[i]) dfs1(i);
	}
	reverse(all(order));
	int cnt=1;
	for (int x:order){
		comp.clear();
		if (!vis2[x]){
			dfs2(x);
			root[x] = cnt;
			for (int y:comp) root[y] =root[x], sum[root[x]]+=a[y];
			cnt++;
			dbg(sum[root[x]], comp);
		}
	}
	cnt--;
	for (int i=1;i<=n;++i){
		for (int e:g[i]){
			int x = root[i], y = root[e];
			if (x!=y) condense[x].pb(y);
		}
	}
	order.clear();
	memset(vis1, 0, sizeof(vis1));
	dbg(cnt);
	for (int i=1;i<=cnt;++i){
		dp[i] = sum[i];
		if (!vis1[i]) dfs3(i);
	}
	reverse(all(order));
	ll res = 0;
	for (int x:order){
		dbg(x);
		for (int e:condense[x]){
			dbg(x,e);
			dbg(dp[e], dp[x], sum[e]);
			ckmax(dp[e], dp[x]+sum[e]);
		}
		ckmax(res, dp[x]);
	}
	cout << res << endl;
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