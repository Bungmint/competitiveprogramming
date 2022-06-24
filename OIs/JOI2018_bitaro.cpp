// Copyright © 2022 Youngmin Park. All rights reserved.
#pragma GCC optimize("O3")
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

constexpr int N = 1e5 + 10;
constexpr int SQ = 320;
int n, m, q;
vi adj[N], radj[N], queries[N];
bitset<N> busy, used;
int t[N], DP[N];
vpi dp[N];

void solve()
{
	cin >> n >> m >> q;
	for (int i : rep(m)) {
		int u, v;
		cin >> u >> v, u--, v--;
		adj[u].pb(v), radj[v].pb(u);
	}
	for (int i : rep(n)) {
		dp[i] = {{0, i}};
		for (int j : radj[i]) {
			vpi res;
			int sa = sz(dp[i]), sb = sz(dp[j]);
			int a = 0, b = 0;
			while (sz(res) < SQ && (a < sa || b < sb)) {
				if (b == sb || (a != sa && dp[i][a].fi >= dp[j][b].fi + 1)) {
					if (used[dp[i][a].se]) a++;
					else{
						res.pb(dp[i][a]);
						used[dp[i][a].se] = 1;
						a++;
					}
				}else{
					if (used[dp[j][b].se]) b++;
					else{
						res.pb({dp[j][b].fi + 1, dp[j][b].se});
						used[dp[j][b].se] = 1;
						b++;
					}
				}
			}
			for (auto [d, v] : res) used[v] = 0;
			swap(res, dp[i]);
		}
		dbg(dp[i]);
	}
	auto naiveDP = [&](int t, vi& C) -> int {
		for (int i : rep(n)) DP[i] = 0;
		for (int i : C) DP[i] = -1;
		for (int i : rep(t + 1)) {
			for (int j : radj[i]) {
				if (DP[j] >= 0) ckmax(DP[i], DP[j] + 1);
			}
		}
		return DP[t];
	};
	for (int i : rep(q)) {
		cin >> t[i];
		t[i]--;
		int x;
		cin >> x;
		queries[i].resize(x);
		for (auto &e : queries[i]) cin >> e, e--, busy[e] = 1;
		if (x >= SQ) {
			cout << naiveDP(t[i], queries[i]) << '\n';
		}else{
			int ans = -1;
			for (auto &[d, v] : dp[t[i]]) {
				if (!busy[v]) ckmax(ans, d);
			}
			cout << ans << '\n';
		}
		for (auto &e : queries[i]) busy[e] = 0;
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
