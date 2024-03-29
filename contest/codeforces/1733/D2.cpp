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
    int n, x, y;
    cin >> n >> x >> y;
    string s, t;
    cin >> s >> t;
    vi ind;
    for (int i = 0; i < n; i++) if (s[i] != t[i]) ind.pb(i);
    if (sz(ind) & 1) {
        cout << -1 << '\n';
        return;
    }
    if (sz(ind) == 0) {
        cout << 0 << '\n';
        return;
    }
    if (x >= y) {
        ll ans = 0;
        if (sz(ind) == 2 && ind[0] == ind[1] - 1) {
            ans = min(2 * y, x);
        }else{
            ans = 1LL * (sz(ind) / 2LL) * y;
        }
        cout << ans << '\n';	
    }else{
        int k = sz(ind);
        vector<vl> dp(k + 1, vl(k / 2 + 1, LINF));
        dp[0][0] = dp[1][0] = 0;
        for (int i = 2; i <= k; i++) {
            for (int j = 0; j <= k / 2; j++) dp[i][j] = dp[i - 1][j];
            for (int j = 0; j < k / 2; j++) {
                ckmin(dp[i][j + 1], dp[i - 2][j] + 1LL * x * (ind[i - 1] - ind[i - 2]));
            }
        }
        ll ans = LINF;
        for (int j = 0; j <= k / 2; j++) {
            ckmin(ans, dp[k][j] + 1LL * y * (k / 2 - j)); 
        }
        cout << ans << '\n';
    }
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

