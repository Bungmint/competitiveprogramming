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

constexpr int MOD = 1e9;
constexpr int MAXN = 1100;
int dp[MAXN][4][6];
map<int, ar<int, 3>> m = {{0, {0, 1, 2}}, {1, {0, 2, 1}}, 
    {2, {1, 0, 2}}, {3, {1, 2, 0}}, {4, {2, 0, 1}}, {5, {2, 1, 0}}};

int get_perm_id(int a, int b, int c) {
    for (auto &[id, v] : m) {
        if (v[0] == a && v[1] == b) return id;
    }
    return -1;
}

void solve() {
    int n;
    cin >> n;
    dp[0][0][0] = 1;
    dp[0][0][1] = 1;
    dp[0][1][0] = 1;
    dp[0][2][0] = dp[0][2][1] = 1;
    dp[0][3][2] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            if (j == 3) {
                for (int k = 0; k < 3; k++) {
                    for (int perm_id = 0; perm_id < 6; perm_id++) {
                        auto [a, b, c] = m[perm_id];
                        if (abs(k - a) > 1) continue;
                        int id = get_perm_id(a, b, c);
                        // attach all three
                        if ((a < b && b < c) || (a > b && b > c)) {
                            dp[i][3][c] += dp[i - 1][3][k];
                            dp[i][3][c] %= MOD;
                        }
                        // attach two
                        if (abs(a - b) == 1) {
                            dp[i][1][id] += dp[i - 1][3][k];
                            dp[i][1][id] %= MOD;
                        }
                        // attach one and split the two
                        dp[i][0][id] += dp[i - 1][3][k];
                        dp[i][0][id] %= MOD;
                        // attach one, two block
                        if (abs(b - c) == 1) {
                            dp[i][2][id] += dp[i - 1][3][k];
                            dp[i][2][id] %= MOD;
                        }
                    }
                }
            } else {
                for (int perm_id = 0; perm_id < 6; perm_id++) {
                    for (int cur = 0; cur < 6; cur++) {
                        auto [aj, bj, cj] = m[perm_id];
                        auto [a, b, c] = m[cur];
                        if (j == 0) {
                            if (abs(aj - a) <= 1 && abs(bj - a) <= 1 &&
                                abs(bj - b) <= 1 && abs(cj - b) <= 1 && 
                                abs(cj - c) <= 1) {
                                dp[i][3][c] += dp[i - 1][j][perm_id];
                                dp[i][3][c] %= MOD;
                            }
                        } else if (j == 1) {
                            if (abs(bj - a) <= 1 && abs(cj - a) <= 1 &&
                                abs(cj - b) <= 1) {
                                dp[i][1][cur] += dp[i - 1][j][perm_id];
                                dp[i][1][cur] %= MOD;
                            }
                            if (abs(a - b) <= 1 && abs(bj - a) <= 1 &&
                                abs(cj - b) <= 1 && abs(cj - c) <= 1) {
                                dp[i][3][c] += dp[i - 1][j][perm_id];
                                dp[i][3][c] %= MOD;
                            }
                            if (abs(bj - a) <= 1 && abs(cj - a) <= 1 &&
                                abs(cj - b) <= 1 && abs(b - c) <= 1) {
                                dp[i][3][c] += dp[i - 1][j][perm_id];
                                dp[i][3][c] %= MOD;
                            }
                            if (abs(bj - a) <= 1 && abs(cj - b) <= 1 &&
                                abs(cj - c) <= 1) {
                                dp[i][2][cur] += dp[i - 1][j][perm_id];
                                dp[i][2][cur] %= MOD;
                            }
                        } else if (j == 2) {
                            if (abs(aj - a) <= 1 && abs(bj - a) <= 1 &&
                                abs(cj - b) <= 1) {
                                dp[i][1][cur] += dp[i - 1][j][perm_id];
                                dp[i][1][cur] %= MOD;
                            }
                            if (abs(a - b) <= 1 && abs(aj - a) <= 1 &&
                                abs(bj - b) <= 1 && abs(cj - c) <= 1) {
                                dp[i][3][c] += dp[i - 1][j][perm_id];
                                dp[i][3][c] %= MOD;
                            }
                            if (abs(aj - a) <= 1 && abs(bj - a) <= 1 &&
                                abs(cj - b) <= 1 && abs(b - c) <= 1) {
                                dp[i][3][c] += dp[i - 1][j][perm_id];
                                dp[i][3][c] %= MOD;
                            }
                            if (abs(aj - a) <= 1 && abs(bj - b) <= 1 &&
                                abs(cj - c) <= 1) {
                                dp[i][2][cur] += dp[i - 1][j][perm_id];
                                dp[i][2][cur] %= MOD;
                            } 
                        }
                    }
                }
            }
        }
    }

    cout << dp[n - 1][3][2] << '\n';
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

