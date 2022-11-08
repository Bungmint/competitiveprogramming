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
	BIT(int n, int k) {
		bit.assign(n + 1, k);
		N = n;
		for (int i : rep(1, N + 1)) {
			int z = i + (i & - i);
			if (z <= N) bit[z] += bit[i];
		}
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
	int n, k, m;
	cin >> n >> k >> m;
	vi c(n);
	vector<vi> adj(n), up(19, vi(n));
	vi tin(n), tout(n), subtree(n);
	BIT<int> bit(n, 1);
	vector<set<pii>> sets(k);
	int timer{};
	for (auto &e : c) cin >> e, e--;
	for (int i : rep(n - 1)) {
		int u, v;
		cin >> u >> v, u--, v--;
		adj[u].pb(v), adj[v].pb(u);
	}
	auto dfs = y_combinator([&](auto self, int u, int pu) -> void {
		tin[u] = timer++;
		subtree[u] = 1;
		for (auto &v : adj[u]) {
			if (v == pu) continue;
			up[0][v] = u;
			for (int i : rep(1, 19)) {
				up[i][v] = up[i - 1][up[i - 1][v]];
			}
			self(v, u);
			subtree[u] += subtree[v];
		}
		tout[u] = timer - 1;
	});
	auto isAnc = [&](int u, int aliens) -> bool {
		if (sz(sets[aliens]) == 0) return false;
		auto it = sets[aliens].lb(make_pair(tin[u], -INF));
		return it != sets[aliens].end() && it->se <= tout[u];
	};
	auto add = [&](int u, int alien) -> void {
		// binary search the parent node
		if (sz(sets[alien])) {
			int st = u;
			for (int j : per(19)) {
				if (!isAnc(up[j][st], alien)) {
					st = up[j][st];
				}
			}
			if (!isAnc(st, alien)) st = up[0][st];
			bit.upd(tin[st], -1);
		}
		sets[alien].insert({tin[u], tout[u]});
	};
	auto remove = [&](int u, int alien) -> void {
		sets[alien].erase({tin[u], tout[u]});
		if (sz(sets[alien])) {
			int st = u;
			for (int j : per(19)) {
				if (!isAnc(up[j][st], alien)) {
					st = up[j][st];
				}
			}
			if (!isAnc(st, alien)) st = up[0][st];
			bit.upd(tin[st], 1);
		}
	};
	dfs(0, -1);
	for (int i : rep(n)) {
		add(i, c[i]);
	}
	for (int i : rep(m)) {
		int t, u;
		cin >> t >> u; u--;
		if (t == 1) {
			int x;
			cin >> x, x--;
			remove(u, c[u]);
			add(u, x);
			c[u] = x;
		}else{
			cout << bit.query(tin[u], tout[u]) << '\n'; 
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
