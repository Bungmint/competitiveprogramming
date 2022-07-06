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

inline namespace RecursiveLambda
{
	template <typename Fun>
	struct y_combinator_result
	{
		Fun fun_;
		template <typename T>
		explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}
		template <typename... Args>
		decltype(auto) operator()(Args &&...args)
		{
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun)
	{
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

inline namespace Range {
	class ForwardRange {
		int src, dst;

	  public:
	  	explicit constexpr ForwardRange(const int l, const int r) : src(l), dst(r) {}
		explicit constexpr ForwardRange(const int n) : src(0), dst(n) {}
		constexpr ForwardRange begin() const { return *this; }
		constexpr monostate end() const { return {}; }
		constexpr bool operator!=(monostate) const { return src < dst; }
		constexpr void operator++() const {}
		constexpr int operator*() { return src++; }
	};
	class BackwardRange {
		int src, dst;

	  public:
	  	explicit constexpr BackwardRange(const int l, const int r) : src(r), dst(l) {}
		explicit constexpr BackwardRange(const int n) : src(n), dst(0) {}
		constexpr BackwardRange begin() const { return *this; }
		constexpr monostate end() const { return {}; }
		constexpr bool operator!=(monostate) const { return src > dst; }
		constexpr void operator++() const {}
		constexpr int operator*() { return --src; }
	};
	using rep = ForwardRange;
	using per = BackwardRange;
};

/**
 * Description: Generic segment tree with lazy propagation
 * Source: Inspired by Jiangly - https://codeforces.com//contest/1672/submission/154766851
 * Verification: https://cses.fi/problemset/task/1735
 * Time Complexity: O(n) build, O(log n) per update/query
 */
template<typename T, typename U, typename Merge = plus<T>>
struct LazySegTree{
	int sz;
	const Merge merge;
	vector<T> t;
	vector<U> lazy;
	LazySegTree(int n) : merge(Merge()) {
		sz = 1;
		while (sz < n) sz *= 2;
		t.resize(sz * 2);
		lazy.resize(sz * 2);
	}
	void build(const vector<T> &vec, int x, int l, int r)
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
	void build(const vector<T> &vec)
	{
	    build(vec, 0, 0, sz);
	}
	void upd(int i, const T& v, int x, int l, int r)
	{
		push(x, l, r);
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
	void rangeUpd(int l, int r, U v, int x, int lx, int rx) {
		push(x, lx, rx);
		if (lx >= r || rx <= l) return;
		if (lx >= l && rx <= r) {
			lazy[x] = lazyOnLazy(lazy[x], v);
			push(x, lx, rx);
			return;
		}
		int mid = (lx + rx) / 2;
		rangeUpd(l, r, v, 2 * x + 1, lx, mid);
		rangeUpd(l, r, v, 2 * x + 2, mid, rx);
		t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void rangeUpd(int l, int r, U v) {
		rangeUpd(l, r, v, 0, 0, sz);
	}
	T query(int l, int r, int x, int lx, int rx)
	{
		push(x, lx, rx);
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
	void push(int x, int l, int r) {
		if (lazy[x] == U()) return;
		t[x] = lazyOnVal(t[x], lazy[x], l, r);
		if (r - l > 1) {
			lazy[2 * x + 1] = lazyOnLazy(lazy[2 * x + 1], lazy[x]);
			lazy[2 * x + 2] = lazyOnLazy(lazy[2 * x + 2], lazy[x]);
		}
		lazy[x] = U();
	}
	U lazyOnLazy(U oldV, U newV) {
		return oldV + newV;
	}
	T lazyOnVal(T val, U la, int l, int r) {
		return val + la;
	}
};

struct Max {
	int x;
	Max(int _x = -2 * INF) : x(_x) {}
	Max operator+(const Max& other) const {
		return max(x, other.x);
	}
	Max operator+(const int& z) const {
		return x + z;
	}
};


void solve()
{
	int n;
	cin >> n;
	vector<vi> g(n);
	vi subt(n), depth(n), head(n), pos(n), par(n, -1);
	LazySegTree<Max, int> st(n);
	st.build(vector<Max>(n, 0));
	int ti{};
	for (int i : rep(n - 1)) {
		int u, v;
		cin >> u >> v, u--, v--;
		g[u].pb(v), g[v].pb(u);
	}
	auto init = y_combinator([&](auto self, int u) -> void {
		subt[u] = 1;
		for (auto &v : g[u]) {
			g[v].erase(find(all(g[v]), u));
			par[v] = u;
			depth[v] = depth[u] + 1;
			self(v);
			subt[u] += subt[v];
			if (subt[v] > subt[g[u][0]]) swap(v, g[u][0]);
		}
	});
	auto label = y_combinator([&](auto self, int u) -> void {
		pos[u] = ti++;
		for (auto &v : g[u]) {
			if (v == g[u][0]) head[v] = head[u];
			else head[v] = v;
			self(v);
		}
	});
	auto modifySub = [&](int u, int v) -> void {
		st.rangeUpd(pos[u], pos[u] + subt[u], v); 
	};
	// auto modifyPath = [&](int u, int v, int t) -> void {
	// 	for (; head[u] != head[v]; v = par[head[v]]) {
	// 		if (depth[head[u]] > depth[head[v]]) swap(u, v);
	// 		st.rangeUpd(pos[head[v]], pos[v] + 1, t);
	// 	}
	// 	if (depth[u] > depth[v]) swap(u, v);
	// 	st.rangeUpd(pos[u], pos[v] + 1, t);
	// };
	auto queryPath = [&](int u, int v) -> int {
		int res = -2 * INF;
		for (; head[u] != head[v]; v = par[head[v]]) {
			if (depth[head[u]] > depth[head[v]]) swap(u, v);
			ckmax(res, st.query(pos[head[v]], pos[v] + 1).x);
		}
		if (depth[u] > depth[v]) swap(u, v);
		ckmax(res, st.query(pos[u], pos[v] + 1).x);
		return res;
	};
	init(0), label(0);
	int q;
	cin >> q;
	for (int i : rep(q)) {
		string s;
		cin >> s;
		if (s[0] == 'a') {
			int t, v;
			cin >> t >> v;
			t--;
			modifySub(t, v);
		}else{
			int a, b;
			cin >> a >> b;
			a--, b--;
			cout << queryPath(a, b) << '\n';
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
