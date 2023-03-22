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

int R, C;

void dfs(vector<vector<char>>& g, vector<vector<bool>>& vis, int r, int c) {
    vis[r][c] = 1;
    for (int i = 0; i < 4; i++) {
        int nr = r + dx[i], nc = c + dy[i];
        if (nr < 0 || nc < 0 || nr >= R + C + 3 || nc >= R + C + 3) continue;
        if (g[nr][nc] == '#') continue;
        if (vis[nr][nc]) continue;
        dfs(g, vis, nr, nc);
    }
}

void solve() {
    cin >> R >> C;
    vector<string> grid(R);
    vector<vector<char>> transform(R + C + 3, vector<char>(R + C + 3, '.'));
    for (auto &s : grid) cin >> s;
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (grid[r][c] == '/') {
                transform[r + c + 2][r + 2 - c + C] = '#';
                transform[r + c + 2][r - c + C] = '#';
                transform[r + c + 2][r + 1 - c + C] = '#';
            }else if (grid[r][c] == '\\') {
                transform[r + c + 1][r + 1 - c + C] = '#';
                transform[r + c + 2][r + 1- c + C] = '#';
                transform[r + c + 3][r + 1 - c + C] = '#';
            }
        }
    }
    vector<vector<bool>> vis(R + C + 3, vector<bool>(R + C + 3));
    int ans = -1;
    for (int i = 0; i < R + C + 3; i++) {
        for (int j = 0; j < R + C + 3; j++) {
            if (!vis[i][j] && transform[i][j] == '.') {
                dfs(transform, vis, i, j);
                ans++;
            }
        }
    }
    cout << ans << '\n';
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

