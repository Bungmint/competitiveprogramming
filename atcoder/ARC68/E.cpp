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

/**
 * Description: Performs range prefix sum queries and point updates. lower_bound returns the first prefix sum >= v
 * Source: Own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=693
 * Time Complexity: O(log n) for query and update
 * 0-indexing
 */

template <typename T>
struct BIT {
	int N; vector<T> bit;
	BIT(int n) : N(n), bit(n + 1) {}
	void upd(int id, T v) {
		for (id++; id <= N; id += id & -id)
			bit[id] += v;
	}
	T query(int id) {
		T res = 0;
		for (id++; id > 0; id -= id & -id)
			res += bit[id];
		return res;
	}
	T query(int l, int r) {
		return l > r ? 0 : query(r) - query(l - 1);
	}
};


void solve() {
	int n, m, tot;
	cin >> m >> n;
	vector<vpi> upd_len(n + 1);
	BIT<int> bit(n + 1);
	tot = m;
	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;
		upd_len[r-l+1].pb({l, r});
	}
	for (int d = 1; d <= n; d++) {
		int ans = tot;
		for (int kd = d; kd <= n; kd += d) {
			ans += bit.query(kd);
		}
		cout << ans << '\n';

		for (auto &[l, r] : upd_len[d]) {
			bit.upd(l, 1);
			if (r < n) bit.upd(r + 1, -1);
			tot--;
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
