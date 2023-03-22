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
int dp[201111][1011];
int tin[201111], tout[201111];
vi g[201111], E[201111];
bool is_red[201111];
int timer = 1;

int add(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}
void dfs(int u, int pu) {
    tin[u] = timer++;
    for (auto &v : g[u]) {
        if (v != pu) dfs(v, u);
    }
    tout[u] = timer - 1;
    E[tout[u]].pb(u);
}


void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n - 1; i++) {
        int x;
        cin >> x;
        x--;
        g[i].pb(x), g[x].pb(i);
    }
    for (int i = 0; i < m; i++) {
        int u;
        cin >> u, u--;
        is_red[u] = 1;
    }
    dfs(0, -1);
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = dp[i - 1][j];
        }
        for (auto &u : E[i]) {
            dbg(i, u, tin[u]);
            for (int j = 0; j <= m; j++) {
                if (!is_red[u]) dp[i][j] = add(dp[i][j], dp[tin[u] - 1][j]);
                if (is_red[u] && j) dp[i][j] = add(dp[i][j], dp[tin[u] - 1][j - 1]);
            }
        }
    } 
    for (int i = 0; i <= m; i++) {
        cout << dp[n][i] << '\n';
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

