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
	int n, q;
	cin >> n >> q;
	vi a(n), ans(n);
	for (auto &e : a) cin >> e;
	if (q >= n) {
		for (int i = 0; i < n; i++) cout << 1;
		cout << '\n';
		return;
	}
	map<int, vi> ind;
	set<int> st;
	for (int i = 0; i < n; i++) {
		ind[a[i]].pb(i);
		st.insert(i);
	}
	int r = n - 1;
	auto get = [&]() -> int {
		if (sz(st) == 0) return -1;
		return *--st.end();
	};
	for (int i = 1; i <= q; i++) {
		if (r < 0) break;
		if (sz(ind[i]) == 0) {
			ans[r] = 1;
			st.erase(st.find(r));
			r = get();
		}else{
			int la = ub(all(ind[i]), r) - ind[i].begin();
			la--;
			if (la < 0)	{
				ans[r] = 1;
				st.erase(r);
				for (auto &id : ind[i]) {
					if (st.count(id)) st.erase(id);
				}
				r = get();
			}else{
				la = ind[i][la];
				for (auto &id : ind[i]) {
					if (id > la) break;
					ans[id] = 1;
				}
				for (auto &id : ind[i]) {
					if (st.count(id)) st.erase(id);
				}
				if (la == r) {
					int new_r = get();
					// for (int j = new_r; j <= r; j++) {
					// 	if (st.count(j)) st.erase(j);
					// }
					r = new_r;
				}else{
					ans[r] = 1;
					st.erase(r);
					int new_r = get();
					// for (int j = new_r; j <= r; j++) {
					// 	if (st.count(j)) st.erase(j);
					// }
					r = new_r;
				}
			}
		}
	}
	for (auto &e : ans) cout << e;
	cout << '\n';
	// cout << ans << '\n';
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
