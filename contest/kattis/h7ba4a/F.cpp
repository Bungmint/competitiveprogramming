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

constexpr int MOD = 1e9 + 9;
int multi[5111][5111];

int add(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}
int sub(int a, int b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}
int mul(int a, int b) {
    return 1LL * a * b % MOD;
}
int bin_pow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

void solve() {
    int N;
    cin >> N;
    vi a(N);
    for (auto &e : a) cin >> e;
    sort(all(a));
    for (int i = 1; i <= N; i++) {
        multi[i][i] = 1;
        int cnt = 1;
        for (int j = 1; j < i; j++) multi[i][j] = 1;
        for (int j = i + 1; j <= N; j++) {
            multi[i][j] = mul(multi[i][j - 1], j - i + 1);
            if (a[j - 1] == a[j - 2]) {
                cnt++;
            } else {
                cnt = 1;
            }
            multi[i][j] = mul(multi[i][j], bin_pow(cnt, MOD - 2));
            dbg(multi[i][j]);
        }
    }
    for (int i = 0; i <= N + 1; i++) multi[N + 1][i] = 1;
    vi dp(N + 1);
    dp[0] = 1;
    for (int i = 1; i <= N; i++) {
        dp[i] = multi[1][i];
        for (int j = 1; j <= i; j++) {
            dbg(j + 1, i, multi[j + 1][i]);
            dp[i] = sub(dp[i], mul(dp[j - 1], multi[j + 1][i])); 
        }
    }
    dbg(dp);
    cout << dp[N] << '\n';
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

