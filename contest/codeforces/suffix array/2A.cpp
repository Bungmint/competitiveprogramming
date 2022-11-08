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

void count_sort_zero(vi &p, vi &c, string &s) {
	int n = sz(s);
	vi cnt(27), pos(27);
	for (int i = 0; i < n; i++) cnt[s[i] + 1 - 'a']++;
	for (int i = 1; i < 27; i++) pos[i] = pos[i - 1] + cnt[i - 1];
	for (int i = 0; i < n; i++) {
		p[pos[s[i] + 1 - 'a']++] = i;
	}
	c[p[0]] = 0;
	for (int i = 1; i < n; i++) {
		c[p[i]] = c[p[i - 1]];
		if (s[p[i]] != s[p[i - 1]]) c[p[i]]++;
	}
}
void count_sort(vi &p, vi &c, int k) {
	int n = sz(p);
	vi cnt(n), pos(n), new_p(n), new_c(n);
	for (int i = 0; i < n; i++) cnt[c[i]]++;
	for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
	for (int i = 0; i < n; i++) {
		new_p[pos[c[p[i]]]++] = p[i];
	}
	swap(p, new_p);
	for (int i = 1; i < n; i++) {
		new_c[p[i]] = new_c[p[i - 1]];
		if (c[p[i]] != c[p[i - 1]] || 
		c[(p[i] + (1 << k)) % n] != c[(p[i - 1] + (1 << k)) % n]) {
			new_c[p[i]]++;
		}
	}
	swap(c, new_c);
}

void solve() {
	string s;
	cin >> s;
	s += (char)('a' - 1);
	int n = sz(s), k = 0;
	vi p(n), c(n);
	// k = 0
	count_sort_zero(p, c, s);
	while ((1 << k) < n) {
		for (auto &x : p) {
			x -= (1 << k);
			if (x < 0) x += n;
		}
		count_sort(p, c, k++);
	}
	for (int i = 0; i < n; i++) {
		cout << p[i] << " \n"[i == n - 1];
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
