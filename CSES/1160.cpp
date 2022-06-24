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


void solve()
{
	int n, q;
	cin >> n >> q;
	vi nxt(n), depth(n), dist(n), cycle(n), SZ(n);
	vector<bool> vis(n);
	vector<vi> radj(n), jmp(18, vi(n));
	for (int i : rep(n)) cin >> nxt[i], nxt[i]--, radj[nxt[i]].pb(i), jmp[0][i] = nxt[i];
	for (int i : rep(1, 18)) for (int j : rep(n)) {
		jmp[i][j] = jmp[i - 1][jmp[i - 1][j]];
	}
	int co{};
	auto raj = y_combinator([&](auto self, int u) -> void {
		for (auto &v : radj[u]) {
			if (!vis[v]) {
				vis[v] = 1;
				depth[v] = depth[u] + 1;
				cycle[v] = cycle[u];
				self(v);
			}
		}
	});
	for (int i : rep(n)) {
		if (vis[i]) continue;
		int x = i, y = i;
		do {
			x = nxt[x];
			y = nxt[nxt[y]];
		}while (x != y);
		int cur{};
		do {
			vis[x] = 1;
			cycle[x] = co;
			dist[x] = cur++;
			x = nxt[x];
		}while (x != y);
		do {
			SZ[x] = cur;
			raj(x);
			x = nxt[x];
		}while (x != y);
		co++;
	}
	auto jump = [&](int u, int k) -> int {
		for (int i : rep(18)) if (k >> i & 1) u = jmp[i][u];
		return u;
	};
	for (int i : rep(q)) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		if (u == v) {
			cout << 0 << '\n';
			continue;
		}
		if (cycle[u] != cycle[v]) {
			cout << -1 << '\n';
			continue;
		}
		if (depth[u] == 0 && depth[v]) {
			cout << -1 << '\n';
			continue;
		}
		if (depth[u] == 0 && depth[v] == 0) {
			int z = dist[v] - dist[u];
			if (z < 0) z += SZ[u];
			cout << z << '\n';
			continue;
		}
		if (depth[u] && depth[v] == 0) {
			int z = depth[u];
			u = jump(u, depth[u]);
			z += dist[v] - dist[u] + (dist[v] < dist[u] ? SZ[u] : 0);
			cout << z << '\n';
			continue;
		}
		if (depth[u] <= depth[v]) {
			cout << -1 << '\n';
			continue;
		}
		dbg();
		int z = -depth[v] + depth[u];
		u = jump(u, z);
		cout << (u == v ? z : -1) << '\n';
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
