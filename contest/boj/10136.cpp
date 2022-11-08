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

/*
 * Solution
 * Create valid interval array of size O(sqrt(n)) for each side
 * Two pointer to finish it off
**/

void solve() {
	int sl, sr, wl, wr;
	cin >> sl >> sr >> wl >> wr;
	if (sr > wr) swap(sr, wr), swap(sl, wl);
	if (wl <= sr && sr <= wr) {
		cout << sr << '\n';
		return;
	}
	vpi ivs, ivw;
	for (int i = 1, la = 0; i <= sr; i = la + 1) {
		int k = sr / i;
		la = sr / k;
		int lo = (sl + k - 1) / k;
		if (lo > la) continue;
		ivs.pb({max(lo, i), la});
	}
	for (int i = 1, la = 0; i <= wr; i = la + 1) {
		int k = wr / i;
		la = wr / k;
		int lo = (wl + k - 1) / k;
		if (lo > la) continue;
		ivw.pb({max(lo, i), la});
	}
	int ans{1};
	int ptr = 0;
	for (auto &[L, R] : ivw) {
		while (ptr < sz(ivs)) {
			auto [l, r] = ivs[ptr];
			int lef = max(l, L), rig = min(r, R);
			if (lef <= rig) ckmax(ans, rig);
			if (r > R) break;
			else{
				ptr++;
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
