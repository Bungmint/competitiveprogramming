// Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

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

void solve() {
	int n;
	cin >> n;
	vector<string> grid(n);
	vector<bool> row(n), col(n);
	for (auto &s : grid) cin >> s;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] != grid[i + 1][j]) {
				for (int k = 0; k < n; k++) {
					if (k < i || k > i + 1) row[k] = 1;
					col[k] = 1;
				}
			}
		}
		for (int j = 0; j < n; j++) {
			if (grid[j][i] != grid[j][i + 1]) {
				for (int k = 0; k < n; k++) {
					if (k < i || k > i + 1) col[k] = 1;
					row[k] = 1;
				}
			}
		}
	}
	int ans{};
	for (int i = 0; i < n; i++) { // row
		if (!row[i]) continue;
		int cur{};
		for (int j = 0; j < n; j++) {
			if (j == 0) cur = 1;
			else{
				if (grid[i][j] == grid[i][j - 1]) cur++;
				else cur = 1;
			} 
			ckmax(ans, cur);
		}
	}
	for (int i = 0; i < n; i++) { // col
		if (!col[i]) continue;
		int cur{};
		for (int j = 0; j < n; j++) {
			if (j == 0) cur = 1;
			else{
				if (grid[j][i] == grid[j - 1][i]) cur++;
				else cur = 1;
			} 
			ckmax(ans, cur);
		}
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == grid[i + 1][j]) continue;
			swap(grid[i][j], grid[i + 1][j]);
			int cur{};
			for (int k = 0; k < n; k++) {
				if (k == 0) cur = 1;
				else{
					if (grid[i][k] == grid[i][k - 1]) cur++;
					else cur = 1;
				} 
				ckmax(ans, cur);
			}
			cur = 0;
			for (int k = 0; k < n; k++) {
				if (k == 0) cur = 1;
				else{
					if (grid[i + 1][k] == grid[i + 1][k - 1]) cur++;
					else cur = 1;
				} 
				ckmax(ans, cur);
			}
			cur = 0;
			for (int k = 0; k < n; k++) {
				if (k == 0) cur = 1;
				else{
					if (grid[k][j] == grid[k - 1][j]) cur++;
					else cur = 1;
				}
				ckmax(ans, cur);
			}
			swap(grid[i][j], grid[i + 1][j]);
		}
		dbg(grid);
	} 
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[j][i] == grid[j][i + 1]) continue;
			swap(grid[j][i], grid[j][i + 1]);
			int cur = 0;
			for (int k = 0; k < n; k++) {
				if (k == 0) cur = 1;
				else{
					if (grid[k][i] == grid[k - 1][i]) cur++;
					else cur = 1;
				} 
				ckmax(ans, cur);
			}
			cur = 0;
			for (int k = 0; k < n; k++) {
				if (k == 0) cur = 1;
				else{
					if (grid[k][i + 1] == grid[k - 1][i + 1]) cur++;
					else cur = 1;
				} 
				ckmax(ans, cur);
			}
			cur = 0;
			for (int k = 0; k < n; k++) {
				if (k == 0) cur = 1;
				else{
					if (grid[j][k] == grid[j][k - 1]) cur++;
					else cur = 1;
				}
				ckmax(ans, cur);
			}
			swap(grid[j][i], grid[j][i + 1]);
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
