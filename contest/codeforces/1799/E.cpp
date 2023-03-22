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

int n, m;
void dfs(int r, int c, vector<vi>& vis, vpi& cc, vector<string>& grid) { 
    cc.pb({r, c});
    vis[r][c] = 1;
    for (int i = 0; i < 4; i++) {
        int nr = r + dx[i], nc = c + dy[i];
        if (nr < 0 || nc < 0 || nr >= n || nc >= m) {
            continue;
        }
        if (!vis[nr][nc] && grid[nr][nc] == '#') dfs(nr, nc, vis, cc, grid);
    }
}

void solve() {
    // int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (auto &s : grid) cin >> s;
    auto fill_hole = [&]() {
        vector<vi> vis(n, vi(m));
        queue<pii> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '#') {
                    q.push({i, j});
                }
            }
        }
        // No hole-y region
        while (sz(q)) {
            auto [r, c] = q.front();
            q.pop();
            if (vis[r][c]) continue;
            vis[r][c] = 1;
            grid[r][c] = '#';
            int mi = INF, mx = -INF;
            for (int i = 0; i < n; i++) {
                if (grid[i][c] == '#') ckmin(mi, i), ckmax(mx, i);
            }
            for (int i = mi; i <= mx; i++) {
                q.push({i, c});
            }
            mi = INF, mx = -INF;
            for (int i = 0; i < m; i++) {
                if (grid[r][i] == '#') ckmin(mi, i), ckmax(mx, i);
            }
            for (int i = mi; i <= mx; i++) {
                q.push({r, i});
            }
        }
    };
    fill_hole();
        // dbg(grid);
    vector<vi> vis(n, vi(m));
    vector<vpi> ccs;
    vpi cc;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (!vis[r][c] && grid[r][c] == '#') {
                cc.clear();
                dfs(r, c, vis, cc, grid);
                // dbg(cc);
                ccs.pb(cc);
            }
        }
    }

    if (sz(ccs) == 2) {
        ar<ar<int, 4>, 2> val = {};
        val[0] = val[1] = {INF, -INF, INF, -INF};
        for (int i = 0; i < 2; i++) {
            for (auto &[r, c] : ccs[i]) {
                ckmin(val[i][0], r);
                ckmin(val[i][2], c);
                ckmax(val[i][1], r);
                ckmax(val[i][3], c);
            } 
        }
        if (val[0][2] > val[1][2]) swap(val[0], val[1]), swap(ccs[0], ccs[1]);
        if (val[0][0] < val[1][0]) {
            grid[val[0][1]][val[0][3]] = '#';
            grid[val[1][0]][val[1][2]] = '#';
            grid[val[0][1]][val[1][2]] = '#';
        } else {
            grid[val[0][0]][val[0][3]] = '#';
            grid[val[1][1]][val[1][2]] = '#';
            grid[val[0][0]][val[1][2]] = '#';
        }
    }
    fill_hole();
    for (auto &s : grid) cout << s << '\n';
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

