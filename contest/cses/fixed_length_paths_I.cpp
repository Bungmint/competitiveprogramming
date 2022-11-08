// Problem: Fixed-Length Paths I
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/2080
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

int k;

//WeakestTopology ORZ (From his solution to 342E) https://codeforces.com/contest/342/submission/90467624
//1-indexing
struct CentroidDecomposition
{
    const vector<vi>& E;
    vi par, subsz, level, cnt;
    vector<bool> vis;
    vector<vi> dist;
    ll ans = 0;
    int mxdepth;
    int dfs(int u, int p, int h)
    {
        if (h != -1) dist[u][h] = dist[p][h] + 1;
        subsz[u] = 1;
        for (auto v : E[u])
            if (!vis[v] && v != p) subsz[u] += dfs(v, u, h);
        return subsz[u];
    }
    int find_centroid(int u, int p, int sz)
    {
        for (auto v : E[u])
            if (!vis[v] && v != p && subsz[v]*2 > sz)
                return find_centroid(v, u, sz);
        return u;
    }
    void get_cnt(int u, int pu, bool filling, int depth=1){
    	if (depth>k) return;
    	ckmax(mxdepth, depth);
    	if (filling) cnt[depth]++;
    	else ans += cnt[k-depth];
    	for (int c:E[u]){
    		if (c!=pu&&!vis[c]) get_cnt(c, u, filling, depth+1);
    	}
    }
    void build(int u, int p)
    {
        int sz = dfs(u, p, p == -1 ? -1 : level[p]);
        int centroid = find_centroid(u, p, sz);
        par[centroid] = p, vis[centroid] = 1;
        if (p != -1) level[centroid] = level[p] + 1;
        mxdepth=0;
        cnt[0] = 1;
        for (auto v: E[centroid]){
        	if (!vis[v]) {
        		get_cnt(v, centroid, false);
        		get_cnt(v,centroid, true); 
        	}
        }
        fill(cnt.begin()+1, cnt.begin()+mxdepth+1,0);
        for (auto v : E[centroid])
            if (!vis[v]) build(v, centroid);
    }
    CentroidDecomposition(const vector<vector<int>>& E) : E(E)
    {
        int n = sz(E);
        par.assign(n, -1), subsz.assign(n, 0), vis.assign(n, 0);
        level.assign(n, 0), dist.assign(n, vector(31 - __builtin_clz(n), 0));
        cnt.assign(n, 0);
        build(1, -1);
    }
    int operator[](int u) const { return par[u]; }
    int lca(int u, int v) // centroid lca, not tree lca
    {
        if (level[u] < level[v]) swap(u, v);
        while (level[u] > level[v]) u = par[u];
        while (u != v) u = par[u], v = par[v];
        return u;
    }
    int distance(int u, int v)
    {
        int w = lca(u, v);
        return dist[u][level[w]] + dist[v][level[w]];
    }
    inline int ancDist(int u, int v){ // v is the ancestor
    	return dist[u][level[v]];
    }
};


void solve()
{
	int n;
	cin >> n >>k;
	vector<vi> g(n+1);
	for (int i=0;i<n-1;++i){int u,v;cin >> u >> v;g[u].pb(v), g[v].pb(u);}
	CentroidDecomposition cd(g);
	cout << cd.ans << endl;
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