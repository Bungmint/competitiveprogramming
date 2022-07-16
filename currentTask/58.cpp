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
    bitset<SZ> is_prime;
    vi primes;
    Sieve() {
        is_prime.set();
        is_prime[0] = is_prime[1] = 0;
        for (int i = 4; i < SZ; i += 2) is_prime[i] = 0;
        for (int i = 3; i * i < SZ; i += 2) {
            if (is_prime[i]) {
                for (int j = i * i; j < SZ; j += 2 * i) {
                    is_prime[j] = 0;
                }
            }
        }
        for (int i = 0; i < SZ; i++) if (is_prime[i]) primes.pb(i);
    }
    // int lp[SZ];
    // Sieve() {
    //     for (int i = 2; i < SZ; i++) {
    //         if (lp[i] == 0) lp[i] = i, primes.pb(i);
    //         for (int p : primes) {
    //             if (p > lp[i] || i * p >= SZ) break;
    //             lp[i * p] = p;
    //         }
    //     }
    // }
};
Sieve<1000'000'010> sieve;
// learn miller-rabin

void solve() {
	int pos = 1;
	int prime = 0;
	for (int len = 2; len * len <= max(16, 200000000); len++) {
		for (int j = 1; j <= 4; j++) {
			pos += 2 * (len - 1);
			prime += sieve.is_prime[pos];
		}
		if (prime * 10 < 4 * len - 3) { cout << 2 * len - 1 << '\n'; return; }
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
