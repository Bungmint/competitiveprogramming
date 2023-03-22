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

int n, m, k, p;	
ll dp[111][111][111];
ll fact[111];
ll binom[111][111];

void precalc() {
    fact[0] = fact[1] = 1;
    for (int i = 2; i < 111; i++) fact[i] = (1LL * fact[i - 1] * i) % p;
    for (int i = 0; i <= 101; i++) {
        binom[i][0] = binom[i][i] = 1;
        for (int j = 1; j < i; j++) {
            binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % p;
        }
    }
}
ll calc(int len, int cur_m, int cnt) {
    ll &res = dp[len][cur_m][cnt];
    dbg(len, cur_m, cnt, res);
    if (res != -1) {
        return res;
    } 
    res = 0;
    if (len == 0) {
        res = 1;
        return res;
    }
    if (cur_m == 1) {
        // dbg(cnt);
        res = (cnt == 1 ? fact[len] : 0);
        return res;
    }
    for (int l = 0; l < len; l++) {
        ll cur = 0;
        for (int x = max(0, cnt + l + 1 - len); x <= min(cnt, l); x++) {
            cur += 1LL * calc(l, cur_m - 1, x) * calc(len - 1 - l, cur_m - 1, cnt - x) % p;
            cur %= p;
        }
        res += 1LL * binom[len - 1][l] * cur % p;
        res %= p;
    } 
    return res;
}

void solve() {
    cin >> n >> m >> k >> p;
    precalc();
    memset(dp, -1, sizeof(dp));
    cout << calc(n, m, k) << '\n';
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

