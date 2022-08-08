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

#define monostate int
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
 * Description: Policy-based data structure to support queries for kth largest and number of elements less than given number.
 * Source: https://codeforces.com/blog/entry/11080
 * Verification: https://www.spoj.com/problems/ORDERSET/
 * Time: O(log n) for both queries, but has a big constant
 */
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// find_by_order(k) - returns iterator to kth largest element (0-indexed) or an iterator to end if it doesn't exist
// order_of_key(x) - returns the number of elements in the set strictly smaller than x

void solve()
{
	int n;
	cin >> n;
	int co = n;
	vector<vi> g(2 * n - 1); // directed graph direction: root to leaves
	vector<Tree<int>> a(2 * n - 1);
	stack<int> st;
	for (int i : rep(2 * n - 1)) {
		int u;
		cin >> u;
		if (u == 0) {
			int cur = co++;
			if (sz(st)) g[st.top()].pb(cur);
			st.push(cur);
		}else{
			u--;
			g[st.top()].pb(u);
			while (sz(st) && sz(g[st.top()]) == 2) st.pop();
		}
	}
	int root = n;
	ll ans{};
	auto dfs = y_combinator([&](auto self, int u) -> void {
		if (sz(g[u]) == 0) {
			a[u].insert(u);
			return;
		}
		int L = g[u][0], R = g[u][1];
		self(L), self(R);
		int add{}, SZ{max(sz(a[L]), sz(a[R]))};
		if (sz(a[L]) > sz(a[R])) a[u].swap(a[L]), add = R;
		else a[u].swap(a[R]), add = L;
		ll resL{}, resR{};
		for (auto &e : a[add]) {
			int x = a[u].order_of_key(e);
			resL += x; resR += SZ - x;
		}
		ans += min(resL, resR);
		for (auto &e : a[add]) {
			a[u].insert(e);
		}
		Tree<int>().swap(a[add]);
	});
	dfs(root);
	cout << ans << '\n';
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
