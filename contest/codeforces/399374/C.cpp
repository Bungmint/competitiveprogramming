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
#define eb emplace_back
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

void solve() {
	int n, m;
	ll k;
	cin >> n >> m >> k;
	vi a(n);
	vpi es(m);
	for (auto &ee : a) cin >> ee;
	for (auto &[u, v] : es) cin >> u >> v, u--, v--;
	int L = *min_element(all(a)), R = *max_element(all(a)), ans = -1;
	while (L <= R) {
		int M = (L + R) / 2;
		vector<vi> g(n);
		vector<bool> good(n), vis(n);
		vi color(n), topsort, dist(n, 1);
		for (int i = 0; i < n; i++) {
			if (a[i] <= M) good[i] = 1;
		}
		for (auto &[u, v] : es) {
			if (a[u] <= M && a[v] <= M) g[u].pb(v);
		}
		auto cycle = y_combinator([&](auto self, int u) -> bool {
			color[u] = 1;
			bool res = 0;
			for (auto &v : g[u]) {
				if (color[v] == 0) {
					res |= self(v);
				}else if (color[v] == 1) {
					res = 1;
				}
			}
			color[u] = 2;
			return res;
		});
		auto dfs = y_combinator([&](auto self, int u) -> void {
			vis[u] = 1;
			for (auto &v : g[u]) {
				if (!vis[v]) self(v);
			}
			topsort.pb(u);
		});
		bool ok = 0;
		for (int i = 0; i < n; i++) {
			if (good[i] && color[i] != 2) ok |= cycle(i);
			if (good[i] && !vis[i]) dfs(i);
		}
		for (auto &e : topsort) {
			for (auto &f : g[e]) {
				ckmax(dist[e], dist[f] + 1);
			}
		}
		ok |= *max_element(all(dist)) >= k;
		if (ok) {
			ans = M;
			R = M - 1;
		}else{
			L = M + 1;
		}
	}
	cout << ans << '\n';
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
