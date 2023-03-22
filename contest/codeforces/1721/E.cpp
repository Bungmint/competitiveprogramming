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
    int n, q;
    cin >> s >> q;
    n = sz(s);
    vector<vi> dp(n, vi(26, 0));
    vi pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        if (j) {
            if (dp[j - 1][s[i] - 'a']) {
                pi[i] = 1 + dp[j - 1][s[i] - 'a'];
            }else if (s[0] == s[i]) {
                pi[i] = 1;
            }else{
                pi[i] = 0; 
            }
        }else{
            if (s[0] == s[i]) {
                pi[i] = 1;
            }
        }
        dp[i - 1][s[i] - 'a'] = i;
        for (int ch = 0; ch < 26 && pi[i]; ch++) {
            dp[i][ch] = dp[pi[i] - 1][ch];
        }
    }
    dbg(pi);
    for (int id = 0; id < q; id++) {
        string t;
        cin >> t;
        int m = sz(t);
        int x = dp[n - 1][t[0] - 'a'];
        for (int i = 0; i < m; i++) {
            int j = pi.back();
            pi.pb(0);
            dp.pb(vi(26));
            if (j) {
                // dbg(dp[j - 1]);
                if (dp[j - 1][t[i] - 'a']) {
                    pi[i + n] = 1 + dp[j - 1][t[i] - 'a'];
                }else if (s[0] == t[i]) {
                    pi[i + n] = 1;
                }else{
                    pi[i + n] = 0; 
                }
            }else{
                if (s[0] == t[i]) {
                    pi[i + n] = 1;
                }
            }
            s.pb(t[i]);    
            dp[i + n - 1][s.back() - 'a'] = i + n;
            for (int ch = 0; ch < 26 && pi[i + n]; ch++) {
                dp[i + n][ch] = dp[pi[i + n] - 1][ch];
            }
            cout << pi.back() << " \n"[i == m - 1];
        }
        for (int i = 0; i < m; i++) {
            s.pop_back(), dp.pop_back(), pi.pop_back();
        }
        dp[n - 1][t[0] - 'a'] = x;
    }
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

