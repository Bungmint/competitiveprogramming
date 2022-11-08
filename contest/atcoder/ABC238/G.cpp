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
Sieve<1'000'100> sieve;

using ull = unsigned long long;
ull H[1'000'100], hsh[200'100];
int pref_cnt[200'100], a[200'100], pref[200'100], freq[1'000'100], n, q;
bool ans[200'100];
vpi pr[200'100];
pii qs[200'100];

void solve() {
	cin >> n >> q;
	int max_p = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		while (a[i] > 1) {
			int p = sieve.lp[a[i]], cnt = 0;
			while (a[i] % p == 0) {
				a[i] /= p; cnt++;
			}
			cnt %= 3;
			if (cnt) pr[i].pb({p, cnt});
			ckmax(max_p, p);
		}
	}
	for (int i = 0; i < q; i++) {
		cin >> qs[i].fi >> qs[i].se;
		qs[i].fi--;
	}
	memset(ans, 1, sizeof(ans));
	for (int iter = 0; iter < 10; iter++) {
		for (int i = 1; i <= max_p; i++) H[i] = rng(), freq[i] = 0;
		for (int i = 1; i <= n; i++) {
			hsh[i] = hsh[i - 1];
			for (auto &[p, cnt] : pr[i]) {
				int bef = freq[p];
				int nxt = (bef + cnt) % 3;
				hsh[i] += (nxt-bef)*H[p];
				freq[p] = nxt;
			}
		}
		for (int i = 0; i < q; i++) {
			ans[i] &= (hsh[qs[i].fi] == hsh[qs[i].se]);
		}
	}
	for (int i = 0; i < q; i++) {
		cout << (ans[i] ? "Yes" : "No") << '\n';
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
