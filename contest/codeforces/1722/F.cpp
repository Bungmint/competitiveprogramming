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
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (auto &s : grid) cin >> s;
    vector<vi> vis(n, vi(m)), corner(n + 1, vi(m + 1));
    vector<pii> comp;
    auto dfs = y_combinator([&](auto self, int r, int c) -> void {
        comp.pb({r, c});
        vis[r][c] = 1;
        for (int i = 0; i < 4; i++) {
            int nr = r + dx[i], nc = c + dy[i];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (!vis[nr][nc] && grid[nr][nc] == '*') self(nr, nc);
        }
    });
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[i][j] && grid[i][j] == '*') {
                comp.clear();
                dfs(i, j);
                if (sz(comp) != 3) {
                    cout << "NO\n";
                    return;
                }
                if ((comp[0].fi == comp[1].fi && comp[1].fi == comp[2].fi) ||
                    (comp[0].se == comp[1].se && comp[1].se == comp[2].se)) {
                    cout << "NO\n";
                    return;
                }
                for (auto &[r, c] : comp) {
                    if (corner[r][c] || corner[r][c + 1] || corner[r + 1][c] || corner[r + 1][c + 1]) {
                        cout << "NO\n";
                        return;
                    }
                }
                for (auto &[r, c] : comp) {
                    corner[r][c] = corner[r][c + 1] = corner[r + 1][c] = corner[r + 1][c + 1] = 1;
                }
            }
        }
    }
    cout << "YES\n";
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

