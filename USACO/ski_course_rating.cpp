// Problem: Problem 3. Ski Course Rating
// Contest: USACO - USACO 2014 January Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=384
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// #pragma GCC optimize("O3")
// #pragma GCC target("sse4")
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
//D&C with DSU with rollback 
//Essentially, multisource binary search

const int MX = 500;
int grid[MX][MX];
int n, m, t;

int conv(int x, int y){
	return m*x + y;
}
pii conv(int x){
	return {x/m, x%m};
}

// From the USACO tutorial lol
struct DSU {
	vector<int> e;
	vector<int> mem;
	vector<pair<pii,pii>> ev;
	DSU(int N) { e = vector<int>(N, -1); }

	// get representive component (uses path compression)
	// To use rollback, disable path compression
	int get(int x) { return e[x] < 0 ? x : get(e[x]); }
	
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
			pair<pii,pii> p = ev.back();
			e[p.fi.fi] = p.fi.se;
			e[p.se.fi] = p.se.se;
			ev.pop_back();
		}
	}
};

struct Edge{
	int u, v, w;
	bool operator<(const Edge& other) const{
		return w<other.w;
	}
};

bool good(int x, int y){
	return x>=0&&x<n&&y>=0&&y<m;
}

int lower_bound(vector<Edge>& edges, int w){
	int l = 0, r = sz(edges)-1, ans = 0;
	if (edges[r].w<w) return r+1;
	while(l<=r){
		int mid = l + (r-l)/2;
		if (edges[mid].w>=w){
			ans = mid, r = mid-1;
		}else l = mid +1;
	}
	return ans;
}

void divide_conquer(int l, int r,vector<Edge>& edges, vpi&point, vi&ans, DSU& dsu){
	if (r==l+1){
		for (auto [x, id]:point){
			ans[id] = l;
		}
		return;
	}
	if (!sz(point)) return;
	int mid = (l+r)>>1;
	int L = lb(edges, l), R =lb(edges, mid);
	vpi a, b;
	dsu.snapshot();
	FOR(i, L, R){
		auto [u,v, w]= edges[i];
		dsu.unite(u, v);
	}
	F0R(i, sz(point)){
		if (dsu.size(point[i].fi)>=t){
			a.pb(point[i]);
		}else b.pb(point[i]);
	}
	dbg(l, mid, r, a, b);
	divide_conquer(mid, r, edges,b, ans, dsu);
	dsu.rollback();
	divide_conquer(l, mid, edges,a, ans, dsu);
}



void solve()
{
	cin >>n >> m >> t;
	F0R(i, n)F0R(j, m){
		cin >> grid[i][j];
	}
	vector<Edge> edges;
	F0R(x, n)F0R(y, m){
		F0R(k, 2){
			int nx = x + dx[k], ny = y + dy[k];
			if (good(nx, ny)){
				edges.pb({conv(x, y), conv(nx, ny), abs(grid[x][y]-grid[nx][ny])});
			}
		}
	}
	sort(all(edges));
	vpi point;
	F0R(i, n)F0R(j, m){
		int tt;
		cin >> tt;
		if (tt) point.emplace_back(conv(i, j), sz(point));
	}
	DSU dsu(n*m);
	vi ans(sz(point));
	divide_conquer(0, (int)(1e9+1),edges, point,ans, dsu);
	ll res = 0;
	F0R(i, sz(ans)) res += ans[i];
	cout << res << endl;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    #ifndef LOCAL
    	setIO("skilevel");
    #endif
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}