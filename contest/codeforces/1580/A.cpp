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
    vector<vi> pref(n + 1, vi(m + 1));
    int ans = INF;
    for (auto &s : grid) cin >> s;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pref[i + 1][j + 1] = grid[i][j] - '0';
            pref[i + 1][j + 1] += pref[i + 1][j] + pref[i][j + 1] - pref[i][j];
        }
    }
    auto get_sum = [&](int a, int b, int c, int d) {
            return pref[c + 1][d + 1] - pref[c + 1][b] - pref[a][d + 1] + pref[a][b];
         };
    // dbg(get_sum(0, 0, 4, 3));
    for (int lo = 0; lo < n; lo++) {
        for (int hi = lo + 4; hi < n; hi++) {
            int suf_min = INF;
            vi pref_lohi(m + 1), c(m);
            for (int i = 0; i < m; i++) {
                pref_lohi[i + 1] += pref_lohi[i] + (grid[lo][i] == '0') + (grid[hi][i] == '0');
                c[i] = hi - lo - 1 - get_sum(lo + 1, i, hi - 1, i);
                dbg(get_sum(lo + 1, i, hi - 1, i));
            }
            dbg(c, lo, hi);
            for (int l = m - 3; l >= 0; l--) {
                ckmin(ans, suf_min - pref_lohi[l + 1] + c[l] - get_sum(lo + 1, 0, hi - 1, l)); 
                ckmin(suf_min, c[l + 2] + pref_lohi[l + 2] + get_sum(lo + 1, 0, hi - 1, l + 1));
            }
        }
    }
    cout << ans << '\n';
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

