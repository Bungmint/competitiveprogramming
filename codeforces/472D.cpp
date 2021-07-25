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

template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
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

struct custom_hash
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
vpi g[2001];
ll d[2001];

// From the USACO tutorial lol
struct DSU {
	vector<int> e;
	vector<int> mem;
	vector<pair<pi,pi>> ev;
	DSU(int N) { e = vector<int>(N, -1); }

	// get representive component (uses path compression)
	// To use rollback, disable path compression
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	
	bool same_set(int a, int b) { return get(a) == get(b); }
	
	int size(int x) { return -e[get(x)]; }
	
	bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return false;
		ev.pb({{x, e[x]}, {y,e[y]}});
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
		return true;
	}
	
	void snapshot(){
		mem.pb(sz(ev));
	}
	
	void rollback(){
		if (mem.empty())return;
		int SZ = mem.back();
		mem.pop_back();
		while(sz(ev)!=SZ){
			pair<pi,pi> p = ev.back();
			e[p.fi.fi] = p.fi.se;
			e[p.se.fi] = p.se.se;
			ev.pop_back();
		}
	}
};

void dfs(int v, int pV){
	for (auto [e,w]:g[v]){
		if (e!=pV){
			d[e] = w+d[v];
			dfs(e,v);
		}
	}
}

void solve()
{
	int n;
	cin >> n;
	vector<vi> grid(n+1, vi(n+1));
	for (int i=1;i<=n;++i) for (int j=1;j<=n;++j){
		cin >> grid[i][j];
	}
	bool ok = 1;
	for (int i=1;i<=n;++i){
		if (grid[i][i]) ok = 0;
	}
	for (int i=1;i<=n;++i) for (int j=1;j<=n;++j) if (grid[i][j]!=grid[j][i]) ok = 0;
	if (!ok){
		cout << "NO\n";
		return;
	}
	DSU dsu(n+1);
	vector<pair<int,pi>> Edge;
	for (int i=1;i<=n;++i) for (int j=i+1;j<=n;++j) Edge.pb({ grid[i][j], {i,j}});
	sort(all(Edge));
	for (int i=0;i<sz(Edge);++i){
		int u = Edge[i].se.fi, v = Edge[i].se.se;
		int w = Edge[i].fi;
		if (!dsu.same_set(u,v)){
			dsu.unite(u,v);
			if (!w) ok = 0;
			g[u].pb({v,w});
			g[v].pb({u,w});
		}
	}
	for (int i=1;i<=n;++i){
		memset(d, 0, sizeof(d));
		dfs(i,0);
		for (int j=1;j<=n;++j){
			if (d[j]!=grid[i][j]) ok = 0;
		}
	}
	cout << (ok? "YES":"NO")<<"\n";
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