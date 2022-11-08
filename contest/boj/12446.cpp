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

int phi(int n) {
	int r = n;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			r -= r / i;
			while (n % i == 0) n /= i;
		}
	}
	if (n > 1) r -= r / n;
	return r;
}
int mod_pow(int a, int b, int mod) {
	int r = 1;
	while (b) {
		if (b & 1) r = (1LL * a * r) % mod;
		a = (1LL * a * a) % mod;
		b >>= 1;
	}
	return r;
}
int bin_pow(int a, int b) {
	int r = 1;
	while (b) {
		if (b & 1) r *= a;
		a *= a;
		b >>= 1;
	}
	return r;
}


/*
 * x --> x^x in 1 hour
 * A bacteria, B hours, Modulo C
 */

void solve(int tc) {
	int a, b, c;
	cin >> a >> b >> c;
	if (a == 1) {
		cout << "Case #" << tc << ": " << 1 % c << '\n';
		return;
	}
	vi mods{c}, ind(c + 1);
	while (mods.back() > 1) mods.pb(phi(mods.back()));
	for (int i = 0; i < sz(mods); i++) {
		ind[mods[i]] = i;
	}
	dbg(mods);
	vector<vi> dp(b + 1, vi(sz(mods), -1));
	auto dfs = y_combinator([&](auto self, int hour, int mod) -> int {
		int& state = dp[hour][ind[mod]];
		if (state != -1) return state;
		if (hour == b - 1) return state = mod_pow(a, a, mod);
		if (hour == b - 2 && a <= 3) {
			int t = bin_pow(a, a);
			return state = mod_pow(t, t, mod);
		}
		if (mod == 1) return state = 0;
		int mod_phi = mods[ind[mod] + 1];
		int base = self(hour + 1, mod);
		int exponent = self(hour + 1, mod_phi);
		while (exponent <= 100) exponent += mod_phi;
		return state = mod_pow(base, exponent, mod);
	});
	cout << "Case #" << tc << ": " << dfs(0, c) << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	for (int tc = 1; tc <= testcase; tc++) {
		solve(tc);
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
