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
	int n, m, q; cin >> n >> m >> q;
	const int B = sqrt(m) + 5;
	vector<vi> adj(n), adjh(n), adjl(n);
	vector<bool> big(n);
	vpi lazy(n, make_pair(-INF, -INF)), cur(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v, u--, v--;
		adj[u].pb(v), adj[v].pb(u);
	}
	for (int i = 0; i < n; i++) {
		cur[i] = {-1, i + 1};
		if (sz(adj[i]) >= B) big[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		for (auto &v : adj[i]) {
			if (big[v]) adjh[i].pb(v);
			else adjl[i].pb(v);
		}
	}
	for (int i = 0; i < q; i++) {
		int u; cin >> u; u--;
		for (auto &v : adjh[u]) {
			ckmax(cur[u], lazy[v]);
		}
		cur[u].fi = i;
		if (big[u]) {
			lazy[u] = cur[u];
		}else{
			for (auto &v : adj[u]) {
				ckmax(cur[v], cur[u]);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (auto &v : adjh[i]) {
			ckmax(cur[i], lazy[v]);
		}
		cout << cur[i].se << " \n"[i == n - 1];
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
