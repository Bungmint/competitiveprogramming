// Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

#pragma region TEMPLATE

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

#pragma endregion TEMPLATE

pll operator+(const pll& a, const pll& b) {
	return {a.fi+b.fi, a.se+b.se};
}

void solve() {
	int n; cin >> n;
	vector<vi> adj(n);
	vi deg(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v, u--, v--;
		adj[u].pb(v), adj[v].pb(u);
		deg[u]++, deg[v]++;
	}
	if (n == 2) {
		cout << 2 << ' ' << 2 << '\n';
		cout << 1 << ' ' << 1 << '\n';
		return;
	}
	vpl f(n), g(n);
	vi ans(n);
	ll sum{LINF}; int cnt{};
	auto dfs = y_combinator([&](auto self, int u = 0, int pu = -1) -> void {
		f[u] = {1, sz(adj[u])};
		g[u] = {0, 1};
		for (auto &v : adj[u]) {
			if (v == pu) continue;
			self(v, u);
			f[u] = f[u] + g[v];
			if (f[v].fi != g[v].fi) {
				g[u] = g[u] + (f[v].fi > g[v].fi ? f[v] : g[v]);
			}else{
				g[u] = g[u] + (f[v].se < g[v].se ? f[v] : g[v]);
			}
		}
	});
	auto recover = y_combinator([&](auto self, bool fl, int u = 0, int pu = -1) -> void {
		if (fl) ans[u] = sz(adj[u]);
		else ans[u] = 1;
		for (auto &v : adj[u]) {
			if (v == pu) continue;
			if (fl) {
				self(0, v, u);
			}else{
				if (f[v].fi != g[v].fi) {
					self((f[v].fi > g[v].fi), v, u);
				}else{
					self((f[v].se < g[v].se), v, u);
				}
			}
		}
	});
	dfs();
	cnt = max(f[0].fi, g[0].fi);
	if (cnt == f[0].fi) ckmin(sum, f[0].se);
	if (cnt == g[0].fi) ckmin(sum, g[0].se);
	if (f[0] == make_pair((ll)cnt, (ll)sum)) {
		recover(1);
	}else recover(0);
	cout << cnt << ' ' << sum << '\n';
	for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i == n - 1];
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
