// Problem: B2. Village (Maximum)
// Contest: Codeforces - Baltic Olympiad in Informatics 2020, Day 2 (IOI, Unofficial Mirror Contest, Unrated)
// URL: https://codeforces.com/contest/1387/problem/B2
// Memory Limit: 256 MB
// Time Limit: 750 ms
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

//WeakestTopology ORZ (From his solution to 342E) https://codeforces.com/contest/342/submission/90467624
//1-indexing
struct CentroidDecomposition
{
    const vector<vi>& E;
    vi par, subsz, level;
    vector<bool> vis;
    vector<vi> dist, subtrees;
    int cnt=1;
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
    void build(int u, int p, int c =0)
    {
        int sz = dfs(u, p, p == -1 ? -1 : level[p]);
        int centroid = find_centroid(u, p, sz);
        par[centroid] = p, vis[centroid] = 1;
        if (p != -1) level[centroid] = level[p] + 1, subtrees[c].pb(centroid);
        else subtrees[c].pb(centroid);
        for (auto v : E[centroid])
            if (!vis[v]) build(v, centroid, (p==-1? cnt++:c));
    }
    CentroidDecomposition(const vector<vector<int>>& E) : E(E)
    {
        int n = sz(E);
        par.assign(n, -1), subsz.assign(n, 0), vis.assign(n, 0);
        level.assign(n, 0), dist.assign(n, vector(31 - __builtin_clz(n), 0));
        subtrees.resize(n);
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
};



void solve()
{
	int n;
	cin >> n;
	vector<vi> g(n+1);
	vi subtree(n+1);
	for (int i=0;i<n-1;++i){
		int u,v;
		cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	CentroidDecomposition cd(g);
	dbg(cd.subtrees);
	ll res = 0;
	function<void(int,int)> dfs = [&](int v, int pv){
		subtree[v] = 1;
		for (int e:g[v]){
			if (e!=pv){ dfs(e,v); subtree[v] += subtree[e];}
		}
		for (int e:g[v]) if (e!=pv) res += 2*min(subtree[e],n-subtree[e]);
	};
	dfs(1,0);
	cout << res << endl;
	vi ans(n+1),s(n+1);
	bitset<100001> used;
	for (auto x:cd.subtrees){
		vi aug, tmp;
		for (int y:x){
			used[y] = 1;
			if (!ans[y]) aug.pb(y);
			else tmp.pb(y);
		}
		dbg(aug,tmp);
		int ptr = 0;
		for (int j=1;j<=n&&ptr<sz(tmp);++j){
			if (used[j]) continue;
			if (!ans[j]) ans[j] = tmp[ptr++];
		}
		ptr = 0;
		for (int j=1;j<=n&&ptr<sz(aug);++j){
			if (used[j]||used[ans[j]]) continue;
			if (ans[j]) ans[aug[ptr]]=ans[j],ans[j] = aug[ptr++];
			else if (!ans[j]) ans[j] = aug[ptr++];
		}
		for (int y:x){
			used[y] = 0;
		}
	}
	for (int i=1;i<=n;++i) s[ans[i]] = i;
	for (int i=1;i<=n;++i) cout << s[i]<<" ";
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