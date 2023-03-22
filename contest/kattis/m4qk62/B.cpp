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
    int d, m;
    cin >> d >> m;
    string adv;
    cin >> adv;
    int tot;
    vector<int> res(21);
    if (adv[0] == 's') {
        tot = 20;
        for (int i = 1; i <= 20; i++) res[i]++;
    }else if (adv[0] == 'a') {
        tot = 400;
        for (int i = 1; i <= 20; i++) {
            for (int j = 1; j <= 20; j++) {
                res[max(i, j)]++;
            }
        }
    }else{
        tot = 400;
        for (int i = 1; i <= 20; i++) {
            for (int j = 1; j <= 20; j++) {
                res[min(i, j)]++;
            }
        }
    }
    int k; 
    cin >> k;
    vi add(k), dp(200);
    int tot_add = 1;
    for (auto &e : add) {
        string s;
        cin >> s;
        int sign = (s[0] == '+' ? 1 : -1);  
        int x = 0;
        if (sz(s) == 4) x = 10;
        else x = s.back() - '0';
        e = sign * x;
        tot_add *= x;
    }
    dp[100] = tot_add;
    for (auto &e : add) {
        if (e < 0) {
            for (int i = 0; i < 200; i++) {
                dp[i] = 0;
                for (int j = 1; j <= -e; j++) {
                    if (i + j < 200) dp[i] += dp[i + j] / -e;
                }
            } 
        }else{
            for (int i = 199; i >= 0; i--) {
                dp[i] = 0;
                for (int j = 1; j <= e; j++) {
                    if (i - j >= 0) dp[i] += dp[i - j] / e;
                }
            }
        }
    }
    ll ans = 1LL * res[20] * tot_add;
    for (int i = 2; i < 20; i++) {
        for (int j = 0; j < 200; j++) {
            int sum = i + j - 100 + m;
            if (sum >= d) ans += 1LL * res[i] * dp[j];
        } 
    }
    cout << fixed << setprecision(20) << (ld)(ans) / (ld)(1LL * tot * tot_add) << '\n';
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

