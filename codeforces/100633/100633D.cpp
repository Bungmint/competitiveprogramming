// Problem: D. LWDB
// Contest: Codeforces - 2015 ICL, Finals, Div. 1
// URL: https://codeforces.com/gym/100633/problem/D
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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
    const vector<vpi>& E;
    vi par, subsz, level;
    vector<int> vis;
    vector<vi> dist, child;
    int dfs(int u, int p, int h, int W)
    {
        if (h != -1) dist[u][h] = dist[p][h] + W;
        subsz[u] = 1;
        for (auto [v, w] : E[u])
            if (!vis[v] && v != p) subsz[u] += dfs(v, u, h, w);
        return subsz[u];
    }
    int find_centroid(int u, int p, int sz)
    {
        for (auto [v,w] : E[u])
            if (!vis[v] && v != p && subsz[v]*2 > sz)
                return find_centroid(v, u, sz);
        return u;
    }
    void build(int u, int p, int w = 0)
    {
        int sz = dfs(u, p, p == -1 ? -1 : level[p], w);
        int centroid = find_centroid(u, p, sz);
        par[centroid] = p, vis[centroid] = 1;
        if (p!=-1)child[p].pb(centroid);
        
        if (p != -1) level[centroid] = level[p] + 1;
        for (auto [v,w] : E[centroid])
            if (!vis[v]) build(v, centroid, w);
    }
    CentroidDecomposition(const vector<vpi>& E) : E(E)
    {
        int n = sz(E);
        par.assign(n, -1LL), subsz.assign(n, 0LL), vis.assign(n, 0LL);
        level.assign(n, 0LL), dist.assign(n, vector(31 - __builtin_clz(n), 0));
        child.resize(n);
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
    	if (u==v) return 0;
        int w = lca(u, v);
        return dist[u][level[w]] + dist[v][level[w]];
    }
};

struct Query{
	vector<ar<int,3>> vec;
};

void solve()
{
	int n;
	cin >> n;
	vector<vpi> g(n+1);
	for (int i=0;i<n-1;++i){
		int u,v, w;
		cin >> u >> v >> w;
		g[u].pb({v,w}), g[v].pb({u,w});
	}
	CentroidDecomposition cd(g);
	vector<Query> ans(n+1);
	function<void(int, int, int, int)> pop = [&](int v, int d, int c, int time){
		while(!ans[v].vec.empty()&&ans[v].vec.back()[0]<=d){
			ans[v].vec.pop_back();
		}
		ans[v].vec.pb({d,c,time});
	};
	function<pi(int,int)> search = [&](int d, int u){
		pi p = {-1,0};
		int l = 0, r = sz(ans[u].vec)-1;
		while(l<=r){
			int m = l + (r-l)/2;
			if (ans[u].vec[m][0]>=d){
				l = m+1, p.fi = ans[u].vec[m][2], p.se = ans[u].vec[m][1];
			}else r = m-1;
		}
		return p;
	};
	
	auto upd = [&](int v, int d, int c, int time){
		pop(v, d,c, time);
		for (int u = cd[v];u!=-1;u=cd[u]){
			pop(u, d-cd.distance(u,v),c, time);
		}
	};
	auto query = [&](int v){
		pi p;
		p = search(0, v);
		for (int u=cd[v];u!=-1;u=cd[u]){
			pi tmp = search(cd.distance(u,v), u);
			if (ckmax(p.fi, tmp.fi)){
				p = tmp;
			}
		}
		return p.se;
	};
	int q;
	cin >> q;
	for (int i=0;i<q;++i){
		int op, v;
		cin >> op>> v;
		if (op==1){
			int d, c;
			cin >> d >> c;
			upd(v,d, c,i);
		}else{
			cout << query(v)<<"\n";
		}
	}
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