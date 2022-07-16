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
constexpr int MX = 1e6 + 19;
Sieve<MX + 199> sieve;
int expsum[MX + 199];
int mi[MX + 199][2];

void precalc() {
	for (int i = 2; i <= MX; i++) {
		int p = sieve.lp[i];
		expsum[i] = expsum[i / p] + 1;
	}
	memset(mi, -1, sizeof(mi));
}

void solve() {
	int n;
	cin >> n;
	vi a(n);
	for (auto &e : a) cin >> e;
	auto ins = [&](int g, int i) -> void {
		for (int j = 0; j < 2; j++) {
			int& k = mi[g][j];
			if (k == -1) { k = i; return; }
			else{
				if (expsum[a[k] / g] > expsum[a[i] / g]) {
					swap(k, i);
				}else if (expsum[a[k] / g] == expsum[a[i] / g] && k > i) {
					swap(k, i);
				}
			}
		}
	};
	for (int i = 0; i < n; i++) {
		int e = a[i];
		vi divisors{1};
		while (e > 1) {
			int p = sieve.lp[e];
			int pp = 1;
			int k = sz(divisors);
			while (e % p == 0) {
				e /= p;
				pp *= p;
				for (int j = 0; j < k; j++) divisors.pb(divisors[j] * pp);
			}
		}
		for (int d : divisors) {
			ins(d, i);
		}
	}
	for (int i = 0; i < n; i++) {
		int e = a[i];
		vi divisors{1};
		while (e > 1) {
			int p = sieve.lp[e];
			int pp = 1;
			int k = sz(divisors);
			while (e % p == 0) {
				e /= p;
				pp *= p;
				for (int j = 0; j < k; j++) divisors.pb(divisors[j] * pp);
			}
		}
		int ans{-1}, mini{INF};
		for (int d : divisors) {
			int z = expsum[a[i] / d];
			for (int j = 0; j < 2; j++) {
				int k = mi[d][j];
				if (k == -1 || k == i) continue;
				int v = z + expsum[a[k] / d];
				if (ckmin(mini, v)) ans = k;
				else if (mini == v && ans > k) ans = k;
			}
		}
		dbg(mini);
		cout << ans + 1 << '\n';
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	precalc();
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
