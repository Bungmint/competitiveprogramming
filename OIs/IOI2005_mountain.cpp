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
#define dbg(...) cerr << "\033[1;35m(" << #__VA_ARGS__ << "):\033[33m", dbg_out(__VA_ARGS__)
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

class Range {
	struct Iter
	{
		int iter;
		constexpr Iter(int it) noexcept : iter(it) {}
		constexpr void operator++() noexcept { iter++; }
		constexpr bool operator!=(const Iter &other) const noexcept { return iter != other.iter; }
		constexpr int operator*() const noexcept { return iter; }
	};
	const Iter first, last;

public:
	explicit constexpr Range(const int f, const int l) noexcept : first(f), last(max(f, l)) {}
	constexpr Iter begin() const noexcept { return first; }
	constexpr Iter end() const noexcept { return last; }
};

constexpr Range rep(const int l, const int r) noexcept { return Range(l, r); }
constexpr Range rep(const int n) noexcept { return Range(0, n); }

class ReversedRange {
    struct Iter {
        int itr;
        constexpr Iter(const int pos) noexcept : itr(pos) {}
        constexpr void operator++() noexcept { --itr; }
        constexpr bool operator!=(const Iter& other) const noexcept { return itr != other.itr; }
        constexpr int operator*() const noexcept { return itr; }
    };
    const Iter first, last;
 
  public:
    explicit constexpr ReversedRange(const int f, const int l) noexcept
        : first(l - 1), last(min(f, l) - 1) {}
    constexpr Iter begin() const noexcept { return first; }
    constexpr Iter end() const noexcept { return last; }
};
 
constexpr ReversedRange per(const int l, const int r) noexcept { return ReversedRange(l, r); }
constexpr ReversedRange per(const int n) noexcept { return ReversedRange(0, n); }

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
		val.sum = la.elev * val.length;
		val.max = max(0, val.sum);
		return val;
	}
	int query(int h, int x, int lx, int rx) {
		push(x, lx, rx);
		if (rx - lx == 1) {
			if (t[x].length == 0) return 0;
			int d = t[x].sum / t[x].length;
			if (d <= 0) return t[x].length;
			else return min(t[x].length, h / d);
		}
		int mid = (lx + rx) >> 1;
		push(2 * x + 1, lx, mid), push(2 * x + 2, mid, rx);
		if (t[2 * x + 1].max > h) return query(h, 2 * x + 1, lx, mid);
		else return t[2 * x + 1].length + query(h - t[2 * x + 1].sum, 2 * x + 2, mid, rx);
	}
	int query(int h) {
		return query(h, 0, 0, sz);
	}
};

struct Node {
	int sum, max, length;
	Node(ll su = 0, ll mx = 0, ll leng = 0) : sum(su), max(mx), length(leng) {}
	Node operator+(const Node& other) const {
		Node ret{};
		ret.length = length + other.length;
		ret.sum = sum + other.sum;
		ret.max = std::max(max, sum + other.max);
		return ret;
	}
};
struct Lazy {
	int elev;
	Lazy(int elev_ = numeric_limits<int>::min()) : elev(elev_) {}
	Lazy operator+(const Lazy& other) const {
		return other;
	}
	bool operator==(const Lazy& other) const {
		return elev == other.elev;
	}
};

void solve()
{
	int n;
	cin >> n;
	vi ind;
	vector<ar<int, 4>> query;
	while (1) {
		char c;
		cin >> c;
		if (c == 'E') break;
		bool fl = c == 'I';
		dbg(fl);
		if (fl) {
			int a, b, d;
			cin >> a >> b >> d;
			a--, b--;
			ind.pb(a), ind.pb(b), ind.pb(a + 1), ind.pb(b + 1);
			query.pb({0, a, b, d});
		}else{
			int h;
			cin >> h;
			query.pb({1, h, 0, 0});
		}
	}
	ind.pb(0), ind.pb(n);
	sort(all(ind)), ind.resize(unique(all(ind)) - ind.begin());
	dbg(ind);
	vector<Node> a(sz(ind) - 1);
	for (int i : rep(sz(ind) - 1)) {
		assert(ind[i] != ind[i + 1]);
		a[i] = {0, 0, ind[i + 1] - ind[i]};
	}
	LazySegTree<Node, Lazy> st(sz(a));
	st.build(a);
	for (auto &[t, a, b, d] : query) {
		if (t) {
			cout << st.query(a) << '\n';
		}else{
			a = lb(all(ind), a) - ind.begin();
			b = lb(all(ind), b) - ind.begin();
			dbg(a, b, d);
			st.rangeUpd(a, b + 1, {d});
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