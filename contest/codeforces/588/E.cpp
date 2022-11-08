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


void solve()
{
	int n, m, q;
	cin >> n >> m >> q;
	int K = 32 - __builtin_clz(n);
	vector<vi> g(n + 1);
	vector<vi> city(n + 1);
	vector<vi> up(K, vi(n + 1));
	vector<ar<int, 10>> mini(n + 1);
	vector<vector<ar<int, 10>>> miniDP(K, vector<ar<int,10>>(n + 1));
	vi depth(n + 1);
	for (int i : rep(n - 1)) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	for (int i : rep(1, m + 1)) {
		int c;
		cin >> c;
		city[c].pb(i);
	}
	auto ins = [&](ar<int, 10>& a, int b) -> void {
		if (b == 0) return;
		for (int i : rep(10)) {
			if (a[i] > b || a[i] == 0) swap(a[i], b);
			if (a[i] == b) return;
		}
	};
	auto insins = [&](ar<int, 10>& a, const ar<int, 10>& b) -> void {
		for (auto &e : b) ins(a, e);
	};
	auto dfs = y_combinator([&](auto self, int u, int pu) -> void {
		for (auto &e : city[u]) {
			ins(mini[u], e);
		}
		for (auto &v : g[u]) {
			if (v == pu) continue;
			depth[v] = depth[u] + 1;
			up[0][v] = u;
			for (int i : rep(1, K)) {
				up[i][v] = up[i - 1][up[i - 1][v]];
				
			}
			self(v, u);
		}
	});
	auto calc = y_combinator([&](auto self, int u, int pu) -> void {
		for (auto &v : g[u]) {
			if (v == pu) continue;
			miniDP[0][v] = mini[v];
			insins(miniDP[0][v], mini[u]);
			for (int i : rep(1, K)) {
				miniDP[i][v] = miniDP[i - 1][v];
				if (up[i - 1][v]) {
					insins(miniDP[i][v], miniDP[i - 1][up[i - 1][v]]);
				}
			}
			self(v, u);
		}
	});
	auto query = [&](int u, int v) -> ar<int, 10> {
		ar<int, 10> res{};
		insins(res, mini[u]);
		insins(res, mini[v]);
		if (depth[u] < depth[v]) swap(u, v);
		int d = depth[u] - depth[v];
		for (int i : per(K)) {
			if (d >> i & 1) {
				insins(res, miniDP[i][u]);
				u = up[i][u];
			}
		}
		if (u == v) return res;
		for (int i : per(K)) {
			if (up[i][u] != up[i][v]) {
				insins(res, miniDP[i][u]);
				insins(res, miniDP[i][v]);
				u = up[i][u], v = up[i][v];
			}
		}
		insins(res, miniDP[0][u]);
		insins(res, miniDP[0][v]);
		// dbg(u, v, miniDP[0][u], miniDP[0][v]);
		return res;
	};
	dfs(1, 0), calc(1, 0);
	for (int i : rep(q)) {
		int v, u, a;
		cin >> v >> u >> a;
		ar<int, 10> res = query(u, v);
		int k = min(a, 10 - (int)count(all(res), 0));
		cout << k;
		for (auto j : rep(k)) cout << ' ' << res[j];
		cout << '\n';
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
