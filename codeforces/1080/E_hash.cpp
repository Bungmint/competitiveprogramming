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
using ull = unsigned long long;

int stor[512];
inline int manacher(const vector<ull>& s) {
	if (sz(s) == 0) return {};
	ull rnd1{}, rnd2{}, rnd3{};
	rnd1 = rng();
	rnd2 = rng();
	rnd3 = rng();
	int res{};
	vector<ull> t{rnd1};
	for (auto &ch : s) t.pb(ch), t.pb(rnd2);
	t.back() = rnd3;
	memset(stor, 0, sizeof(stor));
    for (int i = 1, l = 1, r = 1; i < sz(t) - 1; i++) {
        stor[i] = max(0, min(r - i, stor[l + (r - i)]));
        while (t[i - stor[i]] == t[i + stor[i]]) stor[i]++;
        if (i + stor[i] > r) l = i - stor[i], r = i + stor[i];
    }
	for (int i = 1; i < sz(t) - 1; i++) {
		if (i % 2 != stor[i] % 2) stor[i]--;
		res += (stor[i] + 1) / 2;
	}
	return res;
}

void solve() {
	int n, m; cin >> n >> m;
	vector<string> grid(n);
	vector<vector<ull>> pref(n, vector<ull>(m));
	for (auto &s : grid) cin >> s;
	ll ans{};
	{
		vector<ull> H(26);
		for (int i = 0; i < 26; i++) H[i] = rng();
		for (int i = 0; i < n; i++) {
			ull cur{};
			for (int j = 0; j < m; j++) {
				cur += H[grid[i][j] - 'a'];
				pref[i][j] = cur;
			}
		}
		for (int i = 0; i < m; i++) {
			vector<vi> cnt(n, vi(26));
			vi bad(n);
			for (int j = i; j < m; j++) {
				int r{};
				vector<ull> str;
				for (int k = 0; k < n; k++) {
					cnt[k][grid[k][j]-'a']++;
					if (cnt[k][grid[k][j]-'a'] & 1) bad[k]++;
					else bad[k]--;
					if (bad[k] > 1) {
						r += manacher(str);
						vector<ull>().swap(str);
					}else{
						str.pb(pref[k][j] - (i ? pref[k][i - 1] : 0));
					}	
				}
				if (sz(str)) {
					r += manacher(str);
					vector<ull>().swap(str);
				}
				dbg(i, j, r);
				ans += r;
			}
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
