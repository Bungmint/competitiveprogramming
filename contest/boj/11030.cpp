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
#define int long long
constexpr int MOD = 1e8;
constexpr int LIM = 100;

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
int bin_pow(int a, int b) {
	int r = 1;
	while (b) {
		if (b & 1) r *= a;
		a *= a;
		b >>= 1LL;
	}
	return r;
}
int mod_pow(int a, int b, int mod) {
	int r = 1;
	while (b) {
		if (b & 1) r = (1LL * r * a) % mod;
		a = (1LL * a * a) % mod;
		b >>= 1LL;
	}
	return r;
}
int power_tower(int base, int k, int mod) {
	if (k == 1) return base % mod;
	if (mod == 1) return 0;
	if (k <= 4) {
		if (k == 2 && base <= 100) return mod_pow(base, base, mod);
		else if (k == 3 && base == 2) return mod_pow(base, 4, mod);
		else if (k == 4 && base == 2) return mod_pow(base, 16, mod);
	}
	int nphi = phi(mod);
	int e = power_tower(base, k - 1, nphi);
	return mod_pow(base, e + 100 * nphi, mod);
}

void solve() {
	int a, b;
	cin >> a >> b;
	string s = to_string(power_tower(a, b, MOD));
	if (a == 1) {
		cout << s << '\n';
		return;
	}else if (b == 1) {
		cout << s << '\n';
		return;
	}else if (a <= 8 && b == 2) {
		cout << s << '\n';
		return;
	}else if (a == 2 && b == 3) {
		cout << s << '\n';
		return;
	}else if (a == 2 && b == 4) {
		cout << s << '\n';
		return;
	}
	
	while (sz(s) < 8) {
		s = "0" + s;
	}
	cout << s << '\n';
}

signed main() {
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
