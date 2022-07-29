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
	int n; cin >> n;
	vector<vi> adj(n);
	vi tin(n), tout(n), depth(n);
	const int LG = 32-__builtin_clz(n);
	vector<vi> up(LG, vi(n));
	int ti{};
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		u--, v--;
		adj[u].pb(v), adj[v].pb(u);
	}
	auto dfs = y_combinator([&](auto self, int u, int pu) -> void {
		tin[u] = ti++;
		for (auto &v : adj[u]) {
			if (v == pu) continue;
			depth[v] = depth[u] + 1;
			up[0][v] = u;
			for (int j = 1; j < LG; j++) {
				up[j][v] = up[j - 1][up[j - 1][v]];
			}
			self(v, u);
		}
		tout[u] = ti - 1;
	});
	auto is_anc = [&](int u, int ch) {
		return tin[u] <= tin[ch] && tout[ch] <= tout[u];
	};
	auto find_lca = [&](int u, int v) -> int {
		if (depth[u] < depth[v]) swap(u, v);
		int d = depth[u] - depth[v];
		for (int j = LG - 1; j >= 0; j--) {
			if (d>>j&1) u = up[j][u];
		}
		if (u == v) return u;
		for (int j = LG-1; j >= 0; j--) {
			if (up[j][u] != up[j][v]) {
				u = up[j][u], v = up[j][v];
			}
		}
		return up[0][u];
	};
	auto cmp = [&](int i, int j) {
		return tin[i] < tin[j];
	};
	dfs(0, -1);
	int q; cin >> q;
	for (int qq = 0; qq < q; qq++) {
		int k; cin >> k;
		vi a(k);
		for (auto &e : a) cin >> e, e--;
		set<int> st(all(a));
		vi los;
		int hi{}, dd = INF;
		for (int i = 0; i < k; i++) {
			if (ckmin(dd, depth[a[i]])) hi = a[i];
		}
		for (int iter = 0; iter < 2 && sz(st); iter++) {
			int lo = -1, d = -1;
			for (auto &u : st) {
				if (ckmax(d, depth[u])) lo = u;
			}
			los.pb(lo);
			set<int> nxt;
			for (auto &u : st) {
				if (!is_anc(u, lo)) nxt.insert(u); 
			}
			swap(nxt, st);
		}
		if (sz(st)) {
			cout << "NO\n";
		}else{
			if (sz(los) == 1) {
				cout << "YES\n";
			}else{
				int x = los[0], y = los[1];
				cout << (depth[find_lca(x, y)] <= dd ? "YES" : "NO") << '\n';
			}
		}
	}
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
