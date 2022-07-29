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

constexpr int M = 2e5 + 100;
int ans, a[M];
pair<set<int>, int> paths[M];
vi g[M];

void dfs(int u, int pu = -1) {
	int mx = 0, bigC = -1;
	for (auto &v : g[u]) {
		if (v != pu) {
			dfs(v, u);
			if (ckmax(mx, sz(paths[v].fi))) {
				bigC = v;
			}
		}
	}
	if (bigC == -1) {
		paths[u] = {{a[u]}, 0};
		return;
	}
	paths[u].swap(paths[bigC]);
	paths[u].se ^= a[u];
	paths[u].fi.insert(a[u] ^ paths[u].se);
	bool remove = 0;
	for (auto &v : g[u]) {
		if (v == pu || v == bigC) continue;
		if (remove) break;
		for (auto &e : paths[v].fi) {
			if (paths[u].fi.count(e ^ paths[v].se ^ paths[u].se)) {
				remove = 1;
				break;
			}
		} 
		for (auto &e : paths[v].fi) {
			paths[u].fi.insert(e ^ paths[v].se ^ paths[u].se ^ a[u]);
		}
	}
	if (paths[u].fi.count(paths[u].se)) remove = 1;
	if (remove) {
		ans++;
		pair<set<int>, int>().swap(paths[u]);
	}
}

void solve() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		u--, v--;
		g[u].pb(v), g[v].pb(u);
	}
	dfs(0, -1);
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
