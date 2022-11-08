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

/**
 * Description: Two-edge connected components
 * Source: Benq ORZ
 * Verification: 
 */

struct TwoEdgeCC {
	struct {
		vi e; void init(int n) { e = vi(n,-1); }
		int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
		bool unite(int x, int y) { // set par[y] = x
			x = get(x), y = get(y); if (x == y) return 0;
			e[x] += e[y]; e[y] = x; return 1;
		}
	} DSU;
	int N; vector<vi> adj; vi depth, par;
	vpi extra;
	void init(int _N) {
		N = _N; DSU.init(N);
		adj.resize(N), depth.resize(N), par = vi(N, -1);
	}
	void dfs(int x) {
		for (auto &t : adj[x]) if (t != par[x])
			par[t] = x, depth[t] = depth[x]+1, dfs(t);
	}
	void ae(int a, int b) {
		if (DSU.unite(a,b)) adj[a].pb(b), adj[b].pb(a); // edge of forest
		else extra.pb({a,b}); // extra edge
	}
	void ad(int a, int b) {
		while (1) {
			a = DSU.get(a), b = DSU.get(b);
			if (a == b) return;
			if (depth[a] < depth[b]) swap(a,b);
			assert(par[a] != -1 && DSU.unite(par[a], a));
		}
	}
	void gen() {
		for (int i = 0; i < N; i++) if (par[i] == -1) dfs(i); // independently for each connected component
		DSU.init(N); for (auto &t : extra) ad(t.fi,t.se); // add non-spanning edges
	}
};

void solve() {
	int n, m, s;
	cin >> n >> m;
	vector<vi> adj(n), tree(n);
	vl sum(n), w(n), dp_up(n), dp_stay(n);
	TwoEdgeCC twocc;
	twocc.init(n);
	for (auto &v : w) cin >> v;
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		u--, v--;
		twocc.ae(u, v);
		adj[u].pb(v), adj[v].pb(u);
	}
	cin >> s; s--;
	twocc.gen();
	vi cnt(n);
	set<pii> edges;
	for (int i = 0; i < n; i++) {
		int u = twocc.DSU.get(i);
		cnt[u]++, sum[u] += w[i];
		for (auto &v : adj[i]) {
			int vv = twocc.DSU.get(v);
			if (edges.count({u, vv}) || u == vv) continue;
			else edges.insert({u, vv}), edges.insert({vv, u}), tree[u].pb(vv), tree[vv].pb(u);
		}
	}
	dbg(edges);
	vector<bool> leaf(n);
	auto dfs = y_combinator([&](auto self, int u, int pu) -> void {
		ll sss{};
		bool up{};
		ll leaf_max{}, up_max{};
		for (auto &v : tree[u])	{
			if (v == pu) continue;
			self(v, u);
			if (leaf[v]) {
				ckmax(leaf_max, dp_stay[v]);
			}else{
				up = 1;
				ckmax(up_max, -(dp_up[v] - dp_stay[v]));
				sss += dp_up[v];
			}
		}
		dbg(sss, leaf_max, up_max, u);
		if (!up && cnt[u] == 1) {
			leaf[u]	= 1;
			dp_stay[u] = sum[u] + leaf_max;
		}else{
			dp_stay[u] = sss + sum[u] + max(leaf_max, up_max);
			dp_up[u] = sss + sum[u];
		}
	});
	int root = twocc.DSU.get(s);
	dfs(root, -1);
	cout << max(dp_up[root], dp_stay[root]) << '\n';
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
