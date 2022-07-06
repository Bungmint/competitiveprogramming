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
 * Description: Data structure that supports range idempotent queries on a static array
 * Source: Own
 * Verification:
 * Time Complexity: O(nlogn) build, O(1) query
 */
template<typename T>
struct SparseTableMax{
	vector<vector<T>> spar;
	inline T merge(const T& a, const T& b) { // change this
		return max(a, b);
	} 
	SparseTableMax(const vector<T>& a) {
		int lg = 32 - __builtin_clz(sz(a));
		spar.assign(lg, vi(sz(a), 0));
		for (int i = 0; i < sz(a); ++i) spar[0][i] = a[i];
		for (int j = 1; j < lg; ++j) 
			for (int i = 0; i + (1 << j) <= sz(a); ++i)
				spar[j][i] = merge(spar[j - 1][i], spar[j - 1][i + (1 << (j - 1))]);
	}
	SparseTableMax(T a[], int n) {
		int lg = 32 - __builtin_clz(n);
		spar.assign(lg, vi(n, 0));
		for (int i = 0; i < n; ++i) spar[0][i] = a[i];
		for (int j = 1; j < lg; ++j) 
			for (int i = 0; i + (1 << j) <= n; ++i)
				spar[j][i] = merge(spar[j - 1][i], spar[j - 1][i + (1 << (j - 1))]);
	}
	T query(int a, int b) {
		assert(a <= b);
		int dif = 31 - __builtin_clz(b - a + 1);
		return merge(spar[dif][a], spar[dif][b - (1 << dif) + 1]);
	}
};
template<typename T>
struct SparseTableMin{
	vector<vector<T>> spar;
	inline T merge(const T& a, const T& b) { // change this
		return min(a, b);
	} 
	SparseTableMin(const vector<T>& a) {
		int lg = 32 - __builtin_clz(sz(a));
		spar.assign(lg, vi(sz(a), 0));
		for (int i = 0; i < sz(a); ++i) spar[0][i] = a[i];
		for (int j = 1; j < lg; ++j) 
			for (int i = 0; i + (1 << j) <= sz(a); ++i)
				spar[j][i] = merge(spar[j - 1][i], spar[j - 1][i + (1 << (j - 1))]);
	}
	SparseTableMin(T a[], int n) {
		int lg = 32 - __builtin_clz(n);
		spar.assign(lg, vi(n, 0));
		for (int i = 0; i < n; ++i) spar[0][i] = a[i];
		for (int j = 1; j < lg; ++j) 
			for (int i = 0; i + (1 << j) <= n; ++i)
				spar[j][i] = merge(spar[j - 1][i], spar[j - 1][i + (1 << (j - 1))]);
	}
	T query(int a, int b) {
		assert(a <= b);
		int dif = 31 - __builtin_clz(b - a + 1);
		return merge(spar[dif][a], spar[dif][b - (1 << dif) + 1]);
	}
};


void solve()
{
	int n;
	cin >> n;
	vi a(n), id(n), rma(n), rmi(n);
	
	for (auto &e : a) cin >> e, e--;
	for (int i : rep(n)) id[a[i]] = i;
	stack<int> st;
	SparseTableMax<int> stma(a);
	SparseTableMin<int> stmi(a);
	for (int i : per(n)) {
		while (sz(st) && a[st.top()] < a[i]) st.pop();
		rma[i] = (sz(st) ? st.top() : n);
		st.push(i);
	}
	while (sz(st)) st.pop();
	for (int i : per(n)) {
		while (sz(st) && a[st.top()] > a[i]) st.pop();
		rmi[i] = (sz(st) ? st.top() : n);
		st.push(i);
	}
	int cur = 0;
	int ans = 0;
	dbg(rma[0], rmi[0], stma.query(cur, rmi[cur] - 1));	
	while (cur != n - 1) {
		ans++;
		dbg(cur, 1);
		if (a[cur] > a[cur + 1]) {
			int z = stmi.query(cur, rma[cur] - 1);
			cur = id[z];
		}else{
			int z = stma.query(cur, rmi[cur] - 1);
			cur = id[z];
		}
		dbg(cur, 2);
	}
	cout << ans << "\n";
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	while (testcase--)
	{
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
