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

#ifdef LOCAL
#include "miscellaneous/debug.h"
#else
#define dbg(...) 42
#endif

inline namespace RecursiveLambda {
	template <typename Fun>
	struct y_combinator_result {
		Fun fun_;
		template <typename T>
		explicit constexpr y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}
		template <typename... Args>
		constexpr decltype(auto) operator()(Args &&...args) const {
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun) {
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

/*
 * Solution
 * Tree DP where we store the possible intervals in each node
**/

void solve()
{
	int n, k;
	cin >> n;
	vector<vi> g(n);
	vpi dp(n, make_pair(-INF, INF));
	vi ans(n);
	bool ok = 1;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v, u--, v--;
		g[u].pb(v), g[v].pb(u);
	}
	cin >> k;
	vi vert(k);
	for (int &e : vert) {
		cin >> e; e--;
		int p; cin >> p;
		dp[e] = {p, p};
	}
	auto dfs = y_combinator([&](auto&& self, int u) -> void {
		for (int &v : g[u]) {
			g[v].erase(find(all(g[v]), u));
			self(v);
		}
	});
	auto pullDP = y_combinator([&](auto self, int u) -> void {
		auto &[ra, rb] = dp[u];
		for (auto &v : g[u]) {
			self(v);
			if (!ok) return;
			auto &[L, R] = dp[v];
			int d = 1;
			if (L == -INF && R == INF) continue;
			if (ra == -INF && rb == INF) {
				ckmax(ra, L - d);
				ckmin(rb, R + d);
			}else{
				if ((ra & 1) != ((L - d) & 1) || (rb & 1) != ((R + d) & 1)) {
					ok = 0;
					return;
				}
				ckmax(ra, L - d), ckmin(rb, R + d);
			}
		}
		if (ra > rb) ok = 0;
	});
	auto pushDP = y_combinator([&](auto self, int u) -> void {
		int x = dp[u].fi;
		ans[u] = x;
		for (auto &v : g[u]) {
			auto &[L, R] = dp[v];
			ckmax(L, x - 1);
			ckmin(R, x + 1);
			if (L > R) {
				ok = 0; return;
			}
			self(v);
		}
	});

	dfs(0);
	pullDP(0);
	if (!ok) {
		cout << "No\n";
		return;
	}
	pushDP(0);
	if (!ok) {
		cout << "No\n";
		return;
	}
	cout << "Yes\n";
	for (int i = 0; i < n; i++) cout << ans[i] << '\n';
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
