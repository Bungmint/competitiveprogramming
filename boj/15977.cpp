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


int bit[210000];
int m, n;
void upd(int i, int v) {
	for (i++; i <= n; i += i & -i) ckmax(bit[i], v);
}
void reset(int i) {
	for (i++; i <= n; i += i & -i) bit[i] = 0;
}
int query(int i) {
	int r = 0;
	for (i++; i; i -= i & -i) ckmax(r, bit[i]);
	return r;
}

void solve() {
	cin >> m >> n;
	vector<vi> grid(m, vi(n));
	for (auto &v : grid) for (auto &e : v) cin >> e;
	for (int r = 0; r < m; r++) {
		vi ind;
		for (int c = 0; c < n; c++) ind.pb(grid[r][c]);
		sort(all(ind));
		for (int c = 0; c < n; c++) 
			grid[r][c] = lb(all(ind), grid[r][c]) - ind.begin();
	}
	if (m == 2) {
		vector<ar<int, 2>> a(n);
		for (int i = 0; i < n; i++) a[i] = {grid[0][i], grid[1][i]};
		sort(all(a));
		int ans = 0;
		for (int i = 0; i < n; i++) {
			auto y = a[i][1];
			auto q = query(y - 1);
			ckmax(ans, q + 1);
			upd(y, q + 1);
		}
		cout << ans << '\n';
	}else{
		vector<ar<int, 4>> a(n);
		vi dp(n, 1);
		for (int i = 0; i < n; i++) a[i] = {grid[0][i], grid[1][i], grid[2][i], i};
		sort(all(a));
		dbg(a);
		auto cmp = [&](ar<int, 4> lhs, ar<int, 4> rhs) {
			return lhs[1] < rhs[1];
		};
		auto dc = y_combinator([&](auto self, int l, int r) -> void {
			if (l == r - 1) return;
			int mid = (l + r) / 2;
			self(l, mid);
			vector<ar<int, 4>> tmp; tmp.reserve(r - l);
			for (int i = l; i < r; i++) tmp.pb(a[i]);
			sort(a.begin() + l, a.begin() + mid, cmp);
			sort(a.begin() + mid, a.begin() + r, cmp);			
			int p = l, q = mid;
			while (p < mid && q < r) {
				if (a[p][1] < a[q][1]) {
					upd(a[p][2], dp[a[p][3]]);
					p++;
				}else{
					ckmax(dp[a[q][3]], query(a[q][2] - 1) + 1);
					q++;
				}
			}
			while (q < r) {
				ckmax(dp[a[q][3]], query(a[q][2] - 1) + 1);
				q++;
			}
			dbg("*****RANGE*****");
			dbg(l, r);
			dbg(vector<ar<int, 4>>(begin(a) + l, begin(a) + r));
			dbg("******DP******");
			for (int i = l; i < r; i++) {
				reset(tmp[i - l][2]);
				a[i] = tmp[i - l];
				dbg(i, dp[a[i][3]]);
			}
			self(mid, r);
		});
		dc(0, n);
		cout << *max_element(all(dp)) << '\n';
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
