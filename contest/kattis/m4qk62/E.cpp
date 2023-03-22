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

constexpr int MOD = 10007;
constexpr int MAXN = 1e8;
uint16_t nonprime[MAXN];
uint16_t inv[MOD];

void precalc() {
    inv[1] = 1;
    for (int i = 2; i < MOD; i++) {
        inv[i] = 1LL * (MOD - (MOD / i)) * inv[MOD % i] % MOD;
    }
    nonprime[0] = nonprime[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        nonprime[i] = nonprime[i - 1];
        if (i % MOD == 0) {
            nonprime[i] = 1LL * nonprime[i] * (i / MOD) % MOD;
        }else{
            nonprime[i] = 1LL * nonprime[i] * i % MOD; 
        }
    }
} 
int vp(int n) {
    return n / MOD;
}
int binom(int n, int k) {
    if (k < 0 || n < 0 || n < k) return 0;
    if (vp(n) > vp(n - k) + vp(k)) return 0;
    return (1LL * nonprime[n] * inv[nonprime[k]] * inv[nonprime[n - k]]) % MOD;
}
int calc(int x1, int y1, int x2, int y2) {
    if (x1 > x2 || y1 > y2) return 0;
    int h = x2 - x1, w = y2 - y1;
    if (2 * w - h < 0 || 2 * h - w < 0) return 0;
    if ((2 * w - h) % 3 || (2 * h - w) % 3) return 0;
    int a = (2 * w - h) / 3, b = (2 * h - w) / 3;
    dbg(a, b);
    return binom(a + b, b);
}

void solve() {
    int H, W, R;
    cin >> H >> W >> R;
    vpi rock(R);
    vi dp(R + 1);
    for (auto &[x, y] : rock) cin >> x >> y;
    sort(all(rock));
    rock.pb({H, W});
    for (int i = 0; i <= R; i++) {
        auto &[x, y] = rock[i];
        dp[i] = calc(1, 1, x, y);
        dbg(dp[i]);
        for (int j = 0; j < i; j++) {
            dp[i] = (dp[i] - dp[j] * calc(rock[j].fi, rock[j].se, x, y)) % MOD; 
            dp[i] += MOD;
            dp[i] %= MOD;
        }
    }
    cout << dp[R] << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    precalc();
	int testcase = 1;
	cin >> testcase;
    for (int i = 1; i <= testcase; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

