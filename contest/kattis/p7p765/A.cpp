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



int inverse(int a, int mod) {
    a %= mod;
    int u = 0, v = 1, b = mod;
    while (a) {
        int t = b / a;
        u -= v * t, b -= a * t;
        swap(u, v), swap(a, b);
    }
    return u;
}

void solve() {
    int n, m;
    string s;
    cin >> n >> m >> s;
    vi pref(n + 1);
    vi dp(n + 1);
    vi power_10(22);
    vi power_inv_10(n + 10);
    power_10[0] = 1;
    for (int i = 1; i < 22; i++) power_10[i] = (power_10[i - 1] * 10) % m;
    int q = m, r;
    while (q % 2 == 0 || q % 5 == 0) q /= gcd(q, 10);
    r = m / q;
    power_inv_10[0] = 1, power_inv_10[1] = inverse(10, q); 
    for (int i = 2; i <= n + 5; i++) {
        power_inv_10[i] = (1LL * power_inv_10[i - 1] * power_inv_10[1]) % q;
    }
    map<int, int> dp_set;
    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] * 10 + s[i - 1] - '0';
        pref[i] %= m;
        // Manually check the previous 19 
        for (int j = max(0, i - 19); j < i; j++) {
            if ((1LL * power_10[i - j] * pref[j]) % m == pref[i]) {
                dp[i] += dp[j];
                dp[i] %= MOD;
            }
        }
        // Check dp_set for the rest
        if (pref[i] % r == 0) {
            int key = (1LL * pref[i] * power_inv_10[i]) % q;
            if (dp_set.count(key)) {
                dp[i] += dp_set[key];
                dp[i] %= MOD;
            } 
        }
        if (i - 19 >= 0) {
            (dp_set[(1LL * power_inv_10[i - 19] * pref[i - 19]) % q] += dp[i - 19]) %= MOD;
        }
    }
    cout << dp[n] << '\n';
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

