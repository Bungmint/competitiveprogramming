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

/**
 * Description: Data structure that supports range idempotent queries on a static array
 * Source: Own
 * Verification:
 * Time Complexity: O(nlogn) build, O(1) query
 */

template <typename T>
struct SparseTable{
	vector<vector<T>> spar;
	inline T merge(const T& a, const T& b) { // change this
		return min(a, b);
	} 
	SparseTable() {}
	SparseTable(const vector<T>& a) {
		int lg = 32 - __builtin_clz(sz(a));
		spar.assign(lg, vector<T>(sz(a), 0));
		for (int i = 0; i < sz(a); ++i) spar[0][i] = a[i];
		for (int j = 1; j < lg; ++j) 
			for (int i = 0; i + (1 << j) <= sz(a); ++i)
				spar[j][i] = merge(spar[j - 1][i], spar[j - 1][i + (1 << (j - 1))]);
	}
	SparseTable(T a[], int n) {
		int lg = 32 - __builtin_clz(n);
		spar.assign(lg, vector<T>(n, 0));
		for (int i = 0; i < n; ++i) spar[0][i] = a[i];
		for (int j = 1; j < lg; ++j) 
			for (int i = 0; i + (1 << j) <= n; ++i)
				spar[j][i] = merge(spar[j - 1][i], spar[j - 1][i + (1 << (j - 1))]);
	}
	T query(int a, int b) {
		assert(a <= b);
		int dif = 31 - __builtin_clz(b - a + 1);
		return merge(spar[dif][a], spar[dif][b - (1 << dif) + 1]);
	}
};

void solve() {
	int n, k;
	cin >> n >> k;
	vl a(n + 1);
	vl pref(n + 1);
	vpl closest(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = k + 1; i <= n; i++) {
		pref[i] = pref[i - 1] + a[i];
	}
	set<pll> st{{LINF, n + 1}};
	for (int i = n; i >= k + 1; i--) {
		while (st.begin()->first <= pref[i]) {
			st.erase(st.begin());
		}
		st.insert(make_pair(pref[i], i));
		auto it = st.lb(make_pair(pref[i - 1], -LINF));
		if (it->second == n + 1) {
			closest[i] = make_pair(pref[n] - pref[i - 1], n);
		}else{
			closest[i] = make_pair(it->first - pref[i - 1], it->second);
		}
	}
	st.clear();
	st = {{LINF, 0}};
	for (int i = k - 1; i >= 1; i--) {
		pref[i] = pref[i + 1] + a[i];
	}
	for (int i = 1; i <= k - 1; i++) {
		while (st.begin()->first <= pref[i]) {
			st.erase(st.begin());
		}
		st.insert(make_pair(pref[i], i));
		auto it = st.lb(make_pair(pref[i + 1], -LINF));
		if (it->second == 0) {
			closest[i] = make_pair(pref[1] - pref[i + 1], 1);
		}else{
			closest[i] = make_pair(it->first - pref[i + 1], it->second);
		}
	}
	SparseTable<ll> spar(pref);
	int l = k, r = k;
	ll cur = a[k];
	while (l > 1 && r < n) {
		// dbg(cur, l, r);
		auto [cost_l, nxt_l] = closest[l - 1];
		auto [cost_r, nxt_r] = closest[r + 1];
		
		if (spar.query(nxt_l, l - 1) - pref[l] + cur >= 0) l = nxt_l, cur += cost_l;
		else if (spar.query(r + 1, nxt_r) - pref[r] + cur >= 0) r = nxt_r, cur += cost_r;
		else break;
	}
	cout << ((l > 1 && r < n) ? "NO" : "YES") << '\n';
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
