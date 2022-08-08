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

/*
 * Description: Disjoint Set Union with both path compression and size heuristic
 * Source: USACO Guide/Benq
 * Verification:
 * Time complexity: amortized O(\alpha(n)) updates/queries
 */

struct DSU {
	vi e;
	DSU(int N) { e = vi(N, -1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool same_set(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) {
		x = get(x), y = get(y);
		if (x == y) return false;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
		return true;
	}
};

struct Edge {
	int u{}, v{}, c{};
	bool operator<(const Edge& o) const {
		return c < o.c;
	}
};

ll sum[25];
int cc{}, root{};

void solve() {
	int n, m, k; cin >> n >> m >> k;
	vi p(n);
	vector<Edge> all_edges(m), mr(k), tree_edges, extra;
	DSU dsu(n), tree(n), comp(n);
	for (int i = 0; i < m; i++) {
		auto &[u, v, c] = all_edges[i];
		cin >> u >> v >> c; u--, v--;
	}
	for (int i = 0; i < k; i++) {
		auto &[u, v, c] = mr[i];
		cin >> u >> v; u--, v--;
		dsu.unite(u, v);
	}
	for (int i = 0; i < n; i++) cin >> p[i];
	sort(all(all_edges));
	for (auto &e : all_edges) {
		if (tree.unite(e.u, e.v)) tree_edges.pb(e);
	}
	for (auto &e : tree_edges) {
		if (!dsu.unite(e.u, e.v)) extra.pb(e);
		else comp.unite(e.u, e.v);
	}
	vi id(n);
	vector<bool> vis(n);
	for (int i = 0; i < n; i++) {
		int r = comp.get(i);
		if (!vis[r]) {
			vis[r] = 1;
			id[r] = cc++;
		}
		sum[id[r]] += p[i];
		if (i == 0) root = id[r];
	}
	for (auto &e : mr) {
		e.u = comp.get(e.u);
		e.v = comp.get(e.v);
		e.u = id[e.u];
		e.v = id[e.v];
	}
	for (auto &e : extra) {
		e.u = comp.get(e.u);
		e.v = comp.get(e.v);
		e.u = id[e.u];
		e.v = id[e.v];
	}
	ll ans{};
	vector<vpi> adj(cc);
	vi depth(cc), we(cc), par(cc);
	vl peeps(cc);
	for (int mask = 0; mask < (1 << k); mask++) {
		for (int i = 0; i < cc; i++) adj[i].clear(), depth[i] = peeps[i] = 0, we[i] = INF;
		DSU small(cc);
		ll cur{};
		bool ok = 1;
		for (int i = 0; i < k; i++) {
			if (mask>>i & 1) {
				ok &= small.unite(mr[i].u, mr[i].v);
				adj[mr[i].u].pb({mr[i].v, 1});
				adj[mr[i].v].pb({mr[i].u, 1});
			}
		}
		if (!ok) continue;
		auto dfs = y_combinator([&](auto self, int u = root, int pu = -1) -> void {
			peeps[u] = sum[u];
			for (auto &[v, idid] : adj[u]) {
				if (v == pu) continue;
				depth[v] = depth[u] + 1;
				par[v] = u;
				self(v, u);
				if (idid) cur += peeps[v]*we[v];
				peeps[u] += peeps[v];
			}
		});
		auto dfs_min = [&](int u, int v, int c) -> void {
			if (depth[u] < depth[v]) swap(u, v);
			while (depth[u] != depth[v]) {
				if (we[u] > c) we[u] = c;
				u = par[u];
			}
			while (u != v) {
				if (we[u] > c) we[u] = c;
				if (we[v] > c) we[v] = c;
				u = par[u]; v = par[v];
			}
		};
		vector<Edge> todo;
		for (auto &[u, v, c] : extra) {
			if (!small.unite(u, v)) {
				todo.pb({u, v, c});
				// dfs_min(u, v, c);
			}else{
				adj[u].pb({v, 0});
				adj[v].pb({u, 0});
			}
		}
		dfs();
		for (auto &[u, v, c] : todo) {
			dfs_min(u, v, c);
		}
		cur = 0;
		dfs();
		ckmax(ans, cur);
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
