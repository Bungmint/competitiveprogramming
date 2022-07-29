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
 * Solution: Manacher on the rows where we represent the rows as a tuple of 26
 			* OR we could use hashing to speed up 26 times potentially 
 */

using a26 = ar<int, 26>;
a26 sub(const a26& a, const a26& b) {
	a26 ret{};
	for (int i = 0; i < 26; i++) ret[i] = a[i]-b[i];
	return ret;
}
bool is_bad(const a26& a) {
	int cnt{};
	for (int i = 0; i < 26; i++) if (a[i] & 1) cnt++;
	return cnt > 1;
}

vi manacher(const vector<a26>& s, const a26& sp1, const a26& sp2) {
	vector<a26> t{{}};
	for (auto &ch : s) t.pb(ch), t.pb(sp1);
	t.back() = sp2;
	vi ret(sz(t) - 1);
    for (int i = 1, l = 1, r = 1; i < sz(t) - 1; i++) {
        ret[i] = max(0, min(r - i, ret[l + (r - i)]));
        while (t[i - ret[i]] == t[i + ret[i]]) ret[i]++;
        if (i + ret[i] > r) l = i - ret[i], r = i + ret[i];
    }
	ret.erase(ret.begin());
	for (int i = 0; i < sz(ret); i++) {
		if (i % 2 == ret[i] % 2) ret[i]--;
	}
	return ret;
}

void solve() {
	int n, m; cin >> n >> m;
	vector<string> grid(n);
	vector<vector<a26>> pref(n, vector<a26>(m));
	a26 sp1{}, sp2{};
	for (int i = 0; i < 26; i++) sp1[i] = -2*INF, sp2[i] = -INF;
	for (auto &s : grid) cin >> s;
	for (int i = 0; i < n; i++) {
		a26 cur{};
		for (int j = 0; j < m; j++) {
			cur[grid[i][j]-'a']++;
			pref[i][j] = cur;
		}
	}
	ll ans{};
	for (int i = 0; i < m; i++) {
		for (int j = i; j < m; j++) {
			vector<a26> str(n);
			vector<bool> bad(n);
			for (int k = 0; k < n; k++) {
				str[k] = (i ? sub(pref[k][j], pref[k][i - 1]) : pref[k][j]);
				bad[k] = is_bad(str[k]);
				if (bad[k]) {
					for (int x = 0; x < 26; x++) str[k][x] = -(k + 1);
				}
			}
			vi ret = manacher(str, sp1, sp2);
			dbg(i, j);
			dbg(str);
			dbg(ret);
			for (auto &x : ret) ans += (x + 1) / 2;
			for (int k = 0; k < n; k++) if (bad[k]) ans -= (ret[2*k] + 1) / 2;
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
