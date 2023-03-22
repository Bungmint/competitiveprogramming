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

int dist[13][13];
int d[511][511];
int fuel[1 << 12][12];
int fuel_finish[1 << 12];
ll wsum[1 << 12];
int dp[1 << 12];
int n, k, m;
int x[13], y[13], w[12];
vector<string> grid;

void bfs(int st) {
    deque<pii> q;
    memset(d, 0x3f, sizeof(d));
    q.pb({x[st], y[st]});
    d[x[st]][y[st]] = 0;
    while (sz(q)) {
        auto [r, c] = q.front();
        q.pop_front();
        for (int i = 0; i < k; i++) {
            if (x[i] == r && y[i] == c) {
                ckmin(dist[st][i], d[r][c]);
                dbg(st, i, dist[st][i]);
            }
        }
        for (int i = 0; i < 4; i++) {
            int nr = r + dx[i];
            int nc = c + dy[i];
            if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
            if (grid[nr][nc] == '#') continue;
            if (ckmin(d[nr][nc], d[r][c] + (grid[nr][nc] == '+'))) {
                if (grid[nr][nc] == '+') q.pb({nr, nc});
                else q.push_front({nr, nc});
            }
        }
    }
}

void solve() {
    cin >> n >> k >> m;	
    grid.resize(n);
    memset(dist, 0x3f, sizeof(dist));
    for (int i = 0; i < n; i++) {
        cin >> grid[i]; 
    }
    for (int i = 0; i < k; i++) cin >> x[i] >> y[i] >> w[i], x[i]--, y[i]--;
    for (int i = 0; i <= k; i++) bfs(i);
    memset(fuel, 0x3f, sizeof(fuel));
    memset(fuel_finish, 0x3f, sizeof(fuel_finish));
    for (int i = 0; i < k; i++) {
        fuel[1 << i][i] = dist[k][i];
        fuel_finish[1 << i] = dist[k][i] * 2;
        dbg(fuel[1 << i][i]);
    }
    for (int mask = 1; mask < (1 << k); mask++) {
        for (int la = 0; la < k; la++) {
            if (!(mask >> la & 1)) continue;
            int prev_mask = mask ^ (1 << la);
            for (int i = 0; i < k; i++) {
                if (!(prev_mask >> i & 1)) continue;
                ckmin(fuel[mask][la], fuel[prev_mask][i] + dist[i][la]);
            }
            ckmin(fuel_finish[mask], fuel[mask][la] + dist[k][la]);
        }
    }
    for (int mask = 0; mask < (1 << k); mask++) {
        for (int i = 0; i < mask; i++) {
            if (mask >> i & 1) wsum[mask] += w[i];
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int mask = 0; mask < (1 << k); mask++) {
        for (int s = mask; s; s = (s - 1) & mask) {
            if (wsum[s] <= m) {
                ckmin(dp[mask], dp[mask ^ s] + fuel_finish[s]);
            } 
        }
    }
    cout << dp[(1 << k) - 1] << '\n';
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

