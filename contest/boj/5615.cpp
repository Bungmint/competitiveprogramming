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
#define eb emplace_back
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


/*
 * Description: Miller-Rabin Primality Test
 * Source: rkm0959
 * Verification: 
 * Time complexity: O(log^2 N)
**/
// #include "miscellaneous/template.h"

ll mul(ll a, ll b, ll m) {
    __int128_t T = a; T *= b;
    return (ll)(T % m);
}
ll bin_pow(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b & 1) res = mul(res, a, m), b--;
        a = mul(a, a, m);
        b >>= 1LL;
    }
    return res;
}
bool trial(ll n, ll a) {
    if (n % a == 0) return false;
    ll cnt = -1, d = n - 1;
    while (d % 2 == 0) cnt++, d /= 2;
    ll prod = bin_pow(a, d, n);
    if (prod == 1 || prod == n - 1) return true;
    while (cnt--) {
        prod = mul(prod, prod, n);
        if (prod == n - 1) return true;
    }
    return false;
}
bool is_prime(ll n) {
    if (n == 1) return false;
    ll testcase[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (auto &a : testcase) {
        if (n == a) return true;
        if (n > 40 && !trial(n, a)) return false;
    }
    if (n <= 40) return false;
    return true;
}

void solve() {
    int n;
    int cnt = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        cnt += is_prime(2 * x + 1);
    }
    cout << cnt << '\n';
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

