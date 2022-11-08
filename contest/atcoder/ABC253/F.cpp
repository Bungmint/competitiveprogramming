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

// // USACO Guide coming in clutch again
// template<typename T, int MAXN>
// struct PersistentSegTree{
// 	struct Node {
// 		T val;
// 		Node *l, *r;
	
// 		Node(ll x) : val(x), l(nullptr), r(nullptr) {}
// 		Node(Node *ll, Node *rr) : val(0), l(ll), r(rr) {}
// 		Node(Node *ll, Node *rr, T x) : val(x), l(ll), r(rr) {}
// 	};
	
// 	T n, a[MAXN]; // The initial array and its size
// 	Node* roots[MAXN]; // The persistent array's roots
	
// 	Node* build(int l, int r) {
// 		if (r-l == 1) return new Node(a[l]);
// 		int mid = (l + r) / 2;
// 		return new Node(build(l, mid), build(mid, r));
// 	}
	
// 	Node* update(Node* node, T val, int pos, int l, int r) {
// 		if (r-l == 1) return new Node(val + (node == nullptr ? T(0) : node->val));
// 		int mid = (l + r) / 2;
// 		if (pos >= mid) return new Node(node->l, update(node->r, val, pos, mid, r), (node == nullptr ? 0 : node->val) + val);
// 		else return new Node(update(node->l, val, pos, l, mid), node->r, (node == nullptr ? 0 : node->val) + val);
// 	}
	
// 	T query(Node* node, int pos, int l, int r) {
// 		if (r-l == 1) return node->val;
// 		int mid = (l + r) / 2;
// 		if (pos >= mid) return query(node->r, pos, mid, r);
// 		return query(node->l, pos, l, mid);
// 	}
// 	T range_query(Node* node, int ql, int qr, int l, int r) {
// 		if (ql >= r || l >= qr) return T(0);
// 		if (ql <= l && r <= qr) return (node == nullptr ? 0 : node->val);
// 		int mid = (l + r) >> 1;
// 		T a = range_query(node->l, ql, qr, l, mid);
// 		T b = range_query(node->r, ql, qr, mid, r);
// 		return a + b;
// 	}
	
// 	T get_item(int index, int time) {
// 		// Gets the array item at a given index and time
// 		return query(roots[time], index, 0, n);
// 	}
// 	T range_get(int ql, int qr, int time) {
// 		return range_query(roots[time], ql, qr, 0, n);
// 	}
	
// 	void update_item(int index, T value, int prev_time, int curr_time) {
// 		// Updates the array item at a given index and time
// 		roots[curr_time] = update(roots[prev_time], index, value, 0, n);
// 	}
	
// 	PersistentSegTree(int nn) {
// 		// Initializes the persistent array, given an input array
// 		n = nn;
// 		for (int i = 0; i < n; i++)
// 			a[i] = 0;
// 		roots[0] = build(0, n);
// 	}
// };

/**
 * Description: Performs range prefix sum queries and point updates. lower_bound returns the first prefix sum >= v
 * Source: Own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=693
 * Time Complexity: O(log n) for query and update
 * 0-indexing
 */
template <typename T>
struct BIT
{
	int N;
	vector<T> bit;
	BIT(int n)
	{
		bit.resize(n + 1);
		N = n;
	}
	void upd(int id, T v)
	{
		for (id++; id <= N; id += id & -id)
			bit[id] += v;
	}
	T query(int id)
	{
		T res = 0;
		for (id++; id > 0; id -= id & -id)
			res += bit[id];
		return res;
	}
	T query(int l, int r)
	{
		return l > r ? 0 : query(r) - query(l - 1);
	}
	T lower_bound(T v)
	{
		int id = 0;
		T sum = 0;
		int lg = 31 - __builtin_clz(N);
		for (int j = lg; ~j; j--)
		{
			if (id + (1 << j) <= N && sum + bit[id + (1 << j)] < v)
			{
				id += (1 << j);
				sum += bit[id];
			}
		}
		return id;
	}
};


void solve()
{
	int n, m, q;
	cin >> n >> m >> q;
	BIT<ll> bit(m + 1);
	vpi last(n + 1, make_pair(0, 0));
	vector<vpi> todo(q + 1);
	vector<ar<int, 4>> query(q + 1);
	vl ans(q + 1);
	for (int i : rep(1, 1 + q)) {
		int t;
		cin >> t;
		if (t == 1) {
			int l, r, x;
			cin >> l >> r >> x;
			l--;
			query[i] = {t, l, r, x};
		}else if (t == 2){
			int id, x;
			cin >> id >> x;
			id--;
			last[id] = {i, x};
			query[i] = {t, id, x};
		}else{
			int r, c;
			cin >> r >> c, r--, c--;
			todo[last[r].fi].pb({i, c});
			ans[i] = last[r].se;
			query[i] = {t, r, c};
		}
	}
	for (int i : rep(1, 1 + q)) {
		auto [t, a, b, c] = query[i];
		if (t == 1) {
			bit.upd(a, c);
			bit.upd(b, -c);
			dbg(a, b);
		}else if (t == 3) {
			ans[i] += bit.query(0, b);
			if (i == 4) dbg(ans[i]);
		}
		for (auto &[id, loc] : todo[i]) {
			ans[id] -= bit.query(0, loc);
			if (id == 4) dbg(i, ans[id], bit.query(0, loc));
		}
	}
	for (int i : rep(1, 1 + q)) {
		if (query[i][0] == 3) {
			cout << ans[i] << '\n';
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
