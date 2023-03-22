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

int add(int a, int b, int mod) {
    return (a + b) % mod;
}
int mul(int a, int b, int mod) {
    return 1LL * a * b % mod;
}
int bin_pow(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) res = mul(res, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return res;
}

void solve() {
    int N, MOD;
    cin >> N >> MOD;
    int f0 = 1, f1 = 2, f = f1;
    for (int i = 2; i <= N; i++) {
        int tmp = f1;
        f1 = add(f1, f0, MOD);
        f0 = tmp;
        f = f1;
    }
    int ans = f;
    if (N % 2 == 0) {
        int k = N / 2;
        int factk = 1, fact2k = 1;
        int pk = 0, p2k = 0;
        for (int i = 1; i <= k; i++) {
            int ii = i;
            while (ii % MOD == 0) ii /= MOD, pk++;
            factk = mul(factk, ii, MOD);
        }
        for (int i = 1; i <= 2 * k; i++) {
            int ii = i;
            while (ii % MOD == 0) ii /= MOD, p2k++;
            fact2k = mul(fact2k, ii, MOD);
        }
        if (p2k == 2 * pk) {
            const int INVK = bin_pow(factk, MOD - 2, MOD);
            ans = add(ans, mul(fact2k, mul(INVK, INVK, MOD), MOD), MOD);
        }
        ans -= k + 1;
        ans %= MOD;
        ans += MOD;
        ans %= MOD;
    }
    cout << ans << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

