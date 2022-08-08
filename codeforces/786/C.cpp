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
	T lower_bound(T v) {
		int id = 0;
		T sum = 0;
		int lg = 31 - __builtin_clz(N);
		for (int j = lg; ~j; j--) {
			if (id + (1 << j) <= N && sum + bit[id + (1 << j)] < v) {
				id += (1 << j);
				sum += bit[id];
			}
		}
		return id;
	}
};

void solve() {
	int n; cin >> n;
	BIT<int> bit(n);
	vi nxt(n), last_seen(n, n), a(n), ans(n + 1);
	vector<vi> queries(n);
	queries[0].resize(n);
	iota(all(queries[0]), 1);
	for (auto &e : a) cin >> e, e--;
	for (int i = n - 1; i >= 0; i--) {
		nxt[i] = last_seen[a[i]];
		last_seen[a[i]] = i;
	}
	for (int i = 0; i < n; i++) {
		if (last_seen[a[i]] == i) bit.upd(i, 1);
	}
	for (int i = 0; i < n; i++) {
		for (auto &k : queries[i]) {
			ans[k]++;
			int j = bit.lb(k+1);
			if (j < n) queries[j].pb(k);
		}
		bit.upd(i, -1);
		if (nxt[i] < n) bit.upd(nxt[i], 1);
	}
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << " \n"[i == n];
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
