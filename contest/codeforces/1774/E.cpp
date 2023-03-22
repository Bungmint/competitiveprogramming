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

constexpr int N = 211'111;
vi g[N];
int depth[N];
ll dp[N];
ll f[N];
int n, d;
bool red[N], blue[N];
int max_depth[N];

void init(int u = 0, int pu = -1) {
    if (red[u] || blue[u]) max_depth[u] = depth[u];
    for (auto &v : g[u]) {
        if (v == pu) continue;
        depth[v] = depth[u] + 1;
        init(v, u);
        red[u] |= red[v];
        blue[u] |= blue[v];
        ckmax(max_depth[u], max_depth[v]);
        if (red[v] || blue[v]) f[u] += 2 + f[v];
    }
}
void dfs(int u = 0, int pu = -1) {
    {
        for (auto &v : g[u]) {
            if (v == pu) continue;
            if (red[v] && blue[v]) {
                dfs(v, u);
                dp[u] += 4 + dp[v];
            }else if (red[v]) {
                if (max_depth[v] - depth[u] <= d) {
                    dp[u] += 2 + f[v];
                }else{
                    dfs(v, u);
                    dp[u] += 4 + dp[v];
                }
            }else if (blue[v]) {
                if (max_depth[v] - depth[u] <= d) {
                    dp[u] += 2 + f[v];
                }else{
                    dfs(v, u);
                    dp[u] += 4 + dp[v];
                }     
            }
        }
    }
}

void solve() {
    cin >> n >> d;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].pb(v);
        g[v].pb(u);
    }
    int mr, mb;
    cin >> mr;
    for (int i = 0; i < mr; i++) {
        int u;
        cin >> u;
        u--, red[u] = 1;
    }
    cin >> mb;
    for (int i = 0; i < mb; i++) {
        int u; 
        cin >> u;
        u--, blue[u] = 1;
    }
    init();
    dfs();
    cout << dp[0] << '\n';
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

