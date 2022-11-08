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
 * Description: Tests primality up to SZ [1, SZ)
 * Source: Benq
 * Time complexity: O(SZ log log SZ) or O(SZ)
 */

template <int SZ>
struct Sieve {
    vi primes;
    int lp[SZ];
    Sieve() {
        for (int i = 2; i < SZ; i++) {
            if (lp[i] == 0) lp[i] = i, primes.pb(i);
            for (int p : primes) {
                if (p > lp[i] || i * p >= SZ) break;
                lp[i * p] = p;
            }
        }
    }
};
Sieve<1'000'001> sieve;
int phi[1'000'001], MOD;
void precalc() {
	phi[1] = 1;
	for (int i = 2; i <= 1000000; i++) {
		phi[i] = i;
		int ii = i;
		while (ii > 1) {
			int p = sieve.lp[ii];
			phi[i] -= phi[i] / p;
			while (ii % p == 0) ii /= p;
		}
	}
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
int mod_pow(int a, int b, int mod) {
	int r = 1;
	while (b) {
		if (b & 1) r = (1LL * r * a) % mod;
		a = (1LL * a * a) % mod;
		b >>= 1;
	}
	return r;
}




void solve() {
	int n;
	cin >> n;
	vi bases(n);
	for (auto &e : bases) cin >> e;
	auto restricted_pow = [&](int a, int b) -> int {
		if (a >= 2 && b >= 7) return 100;
		if (a >= 3 && b >= 5) return 100;
		if (a >= 4 && b >= 4) return 100;
		if (a >= 5 && b >= 3) return 100;
		if (a >= 10 && b >= 2) return 100;
		return bin_pow(a, b);
	};
	auto check = y_combinator([&](auto self, int pos) -> int {
		if (n - pos >= 4) return 100;
		if (pos == n - 1) return bases[n - 1];
		return restricted_pow(bases[pos], self(pos + 1));
	});
	auto calc = y_combinator([&](auto self, int pos, int mod) -> int {
		if (mod == 1) return 0;
		if (pos == n - 1) return bases[n - 1] % mod;
		int expo = check(pos + 1);
		if (expo < 100) {
			return mod_pow(bases[pos], expo, mod);
		}else{
			int mod_phi = phi[mod];
			int next_expo = self(pos + 1, mod_phi);
			// dbg(mod_phi, next_expo);
			while (next_expo <= 100) next_expo += mod_phi;
			return mod_pow(bases[pos], next_expo, mod);
		}
	});
	for (int i = n - 1; i >= 0; i--) {
		if (bases[i] == 1) {
			n = i;
		}
	}
	if (n == 0) {
		cout << 1 % MOD << '\n';
		return;
	}else cout << calc(0, MOD) << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	precalc();
	int testcase = 1;
	cin >> testcase >> MOD;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
