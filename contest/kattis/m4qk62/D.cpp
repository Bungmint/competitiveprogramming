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

constexpr ld EPS = 1e-9;
bool ckmin(ld& a, const ld& b) {
    return (a > b + EPS ? a = b, 1 : 0);
}

void solve() {
    int h, w;
    cin >> h >> w;
    vector<string> grid(h);
    for (auto &s : grid) cin >> s;
    ld dp[2][h + 1][w + 1];
    for (int i = 0; i < 2; i++) for (int j = 0; j <= h; j++) for (int k = 0; k <= w; k++) {
        dp[i][j][k] = INF;
    }
    dp[0][0][0] = dp[1][0][0] = 0;
    for (int r = 0; r <= h; r++) {
        for (int c = 0; c <= w; c++) {
            if (!r && !c) continue;
            if (r) {
                ckmin(dp[0][r][c], dp[0][r - 1][c] + 10); 
                ckmin(dp[0][r][c], dp[1][r - 1][c] + 10);
                if (dp[1][r - 1][c] < INF / 2 && c && grid[r - 1][c - 1] == 'O') {
                    ckmin(dp[0][r][c], dp[1][r - 1][c] + 2.5 * PI);
                }
            }
            if (c) {
                ckmin(dp[1][r][c], dp[0][r][c - 1] + 10); 
                ckmin(dp[1][r][c], dp[1][r][c - 1] + 10);
                if (dp[0][r][c - 1] < INF / 2 && r && grid[r - 1][c - 1] == 'O') {
                    ckmin(dp[1][r][c], dp[0][r][c - 1] + 2.5 * PI);
                }
            }
        }
    }
    ld ans = dp[0][h][w];
    ckmin(ans, dp[1][h][w]);
    cout << fixed << setprecision(20);
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

