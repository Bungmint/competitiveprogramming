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
    string s;
    cin >> s;
    int n = sz(s);
    vector<vi> dp(n, vi(n));
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            if (len == 2) {
                dp[l][r] = (s[l] == s[r] ? 0 : 1);
            }else if (len % 2 == 1) {
                int best = 1, alph = INF;
                if (dp[l + 1][r] == -1) {
                    best = -1;
                }else if (dp[l + 1][r] == 0) {
                    best = 0;
                    ckmin(alph, s[l] - 'a'); 
                }

                if (dp[l][r - 1] == -1) {
                    best = -1;
                }else if (dp[l][r - 1] == 0) {
                    if (best != -1) {
                        best = 0;
                        ckmin(alph, s[r] - 'a');
                    }
                }

                dp[l][r] = (best == 0 ? alph + 26 : best);
            }else{
                int best = -1;
                if (dp[l + 1][r] == 1) {
                    best = 1;
                }else if (dp[l + 1][r] > 0) {
                    int cur = s[l] - 'a';
                    if (cur < dp[l + 1][r] - 26) best = 1;
                    else best = 0;
                }
                if (dp[l][r - 1] == 1) {
                    best = 1;
                }else if (dp[l][r - 1] > 0) {
                    int cur = s[r] - 'a';
                    if (cur < dp[l][r - 1] - 26) best = 1;
                    else ckmax(best, 0);
                }
                dp[l][r] = best;
            }
        } 
    }
    if (dp[0][n - 1] > 0) cout << "Alice\n";
    else if (dp[0][n - 1] == 0) cout << "Draw\n";
    else cout << "Bob\n";
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

