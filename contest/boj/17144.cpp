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
    int n, m, t;
    cin >> n >> m >> t;
    vector<vi> a(n, vi(m));
    for (auto &V : a) for (auto &e : V) cin >> e;
    int hi = 0, lo = 0;
    for (int i = 0; i < n; i++) {
        if (a[i][0] == -1) {
            hi = i, lo = i + 1;
            break;
        }
    }
    for (int iter = 0; iter < t; iter++) {
        vector<vi> nxt(n, vi(m));
        // prop
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] < 0) {
                    nxt[i][j] = -1;
                    continue;
                }
                nxt[i][j] += a[i][j];
                int prop = a[i][j] / 5;
                for (int k = 0; k < 4; k++) {
                    int ni = i + dx[k], nj = j + dy[k];
                    if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
                    if (a[ni][nj] == -1) continue;
                    nxt[i][j] -= prop;
                    nxt[ni][nj] += prop;
                }
                // nxt[i][j] += rem;
            }
        }
        // Clean
        int p = 0;
        for (int c = 1; c < m; c++) {
            swap(p, nxt[hi][c]);
        }
        for (int r = hi - 1; r >= 0; r--) {
            swap(p, nxt[r][m - 1]);
        }
        for (int c = m - 2; c >= 0; c--) {
            swap(p, nxt[0][c]);
        }
        for (int r = 1; r < hi; r++) {
            swap(p, nxt[r][0]);
        }
        p = 0;
        for (int c = 1; c < m; c++) {
            swap(p, nxt[lo][c]);
        }
        for (int r = lo + 1; r < n; r++) {
            swap(p, nxt[r][m - 1]);
        }
        for (int c = m - 2; c >= 0; c--) {
            swap(p, nxt[n - 1][c]);
        }
        for (int r = n - 2; r > lo; r--) {
            swap(p, nxt[r][0]);
        }
        swap(nxt, a);
    }
    dbg(a);
    int ans = 0;
    for (auto &v : a) ans += accumulate(all(v), 0LL);
    ans += 2;
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

