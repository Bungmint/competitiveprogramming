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

struct DSU {
    vi e, left, right, sum;
    DSU(int N) {
        e = vi(N, -1);
        left = right = sum = vi(N);
    }
    int get(int u) { return e[u] < 0 ? u : e[u] = get(e[u]); }
    void unite(int u, int v) {
        u = get(u), v = get(v);
        if (u == v) return;
        if (e[u] < e[v]) swap(u, v);
        e[u] += e[v], e[v] = u;
        sum[u] += sum[v];
        ckmin(left[u], left[v]), ckmax(right[u], right[v]);
    }
};

int cost[2022][2022];
int R, S;
vi dp_old, dp_new;

int rc(int r, int c) {
    return r * S + c;
}
void solve_dp(int l, int r, int optl, int optr) {
    if (l > r) return;
    int m = (l + r) >> 1;
    int opt = -1, res = -1;
    for (int i = optl; i <= min(optr, m); i++) {
        if (ckmax(res, dp_old[i] + cost[i][m])) {
            opt = i;
        }
    }
    dp_new[m] = res;
    solve_dp(l, m - 1, optl, opt);
    solve_dp(m + 1, r, opt, optr);
}

void solve() {
    cin >> R >> S;	
    vector<string> grid(R);
    DSU dsu(R * S);
    for (auto &v : grid) cin >> v;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < S; j++) {
            if (grid[i][j] == '.') continue;
            dsu.left[rc(i, j)] = dsu.right[rc(i, j)] = j;
            dsu.sum[rc(i, j)] = grid[i][j] - '0'; 
        } 
    }
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < S; j++) {
            if (grid[i][j] == '.') continue;
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                if (ni < 0 || nj < 0 || ni >= R || nj >= S) continue;
                if (grid[ni][nj] == '.') continue;
                dsu.unite(rc(i, j), rc(ni, nj));
            }
        }
    }
    vi vis(R * S);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < S; j++) {
            int h = dsu.get(rc(i, j));
            if (!vis[h] && dsu.sum[h]) {
                vis[h] = 1;
                int l = dsu.left[h], r = dsu.right[h];
                int sum = dsu.sum[h];
                dbg(l, r, sum, h);
                cost[0][l + 1] += sum;
                cost[0][r + 2] -= sum;
                cost[l + 1][l + 1] -= sum;
                cost[l + 1][r + 2] += sum;
            }
        }
    }
    for (int i = 0; i <= S; i++) {
        for (int j = 0; j <= S; j++) {
            if (i) cost[i][j] += cost[i - 1][j];
            if (j) cost[i][j] += cost[i][j - 1];
            if (i && j) cost[i][j] -= cost[i - 1][j - 1];
        }
    }
    dp_old = dp_new = vi(S + 1);
    for (int i = 1; i <= S; i++) {
        dp_old[i] = cost[0][i];  
    }
    cout << *max_element(all(dp_old)) << '\n';
    for (int i = 1; i < S; i++) {
        dp_new = vi(S + 1);
        solve_dp(1, S, 1, S);
        swap(dp_old, dp_new);
        cout << *max_element(all(dp_old)) << '\n';
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

