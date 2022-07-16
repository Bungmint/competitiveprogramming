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
ll cdiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // divide a by b rounded down

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

void solve() {
	int n;
	cin >> n;
	vi a(n);
	for (auto &e : a) cin >> e;
	vector<vi> g(n);
	vector<vi> dp(n, vi(2));
	vi ans;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v, u--, v--;
		g[u].pb(v), g[v].pb(u);
	}
	auto dfs = y_combinator([&](auto self, int u, int pu) -> void {
		dp[u][1] = a[u];
		for (auto &v : g[u]) {
			if (v == pu) {
				continue;
			}
			self(v, u);
			dp[u][1] += dp[v][0];
			dp[u][0] += max(dp[v][0], dp[v][1]);
		}
	});
	auto push = y_combinator([&](auto self, int u, int pu, bool take) -> void {
		if (take) ans.pb(u);
		for (auto &v : g[u]) {
			if (v == pu) continue;
			if (take) {
				self(v, u, 0);
			}else{
				bool fl = (dp[v][1] > dp[v][0] ? 1 : 0);
				self(v, u, fl);
			}
		}
	});
	dfs(0, -1);
	cout << max(dp[0][1], dp[0][0]) << '\n';
	bool fl = (dp[0][1] > dp[0][0] ? 1 : 0);
	push(0, -1, fl);
	sort(all(ans));
	for (auto &e : ans) cout << e + 1 << ' ';
	cout << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
