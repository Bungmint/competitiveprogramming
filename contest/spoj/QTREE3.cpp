// Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
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
template <typename T, size_t SZ>
using ar = array<T, SZ>;
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

#define all(v) (v).begin(), (v).end()
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound

constexpr int INF = 1e9;
constexpr ll LINF = 1e18;
const ld PI = acos((ld)-1.0);
constexpr int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
constexpr bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
constexpr bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

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
template <typename T>
ostream &operator<<(ostream &os, const deque<T> &v) {
	os << vector<T>(all(v));
	return os;
}
template <typename T, typename S, typename C>
ostream &operator<<(ostream &os, priority_queue<T, S, C> pq) {
	vector<T> v;
	while (sz(pq)) {
		v.pb(pq.top());
		pq.pop();
	}
	os << v;
	return os;
}
void dbg_out()
{
	cerr << "\033[0m" << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
	cerr << ' ' << H;
	dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "\033[1;35m" << __func__ << ':' << __LINE__ << " (" << #__VA_ARGS__ << "):\033[33m", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif


inline namespace Range {
	class ForwardRange {
		int src, dst;

	  public:
	  	explicit constexpr ForwardRange(const int l, const int r) : src(l), dst(r) {}
		explicit constexpr ForwardRange(const int n) : src(0), dst(n) {}
		constexpr ForwardRange begin() const { return *this; }
		constexpr ForwardRange end() const { return *this; }
		constexpr bool operator!=(ForwardRange) const { return src < dst; }
		constexpr void operator++() const {}
		constexpr int operator*() { return src++; }
	};
	class BackwardRange {
		int src, dst;

	  public:
	  	explicit constexpr BackwardRange(const int l, const int r) : src(r), dst(l) {}
		explicit constexpr BackwardRange(const int n) : src(n), dst(0) {}
		constexpr BackwardRange begin() const { return *this; }
		constexpr BackwardRange end() const { return *this; }
		constexpr bool operator!=(BackwardRange) const { return src > dst; }
		constexpr void operator++() const {}
		constexpr int operator*() { return --src; }
	};
	using rep = ForwardRange;
	using per = BackwardRange;
};

/**
 * Description: Generic segment tree without lazy propagation
 * Source: Inspired by Jiangly - https://codeforces.com//contest/1672/submission/154766851
 * Verification:
 * Time Complexity: O(n) build, O(log n) per update/query
 */
template<typename T, typename Merge = plus<T>>
struct SegTree{
	int sz;
	const Merge merge;
	vector<T> t;
	SegTree(int n) : merge(Merge()) {
		sz = 1;
		while (sz < n) sz *= 2;
		t.resize(sz * 2);
	}
	void build(vector<T> &vec, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        if (l < (int)vec.size())
	            t[x] = vec[l];
	        return;
	    }
	    int mid = (l + r) / 2;
	    build(vec, 2 * x + 1, l, mid);
	    build(vec, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void build(vector<T> &vec)
	{
	    build(vec, 0, 0, sz);
	}
	void upd(int i, const T& v, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        t[x] = v;
	        return;
	    }
	    int mid = (l + r) / 2;
	    if (i < mid)
	        upd(i, v, 2 * x + 1, l, mid);
	    else
	        upd(i, v, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void upd(int i, const T& v)
	{
	    upd(i, v, 0, 0, sz);
	}
	T query(int l, int r, int x, int lx, int rx)
	{
	    if (lx >= r || rx <= l)
	        return T();
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

struct MinMax {
	int x, y; 
	MinMax(int x_ = -INF, int y_ = INF) : x(x_), y(y_) {}
	MinMax operator+(const MinMax& other) const {
		return {max(x, other.x), min(y, other.y)};
	}
};


constexpr int M = 1e5 + 100;
int par[M], depth[M], subt[M], pos[M], head[M], ver[M];
bitset<M> black{};
SegTree<MinMax> st(M);
vi adj[M];
int co;

void dfs(int u) {
	for (auto &v : adj[u]) {
		par[v] = u;
		adj[v].erase(find(all(adj[v]), u));
		depth[v] = depth[u] + 1;
		dfs(v);
		subt[u] += subt[v];
		if (subt[adj[u][0]] < subt[v]) swap(v, adj[u][0]);
	}
}
void decompose(int u) {
	pos[u] = co++;
	ver[pos[u]] = u;
	for (auto &v : adj[u]) {
		head[v] = (adj[u][0] == v ? head[u] : v);
		decompose(v);
	}
}
void upd(int u) {
	if (black[u]) st.upd(pos[u], {-INF, INF});
	else st.upd(pos[u], {pos[u], pos[u]});
	black[u].flip();
}
int query(int a, int b) {
	int res = INF;
	while (head[a] != head[b]) {
		if (depth[head[a]] > depth[head[b]]) {
			MinMax q = st.query(pos[head[a]], pos[a] + 1);
			if (q.x != -INF) return ver[q.x];
			a = par[head[a]];
		}else{
			MinMax q = st.query(pos[head[b]], pos[b] + 1);
			if (q.y != INF) res = ver[q.y];
			b = par[head[b]];
		}
	}
	dbg(pos[a], pos[b]);
	MinMax q = st.query(pos[a], pos[b] + 1);
	dbg(q.x, q.y);
	if (q.y != INF) res = ver[q.y];
	return (res == INF ? -1 : res + 1);
}

void solve()
{
	int n, q;
	cin >> n >> q;
	fill(par, par + n, -1);
	for (int i : rep(n - 1)) {
		int u, v;
		cin >> u >> v; u--, v--;
		adj[u].pb(v), adj[v].pb(u);
	}
	dfs(0), decompose(0);
	for (int i : rep(q)) {
		int t, v;
		cin >> t >> v; v--;
		if (t == 0) {
			upd(v);
		}else{
			cout << query(0, v) << '\n';
		}
	}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--)
	{
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
