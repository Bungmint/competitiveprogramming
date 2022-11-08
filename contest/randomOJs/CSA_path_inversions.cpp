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

constexpr int NAX = 1e5 + 110, MOD = 1e9 + 7;
int n, k, d = 1;
int s[NAX], cnt[NAX];
bool vis[NAX];
vi g[NAX];
ll ans;

int binom(int nn) { return (1LL*nn*(nn-1)/2LL) % MOD; }
int subtree(int u, int pu = -1) {
	s[u] = 1;
	for (auto &v : g[u]) {
		if (vis[v] || v == pu) continue;
		s[u] += subtree(v, u);
	}
	return s[u];
}
int centroid(int u, int SZ, int pu = -1) {
	for (auto &v : g[u]) {
		if (vis[v] || v == pu) continue;
		if (2*s[v] > SZ) return centroid(v, SZ, u);
	}
	return u;
}
void dfs_cnt(int u, int pu = -1) {
	for (auto &v : g[u]) {
		if (v == pu || vis[v]) continue;
		d++; dfs_cnt(v, u); d--;
	}
	if (d <= k) (ans += ((1LL*binom(k+1)*cnt[k-d]) % MOD)) %= MOD;
}
void dfs_add(int u, int pu = -1, int x = 1) {
	for (auto &v : g[u]) {
		if (v == pu || vis[v]) continue;
		d++; dfs_add(v, u, x); d--;
	}
	if (d <= k) cnt[d] += x;
}
void cd(int u) {
	u = centroid(u, subtree(u));
	cnt[0] = 1;
	for (auto &v : g[u]) {
		if (vis[v]) continue;
		dfs_cnt(v, u);
		dfs_add(v, u);
	}
	for (auto &v : g[u]) {
		if (vis[v]) continue;
		dfs_add(v, u, -1);
	}
	vis[u] = 1;
	for (auto &v : g[u]) {
		if (!vis[v]) cd(v);
	}
}


void solve() {
	cin >> n >> k;
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		u--, v--;
		g[u].pb(v), g[v].pb(u);
	}
	cd(0);
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
