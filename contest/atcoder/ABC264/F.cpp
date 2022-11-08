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

ll dp[2][2][2011][2011]; // flip row, flip col, row, col
bool val[2011][2011];

void solve() {
	int H, W;
	cin >> H >> W;
	vi rcost(H), ccost(W);
	for (auto &e : rcost) cin >> e;
	for (auto &e : ccost) cin >> e;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			char c;
			cin >> c;
			val[i][j] = c - '0';
			for (int k = 0; k < 2; k++) for (int l = 0; l < 2; l++) {
				dp[k][l][i][j] = LINF;
			}
			if (i == 0 && j == 0) {
				dp[0][0][i][j] = 0;
				dp[1][0][i][j] = rcost[i];
				dp[0][1][i][j] = ccost[j];
				dp[1][1][i][j] = rcost[i] + ccost[j];
			}else if (i == 0) {
				for (int rflip = 0; rflip < 2; rflip++) {
					for (int cflip = 0; cflip < 2; cflip++) {
						if ((val[i][j - 1] ^ cflip) == val[i][j]) {
							ckmin(dp[rflip][0][i][j], dp[rflip][cflip][i][j - 1]);
						}else{
							ckmin(dp[rflip][1][i][j], dp[rflip][cflip][i][j - 1] + ccost[j]);
						}
					}
				}
			}else if (j == 0) {
				for (int rflip = 0; rflip < 2; rflip++) {
					for (int cflip = 0; cflip < 2; cflip++) {
						if ((val[i - 1][j] ^ rflip) == val[i][j]) {
							ckmin(dp[0][cflip][i][j], dp[rflip][cflip][i - 1][j]);
						}else{
							ckmin(dp[1][cflip][i][j], dp[rflip][cflip][i - 1][j] + rcost[i]);
						}
					}
				}
			}else{
				for (int rflip = 0; rflip < 2; rflip++) {
					for (int cflip = 0; cflip < 2; cflip++) {
						if ((val[i][j - 1] ^ cflip) == val[i][j]) {
							ckmin(dp[rflip][0][i][j], dp[rflip][cflip][i][j - 1]);
						}else{
							ckmin(dp[rflip][1][i][j], dp[rflip][cflip][i][j - 1] + ccost[j]);
						}
					}
				}
				for (int rflip = 0; rflip < 2; rflip++) {
					for (int cflip = 0; cflip < 2; cflip++) {
						if ((val[i - 1][j] ^ rflip) == val[i][j]) {
							ckmin(dp[0][cflip][i][j], dp[rflip][cflip][i - 1][j]);
						}else{
							ckmin(dp[1][cflip][i][j], dp[rflip][cflip][i - 1][j] + rcost[i]);
						}
					}
				}
			}
		}
	}
	ll ans = LINF;
	for (int rflip = 0; rflip < 2; rflip++) {
		for (int cflip = 0; cflip < 2; cflip++) {
			ckmin(ans, dp[rflip][cflip][H - 1][W - 1]);
		}
	}
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
