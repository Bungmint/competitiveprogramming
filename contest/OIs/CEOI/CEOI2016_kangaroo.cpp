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



template <int MOD>
struct mint {
    static constexpr int mod = MOD;
    int x;
    mint() { x = 0; }
    mint(ll _x) {
        _x %= mod;
        if (_x < 0) _x += mod;
        x = _x;
    }
    explicit operator int() const { return x; }
    constexpr mint& operator+=(const mint& other) {
        x += other.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    constexpr mint& operator*=(const mint& other) {
        x = 1LL * x * other.x % mod;     
        return *this;
    }
    constexpr friend mint operator+(mint a, const mint& b) { return a += b; } 
    constexpr friend mint operator*(mint a, const mint& b) { return a *= b; }
};

using Mint = mint<MOD>;
Mint dp[2][2111];

void solve() {
    int n, st, en;
    cin >> n >> st >> en;
    int cur = 0, nxt = 1;
    dp[cur][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n + 10; j++) dp[nxt][j] = 0;
        if (i == st) {
            for (int j = 0; j <= n; j++) {
                dp[nxt][j + 1] += dp[cur][j];
                dp[nxt][j] += dp[cur][j];
            }
        } else if (i == en) {
            for (int j = 0; j <= n; j++) {
                dp[nxt][j + 1] += dp[cur][j];
                dp[nxt][j] += dp[cur][j];
            }
        } else {
            for (int j = 0; j <= n; j++) {
                if (j) dp[nxt][j - 1] += dp[cur][j] * (j - 1);
                int newCC = j + 1;
                if (i > st) newCC--;
                if (i > en) newCC--;
                if (newCC > 0) dp[nxt][j + 1] += dp[cur][j] * newCC;
            }
        }
        swap(cur, nxt);
    }
    cout << dp[cur][1].x << '\n';
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

