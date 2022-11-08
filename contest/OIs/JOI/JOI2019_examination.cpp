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
 * Description: point update and rectangle sum with offline 2D BIT. 
	* For each of the points to be updated, $x\in (0,SZ)$ and $y\neq 0$.
 * Time: O(N\log^2 N)
 * Memory: O(N\log N)
 * Source: Benq
 * Verification: 
 	* https://dmoj.ca/problem/occ19g4
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=722 (753 ms)
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=601 (679 ms)
 */

template<class T, int SZ> struct BITOff2D { 
	bool mode = 0; // mode = 1 -> initialized
	vpi todo; // locations of updates to process
	int cnt[SZ], st[SZ];
	vi val; vector<T> bit; // store all BITs in single vector
	void init() { assert(!mode); mode = 1;
		int lst[SZ]; for (int i : rep(SZ)) lst[i] = cnt[i] = 0;
		sort(all(todo),[](const pii& a, const pii& b) { 
			return a.se < b.se; });
		for (auto &t : todo) for (int x = t.fi; x < SZ; x += x & -x) 
			if (lst[x] != t.se) lst[x] = t.se, cnt[x]++;
		int sum = 0; for (int i : rep(SZ)) lst[i] = 0, st[i] = (sum += cnt[i]);
		val.resize(sum); bit.resize(sum); reverse(all(todo));
		for (auto &t : todo) for (int x = t.fi; x < SZ; x += x & -x) 
			if (lst[x] != t.se) lst[x] = t.se, val[--st[x]] = t.se;
	}
	int rank(int y, int l, int r) {
		return ub(begin(val) + l, begin(val) + r, y) - begin(val) - l; }
	void UPD(int x, int y, T t) {
		for (y = rank(y, st[x], st[x] + cnt[x]); y <= cnt[x]; y += y & -y) 
			bit[st[x] + y - 1] += t; }
	void upd(int x, int y, T t) { 
		if (!mode) todo.pb({x, y});
		else for (; x < SZ; x += x & -x) UPD(x, y, t); }
	int QUERY(int x, int y) { T res = 0;
		for (y = rank(y, st[x], st[x] + cnt[x]); y; y -= y & -y) res += bit[st[x] + y - 1];
		return res; }
	T query(int x, int y) { assert(mode);
		T res = 0; for (; x; x -= x & -x) res += QUERY(x, y);
		return res; }
	T query(int xl, int xr, int yl, int yr) { 
		return query(xr, yr) - query(xl - 1, yr)
			- query(xr, yl - 1) + query(xl - 1, yl - 1); }
};
BITOff2D<int, 210000> bit;

void solve()
{
	int n, q;
	cin >> n >> q;
	vpi sorted_by_sum(n);
	vector<ar<int, 3>> queries(q);
	vi ind(q), ans(q), xs(n), ys(n);
	for (int i : rep(n)) {
		int s, t;
		cin >> s >> t;
		sorted_by_sum[i] = {s, t};
		xs[i] = s;
		ys[i] = t;
		// bit.upd(s, t, 1);
	}
	sort(all(sorted_by_sum), [&](auto x, auto y){
		return x.fi + x.se > y.fi + y.se;
	});
	for (int i : rep(q)) {
		auto &[x, y, z] = queries[i];
		cin >> x >> y >> z;
		xs.pb(x), ys.pb(y);
	}
	iota(all(ind), 0);
	sort(all(ind), [&](int i, int j){
		return queries[i][2] > queries[j][2];
	});
	sort(all(xs)), xs.resize(unique(all(xs)) - xs.begin());
	sort(all(ys)), ys.resize(unique(all(ys)) - ys.begin());
	for (auto &[s, t] : sorted_by_sum) {
		s = lb(all(xs), s) - xs.begin() + 1;
		t = lb(all(ys), t) - ys.begin() + 1;
		bit.upd(s, t, 0);
	}
	bit.init();
	int ptr{};
	for (int i : rep(q)) {
		auto& [x, y, z] = queries[ind[i]];
		x = lb(all(xs), x) - xs.begin() + 1;
		y = lb(all(ys), y) - ys.begin() + 1;
		while (ptr < n && xs[sorted_by_sum[ptr].fi - 1] + ys[sorted_by_sum[ptr].se - 1] >= z) {
			auto [s, t] = sorted_by_sum[ptr++];
			bit.upd(s, t, 1);
		}
		ans[ind[i]] = bit.query(x, sz(xs), y, sz(ys));
	}
	for (int i : rep(q)) cout << ans[i] << '\n';
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
