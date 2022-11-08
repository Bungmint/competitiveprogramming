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

constexpr int MOD = 1e9 + 7;

void add(int& a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
}

int dp[2][1001][1001];

void solve() {
	int N;
	cin >> N;
	vi h(N);
	for (int &e : h) cin >> e;
	if (N & 1) {
		int current = 0;
		for (int targ = 0; targ <= h[0]; targ++) {
			for (int i = targ; i <= h[0]; i++) dp[current][targ][i] = 1;
		}
		for (int i = 1; i < N; i++) {
			memset(dp[current ^ 1], 0, sizeof(int)*1001*1001);
			for (int targ = 0; targ <= h[i]; targ++) {
				int res = 0;
				for (int cur = h[i]; cur >= targ; cur--) {
					add(res, dp[current][targ][targ + h[i] - cur]);
					add(dp[current ^ 1][targ][cur], res);
				}
			}
			current ^= 1;
		}
		int ans = 0;
		for (int i = 0; i <= 1000; i++) {
			if (dp[current][i][i]) dbg(i, dp[current][i][i]);
			add(ans, dp[current][i][i]);
		}
		cout << ans << '\n';
	}else{
		int current = 0;
		for (int targ = 0; targ <= 0; targ++) {
			for (int i = targ; i <= h[0]; i++) dp[current][targ][i] = 1;
		}
		for (int i = 1; i < N; i++) {
			memset(dp[current ^ 1], 0, sizeof(int)*1001*1001);
			for (int targ = 0; targ <= 0; targ++) {
				int res = 0;
				for (int cur = h[i]; cur >= targ; cur--) {
					add(res, dp[current][targ][targ + h[i] - cur]);
					add(dp[current ^ 1][targ][cur], res);
				}
			}
			current ^= 1;
		}
		int ans = 0;
		for (int i = 0; i <= 0; i++) {
			if (dp[current][i][i]) dbg(i, dp[current][i][i]);
			add(ans, dp[current][i][i]);
		}
		cout << ans << '\n';
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
