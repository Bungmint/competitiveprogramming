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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
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


/**
 * Description: Tests primality up to SZ [1, SZ)
 * Source: Benq
 * Time complexity: O(SZ log log SZ) or O(SZ)
 */
template <int SZ>
struct Sieve {
    bitset<SZ> is_prime;
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
Sieve<2'000'001> sieve;

/*
 * Solution:
 * Deterministic approach
 * Idea: Answer is always greater or equal to n/2
 * Thus, we can check all neighboring elements and see if the difference has an optimal answer
 * If not, since the maximum answer is >= n/2, we are done. (e.g. xoxoxo)
 * 
 * Nondeterministic appraoch
 * Idea: At least half of the array is included in the maximum set
 * Randomly choose 2 elements - probability of success 1/4
 * Each iteration takes O(n) 
 * Do 100 iteration - probability of failing very low
**/

// void solve() {
// 	int n;
// 	cin >> n;
// 	vi a(n);
// 	int odd{};
// 	for (auto &e : a) {
// 		cin >> e;
// 		if (e & 1) odd++;
// 	}
// 	int ans = max(odd, n - odd);
// 	auto factorize = [&](int x) -> vi {
// 		vi res;
// 		while (x > 1) {
// 			int p = sieve.lp[x];
// 			res.pb(p);
// 			while (x % p == 0) x /= p;
// 		}
// 		return res;
// 	};
// 	for (int i = 0; i < n - 1; i++) {
// 		int d = a[i + 1] - a[i];
// 		vi fac = factorize(d);
// 		for (auto &p : fac) {
// 			int k = a[i] % p;
// 			int cnt = 0;
// 			for (auto &e : a) if ((e - k) % p == 0) cnt++;
// 			ckmax(ans, cnt);
// 		}
// 	}
// 	cout << ans << '\n';
// }

void solve2() {
	int n;
	cin >> n;
	vi a(n);
	for (auto &e : a) cin >> e;
	if (n <= 2) {
		cout << n << '\n';
		return;
	}
	int ans{};
	auto factorize = [&](int x) -> vi {
		vi res;
		while (x > 1) {
			int p = sieve.lp[x];
			res.pb(p);
			while (x % p == 0) x /= p;
		}
		return res;
	};
	uniform_int_distribution<int> rnd(0, n - 1);
	for (int i = 0; i < 100; i++) {
		int j = rnd(rng);
		int k = rnd(rng);
		while (k == j) k = rnd(rng);
		if (j > k) swap(j, k);
		int d = a[k] - a[j];
		vi t = factorize(d);
		for (auto &p : t) {
			int r = a[k] % p;
			int cnt = 0;
			for (auto &e : a) if (e % p == r) cnt++;
			ckmax(ans, cnt);
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
		// solve();
		solve2();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
