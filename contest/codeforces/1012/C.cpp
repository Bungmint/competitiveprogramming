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

void solve() {
	int n, k; cin >> n;
	vi a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];
	if (n == 1) {
		cout << 0 << '\n';
		return;
	}
	k = (n + 1)/2;
	vector<vi> dp(n + 1, vi(k + 1, 2*INF));
	vi cur_min(n + 1, 2*INF);
	vi ans(n + 1, 2*INF);
	dp[0][0] = 0;
	cur_min[0] = 0;
	for (int i = 1; i <= n; i++) {
		if (i == 1) {
			if (a[i] > a[i + 1]) dp[1][1] = dp[1][0] = 0;
			else{
				dp[1][1] = a[i + 1] - a[i] + 1;
				dp[1][0] = 0;
			}
		}else if (i == n) {
			for (int j = 1; j <= k; j++) {
				// i-2
				if (j > 1) {
					int t = 0;
					if (a[i-2] > a[i]) {
						if (a[i-2] > a[i-1]) t = max(0, a[i-1]-a[i]+1);
						else t = max(0, a[i-2]-a[i]);
					}
					ckmin(dp[i][j], dp[i-2][j-1] + t);
				}
				// else
				int t = max(0, a[i-1]-a[i]+1);
				ckmin(dp[i][j], cur_min[j - 1] + t);
			}
		}else{
			for (int j = 1; j <= k; j++) {
				// i-2
				if (j > 1) {
					int t = max(0, a[i+1]-a[i]+1);
					if (a[i-2] > a[i]) {
						if (a[i-2] > a[i-1]) t += max(0, a[i-1]-a[i]+1);
						else t += max(0, a[i-2]-a[i]);
					}
					ckmin(dp[i][j], dp[i-2][j-1] + t);
				}
				// else
				int t = max(0, a[i+1]-a[i]+1) + max(0, a[i-1]-a[i]+1);
				ckmin(dp[i][j], cur_min[j - 1] + t);
			}
		}
		if (i >= 2) {
			for (int j = 0; j <= k; j++) {
				ckmin(cur_min[j], dp[i - 2][j]);
			}
		}
	}
	int mi = 2*INF;
	for (int i = k; i >= 1; i--) {
		for (int j = 1; j <= n; j++) ckmin(mi, dp[j][i]);
		ans[i] = mi;
	}

	for (int i = 1; i <= k; i++) {
		cout << ans[i] << " \n"[i == k];
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
