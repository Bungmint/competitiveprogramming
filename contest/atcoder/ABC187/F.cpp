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

bitset<1 << 18> is_good{};
int dp[1 << 18];

void solve() {
	int n, m;
	cin >> n >> m;
	vector<vi> g(n, vi(n));
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v, u--, v--;
		g[u][v] = g[v][u] = 1;
	}
	for (int mask = 1; mask < (1 << n); mask++) {
		int cnt = __builtin_popcount(mask);
		if (cnt == 1) is_good[mask] = 1;
		else{
			int la = __builtin_ctz(mask);
			int prev_mask = mask ^ (1 << la);
			bool ok = 1;
			for (int i = 0; i < n; i++) {
				if ((prev_mask & (1 << i)) && !g[i][la]) {
					ok = 0;
					break;
				}
			}
			is_good[mask] = ok && is_good[prev_mask];
		}
	}
	for (int mask = 0; mask < (1 << n); mask++) dp[mask] = __builtin_popcount(mask);
	for (int mask = 1; mask < (1 << n); mask++) {
		if (is_good[mask]) {
			int neg = mask ^ ((1 << n) - 1);
			for (int s = neg; ; s = (s - 1) & neg) {
				if (dp[mask ^ s] > dp[s] + 1) dp[mask ^ s] = dp[s] + 1;
				if (s == 0) break;
			}
		}
	} 
	cout << dp[(1 << n) - 1] << '\n';
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
