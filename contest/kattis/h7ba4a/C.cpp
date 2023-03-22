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


constexpr int MOD = 1001113;
int dp[111][111];
int binom[111][111];

int calc_dp(int N, int v) {
    if (N <= v) return 0;
    if (v < 0) return 0;
    if (N == 1) return 1;
    assert(N >= 0 && v >= 0);
    int& res = dp[N][v];
    if (res != -1) return res;
    res = 0;
    res = (res + calc_dp(N - 1, v)) % MOD;
    res = (res + calc_dp(N - 1, v - 1)) % MOD;
    for (int L = 1; L < N - 1; L++) {
        int R = N - 1 - L;
        int cur = 0;
        for (int j = 0; j < v; j++) {
            cur = (cur + 1LL * calc_dp(L, j) * calc_dp(R, v - 1 - j)) % MOD;
        }
        res = (res + 1LL * cur * binom[N - 1][L]) % MOD;
    }
    // if (res) dbg(N, v, res);
    return res;
}

void precalc() {
    memset(dp, -1, sizeof(dp));
    for (int n = 0; n <= 100; n++) {
        binom[n][0] = binom[n][n] = 1;
        for (int i = 1; i < n; i++) {
            binom[n][i] = binom[n - 1][i] + binom[n - 1][i - 1];
            binom[n][i] %= MOD;
        }
    }
    for (int n = 1; n <= 100; n++) {
        for (int v = 0; v < n; v++) {
            calc_dp(n, v);
        }
    }
    dbg(calc_dp(3, 0), calc_dp(3, 1));
}

void solve() {
    int k, n, v;
    cin >> k >> n >> v;
    cout << k << ' ' << calc_dp(n, v) << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    precalc();
	int testcase = 1;
	cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

