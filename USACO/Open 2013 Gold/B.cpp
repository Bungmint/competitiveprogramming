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
 * Description: Performs range prefix sum queries and point updates. lower_bound returns the first prefix sum >= v
 * Source: Own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=693
 * Time Complexity: O(log n) for query and update
 * 0-indexing
 */

template <typename T>
struct BIT {
	int N; vector<T> bit;
	BIT(int n) : N(n), bit(n + 1) {}
	void upd(int id, T v) {
		for (id++; id <= N; id += id & -id)
			bit[id] += v;
	}
	ll query(int id) {
		ll res = 0;
		for (id++; id > 0; id -= id & -id)
			res += bit[id];
		return res;
	}
	ll query(int l, int r) {
		return l > r ? 0 : query(r) - query(l - 1);
	}
	T lower_bound(T v) {
		int id = 0;
		T sum = 0;
		int lg = 31 - __builtin_clz(N);
		for (int j = lg; ~j; j--)
		{
			if (id + (1 << j) <= N && sum + bit[id + (1 << j)] < v)
			{
				id += (1 << j);
				sum += bit[id];
			}
		}
		return id;
	}
};

const int MX = 1e5 + 100;
vector<pair<int, int>> adj[MX];
ll ans{};
int s[MX], n, d;
bool vis[MX];
int cur[MX * 2];
int zero_freq[MX * 2];
int freq[MX * 2];

int subtree(int u, int pu = -1) {
	s[u] = 1;
	for (auto &[v, fl] : adj[u]) {
		if (v == pu || vis[v]) continue;
		s[u] += subtree(v, u);
	}
	return s[u];
}
int centroid(int u, int tot, int pu = -1) {
	for (auto &[v, fl] : adj[u]) {
		if (v != pu && !vis[v] && 2 * s[v] > tot) {
			return centroid(v, tot, u);
		}
	}
	return u;
}
void dfs_add_ans(int u, int pu) {
	cur[d + MX]++;
	if (d == 0 && cur[MX] >= 2) ans++;
	ans += zero_freq[-d + MX];
	if (cur[d + MX] > 1) {
		if (d > 0 && cur[d + MX] > 1) {
			ans += freq[-d + MX];
		}else if (d < 0 && cur[d + MX] > 1) {
			ans += freq[-d + MX];
		}
	}
	for (auto &[v, fl] : adj[u]) {
		if (vis[v] || v == pu) continue;
		d += fl;
		dfs_add_ans(v, u);
		d -= fl;
	}
	cur[d + MX]--;
}
void dfs_add(int u, int pu, const int x) {
	cur[d + MX]++;
	if (cur[MX + d] > 1 || d == 0) {
		zero_freq[d + MX] += x;
	}else{
		freq[d + MX] += x;
	}
	for (auto &[v, fl] : adj[u]) {
		if (vis[v] || v == pu) continue;
		d += fl;
		dfs_add(v, u, x);
		d -= fl;
	}
	cur[d + MX]--;
}
void cd(int u) {
	u = centroid(u, subtree(u));
	for (auto &[v, fl] : adj[u]) {
		if (vis[v]) continue;
		d += fl;
		dfs_add_ans(v, u);
		dfs_add(v, u, 1);
		d -= fl;
	}
	for (auto &[v, fl] : adj[u]) {
		if (vis[v]) continue;
		d += fl;
		dfs_add(v, u, -1);
		d -= fl;
	}
	vis[u] = 1;
	for (auto &[v, fl] : adj[u]) {
		if (!vis[v]) cd(v);
	}
}

void solve() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v, fl;
		cin >> u >> v >> fl;
		fl = (fl ? 1 : -1);
		u--, v--;
		adj[u].pb({v, fl}), adj[v].pb({u, fl});
	}
	cd(0);
	cout << ans << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	#ifndef LOCAL
		freopen("yinyang.in", "r", stdin);
		freopen("yinyang.out", "w", stdout);
	#endif
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
