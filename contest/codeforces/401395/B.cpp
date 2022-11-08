// Copyright © 2022 Youngmin Park. All rights reserved.
// #pragma GCC optimize("O3")
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
	int h, w, q;
	cin >> h >> w;
	vector<string> grid(h);
	vector<vi> btw_row(h - 1, vi(w)), btw_col(h, vi(w - 1));
	for (auto &s : grid) cin >> s;
	for (int i = 0; i < h - 1; i++) {
		for (int j = 0; j < w; j++) {
			if (grid[i][j] == grid[i + 1][j] && grid[i][j] == '.') 
				btw_row[i][j] = 1;
			if (i) btw_row[i][j] += btw_row[i - 1][j];
			if (j) btw_row[i][j] += btw_row[i][j - 1];
			if (i && j) btw_row[i][j] -= btw_row[i - 1][j - 1];
		}
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w - 1; j++) {
			if (grid[i][j] == grid[i][j + 1] && grid[i][j] == '.') {
				btw_col[i][j] = 1;
			}
			if (i) btw_col[i][j] += btw_col[i - 1][j];
			if (j) btw_col[i][j] += btw_col[i][j - 1];
			if (i && j) btw_col[i][j] -= btw_col[i - 1][j - 1];
		}
	}

	cin >> q;
	for (int i = 0; i < q; i++) {
		int r1, c1, r2, c2;
		cin >> r1 >> c1 >> r2 >> c2;
		r1--, c1--, r2--, c2--;
		int res = 0;
		if (c1 < c2) {
			res += btw_col[r2][c2 - 1];
			if (r1) res -= btw_col[r1 - 1][c2 - 1];
			if (c1) res -= btw_col[r2][c1 - 1];
			if (r1 && c1) res += btw_col[r1 - 1][c1 - 1];
		}
		if (r1 < r2) {
			res += btw_row[r2 - 1][c2];
			if (r1) res -= btw_row[r1 - 1][c2];
			if (c1) res -= btw_row[r2 - 1][c1 - 1];
			if (r1 && c1) res += btw_row[r1 - 1][c1 - 1];
		}
		cout << res << '\n';
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
