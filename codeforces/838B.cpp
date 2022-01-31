// Problem: B. Diverging Directions
// Contest: Codeforces - IndiaHacks 2nd Elimination 2017 (unofficial, unrated mirror, ICPC rules)
// URL: https://codeforces.com/contest/838/problem/B
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

template<typename T, typename S>
struct LazySegTree{
	const T seg_initial = 0;
	const S seg_lazy_sentinel = 0;
	const T NEUTRAL = LINF;
	int sz;
	vector<T> t;
	vector<S> lazy;
	
	
	// Change the inline function accordingly to the q
	inline T merge(T a, T b){
		return min(a,b);
	}
	inline S lazy_apply(S lazy_val, S new_val){
		return new_val+lazy_val;
	}
	inline T lazy_func(T cur_val, S lazy_val, ll l, ll r){
		return lazy_val+cur_val;
	}
	
	
	void init(int n){
		sz = 1;
		while(sz<n) sz*=2;
		t.assign(2*sz, seg_initial);
		lazy.assign(2*sz, seg_lazy_sentinel);
	}
	void seg_eval_lazy(int i, ll l, ll r)
	{
	    if (lazy[i] == seg_lazy_sentinel)
	        return;
	
	    t[i] = lazy_func(t[i], lazy[i], l, r);
	
	    if (r-l>1)
	    {
	        lazy[i * 2 + 1] = lazy_apply(lazy[i * 2 + 1], lazy[i]);
	       	lazy[i * 2 + 2] = lazy_apply(lazy[i * 2 + 2], lazy[i]);
	    }
	
	    lazy[i] = seg_lazy_sentinel;
	}
	T upd(int x, int l, int r, int lx, int rx, S v)
	{
		seg_eval_lazy(x, lx, rx);
		if (lx>=r||rx<=l) return t[x];
		if (lx>=l&&rx<=r){
			lazy[x] = lazy_apply(lazy[x],v);
			seg_eval_lazy(x, lx ,rx);
			return t[x];
		}
		if (rx-lx==1) return t[x];
	    
	    int mid = (lx + rx) / 2;
	    T a = upd(2*x+1, l, r, lx, mid, v);
	    T b = upd(2*x+2, l, r, mid, rx, v);
	   	return t[x] = merge(a, b);
	}
	void upd(int l, int r, S v)
	{
	    upd(0, l, r, 0, sz, v);
	}
	T query(int l, int r, int x, int lx, int rx)
	{
		seg_eval_lazy(x, lx, rx);
	    if (lx >= r || rx <= l)
	        return NEUTRAL;
	    if (lx >= l && rx <= r)
	        return t[x];
	    int mid = (lx + rx) / 2;
	    T a = query(l, r, 2 * x + 1, lx, mid);
	    T b = query(l, r, 2 * x + 2, mid, rx);
	    return merge(a, b);
	}
	T query(int l, int r)
	{
	    return query(l, r, 0, 0, sz);
	}
};

const int N=2e5+1;
vi g[N];
int tin[N], tout[N], ver[N], timer = 0;
void dfs(int v, int pv){
	tin[v] = timer++, ver[tin[v]] = v;
	for (int e:g[v]){
		if (e!=pv){
			dfs(e,v);
		}
	}
	tout[v] = timer;
}
bool isAnc(int a, int b){// check if a is an ancestor of b
	return tin[a]<=tin[b]&&tout[b]<=tout[a];
}
struct Edge{
	int u, v, w;
};

void solve()
{
	int n, q;
	cin >> n >> q;
	vector<Edge> edges(2*n-2);
	F0R(i, 2*n-2){
		int u, v, w;
		cin >> u >> v >> w;
		edges[i] = {u,v,w};
		if (i<n-1) g[u].pb(v), g[v].pb(u);
	}
	dfs(1,0);
	LazySegTree<ll,ll>st, ST;
	st.init(n+1), ST.init(n+1);
	F0R(i, 2*n-2){
		auto &[u, v, w] = edges[i];
		if (i<n-1){
			if (tin[u]>tin[v]) swap(u, v);
			st.upd(tin[v], tout[v], w);
			ST.upd(tin[v], tout[v], w);
		}else{
			st.upd(tin[u], tin[u]+1, w);
		}
	}
	while(q--){
		int t;
		cin >> t;
		if (t==1){
			int i, W;
			cin >> i >> W;
			i--;
			auto &[u, v, w] = edges[i];
			if (i<n-1){
				st.upd(tin[v], tout[v], W-w);
				ST.upd(tin[v], tout[v], W-w);
				w = W;
			}else{
				st.upd(tin[u], tin[u]+1, W-w);
				w = W;
			}
		}else{
			int u, v;
			cin >> u >> v;
			int distU = ST.query(tin[u], tin[u]+1);
			int distV = ST.query(tin[v], tin[v]+1);
			if (u==v){
				cout << 0 << "\n";
			}else if (isAnc(u, v)){
				cout << distV-distU << "\n";
			}else{
				cout << st.query(tin[u], tout[u])-distU+distV<<"\n";
			}
		}
	}
	
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