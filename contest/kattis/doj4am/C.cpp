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
    while (true) {
        int a, b;
        cin >> a >> b;
        if (a == 0 && b == 0) return;
        int ans = a * b;
        vi digA, digB, digAns;
        while (a) digA.pb(a % 10), a /= 10;
        while (b) digB.pb(b % 10), b /= 10;
        while (ans) digAns.pb(ans % 10), ans /= 10;
        reverse(all(digA)), reverse(all(digB)), reverse(all(digAns));
        int n = sz(digA), m = sz(digB);
        vector<vector<char>> grid(4 * m + 5, vector<char>(4 * n + 5, ' '));
        for (int i = 0; i < 4 * n + 5; i++) {
            grid[0][i] = '-';
            grid[4 * m + 4][i] = '-';
        }
        for (int i = 0; i < 4 * m + 5; i++) {
            grid[i][0] = '|';
            grid[i][4 * n + 4] = '|';
        }
        grid[0][0] = grid[0][4 * n + 4] = grid[4 * m + 4][0] = grid[4 * m + 4][4 * n + 4] = '+';
        for (int i = 0; i < n; i++) {
            grid[1][4 * i + 4] = (char)('0' + digA[i]);
        } 
        for (int i = 0; i < m; i++) {
            grid[4 * i + 4][4 * n + 3] = (char)('0' + digB[i]);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 2 + 4*i; k <= 6 + 4*i; k++) grid[2 + 4*j][k] = grid[6 + 4*j][k] = '-';
                for (int k = 2 + 4*j; k <= 6 + 4*j; k++) grid[k][2 + 4*i] = grid[k][6 + 4*i] = '|';
                grid[2 + 4*j][2 + 4*i] = grid[2 + 4*j][6 + 4*i] = grid[6 + 4*j][2 + 4*i] = grid[6 + 4*j][6 + 4*i] = '+';
                for (int k = 0; k < 3; k++) {
                    grid[3 + 4*j + k][5 + 4*i - k] = '/';
                }
                int res = digA[i] * digB[j];
                grid[3 + 4*j][3 + 4*i] = (char)(res / 10 + '0'); 
                grid[5 + 4*j][5 + 4*i] = (char)(res % 10 + '0');
            }
        }
        reverse(all(digAns));
        for (int i = 0; i < n; i++) {
            grid[3 + 4*m][-1 + 4*n - 4*i] = (char)(digAns[i] + '0');
            if (sz(digAns) > i + 1) {
                grid[3 + 4*m][-3 + 4*n - 4*i] = '/';
            }
        }
        for (int ii = n; ii < sz(digAns); ii++) {
            int i = ii - n;
            grid[1 + 4*m - 4*i][1] = (char)(digAns[ii] + '0');
            if (sz(digAns) > ii + 1) {
                grid[-1 + 4*m - 4*i][1] = '/';
            } 
        }

        for (auto &s : grid) {
            for (auto &ch: s) cout << ch;
            cout << '\n';
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

