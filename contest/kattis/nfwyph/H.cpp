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
    int N, W;
    cin >> N >> W;
    vector<string> dict(N);
    vi a;
    vector<vi> range_max(N + 1, vi(N + 1)), dp_final;
    for (auto &e : dict) cin >> e, a.pb(sz(e));
    for (int i = 0; i < N; i++) {
        range_max[i + 1][i + 1] = a[i];
        for (int j = i + 1; j < N; j++) {
            range_max[i + 1][j + 1] = range_max[i + 1][j];
            ckmax(range_max[i + 1][j + 1], a[j]);
        }
    }
    int L = 1, R = N, ans = N;
    while (L <= R) {
        int mid = (L + R) / 2;
        vector<vi> dp(N + 1, vi(mid + 1, INF));
        vi dp_min(N + 1, INF);
        dp[0][0] = dp_min[0] = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= min(i, mid); j++) {
                dp[i][j] = (i - j == 0 ? 0 : 1) + dp_min[i - j] + range_max[i - j + 1][i];
                ckmin(dp_min[i], dp[i][j]);
            }
        }
        if (dp_min[N] <= W) {
            ans = mid;
            R = mid - 1;
            dp_final.swap(dp);
        }else L = mid + 1;
    }
    vi columns;
    int last = N;
    while (last) {
        int last_col = min_element(all(dp_final[last])) - dp_final[last].begin();
        columns.pb(last_col);
        last -= last_col;
    }
    reverse(all(columns));
    vector<vector<string>> strs(ans, vector<string>(sz(columns)));
    vi max_len(sz(columns));
    int ptr = 0;
    for (int c = 0; c < sz(columns); c++) {
        int len = range_max[ptr + 1][ptr + columns[c]];
        max_len[c] = len;
        for (int r = 0; r < columns[c]; r++) {
            strs[r][c] = dict[ptr + r]; 
        }
        for (int r = 0; r < ans; r++) {
            while (sz(strs[r][c]) < len) strs[r][c] += ' ';
        }
        ptr += columns[c];
    }
    
    cout << ans << ' ' << sz(columns) << '\n';
    for (int i = 0; i < sz(columns); i++) {
        cout << max_len[i] << " \n"[i == sz(columns) - 1];
    }
    for (auto &v : strs) {
        for (int i = 0; i < sz(v); i++) {
            cout << v[i] << " \n"[i == sz(v) - 1];
        }
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

