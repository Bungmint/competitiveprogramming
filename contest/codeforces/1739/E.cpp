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

void solve() {
    int n;
    cin >> n;
    vector<vi> dp(2, vi(n + 1, INF));
    vector<string> grid(2);
    int total = 0;
    for (auto &e : grid) cin >> e, total += count(all(e), '1');
    dp[0][n] = dp[1][n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (grid[0][i] == grid[1][i]) {
            if (grid[0][i] == '0') {
                dp[0][i] = dp[0][i + 1];
                dp[1][i] = dp[1][i + 1];
            } else {
                for (int r = 0; r < 2; r++) {
                    if (i + 1 < n && grid[r][i + 1] == '1') {
                        dp[r][i] = 1 + min(dp[r][i + 1], dp[r ^ 1][i + 2]);
                    } else {
                        dp[r][i] = min(1 + dp[r][i + 1], dp[r ^ 1][i + 1]);
                    }
                } 
            }
        } else {
            int r = (grid[0][i] == '1' ? 0 : 1);
            dp[r][i] = dp[r][i + 1];
            if (i + 1 < n && grid[r ^ 1][i + 1] == '1') {
                dp[r ^ 1][i] = 1 + min(dp[r ^ 1][i + 1], dp[r][i + 2]); 
            } else {
                dp[r ^ 1][i] = min(1 + dp[r ^ 1][i + 1], dp[r][i + 1]);
            }
        }
        dbg(dp[0][i], dp[1][i], i);
    }
    cout << total - dp[0][0] << '\n';
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

