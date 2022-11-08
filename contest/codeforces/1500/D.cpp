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



inline namespace Util {
inline namespace ModUtil {

constexpr int MOD = 1e9 + 7; // 998244353
int add(int a, const int& b) { 
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}
int mul(const int& a, const int& b) { return 1LL * a * b % MOD; }
int sub(int a, const int& b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}
int mod_pow(int a, int b) {
    int r = 1;
    while (b) {
        if (b & 1) r = mul(r, a);
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}
template <typename T>
T inverse(T a, T m) {
    T u = 0, v = 1, b = m;
    while (a) {
        T q = b / a;
        u -= q * v, b -= q * a;
        swap(u, v), swap(a, b);
    }
    assert(b == 1);
    if (u < 0) u += m;
    return u;
}

} // namespace ModUtil
} // namespace Util

pll crt_solver(pll A, pll B) {
	if (A.se == -1 || B.se == -1) return {-1, -1};
	if (A.se == 1 || B.se == 1) return A.se == 1 ? B : A;
	ll g = gcd(A.se, B.se), l = (A.se / g) * B.se;
	if ((B.fi - A.fi) % g) return {-1, -1};
	ll a = A.se / g, b = B.se / g;
	ll mul = (B.fi - A.fi) / g;
	mul = (mul * inverse(a, b)) % b;
	ll ret = mul * A.se + A.fi;
	ret %= l, ret = (ret + l) % l;
	return {ret, l};
}

void solve() {
	ll n, m;
	ll k, lc;
	cin >> n >> m >> k;
	lc = lcm(n, m);
	vi a(n), b(m);
	map<int, vi> days;
	for (int i = 0; i < n; i++) cin >> a[i], days[a[i]].pb(i);
	for (int i = 0; i < m; i++) cin >> b[i], days[b[i]].pb(i);
	vl cache;
	int cnt = 0;
	for (auto &[_, p] : days) {
		if (sz(p) == 1) continue;
		assert(sz(p) == 2);
		auto [res, __] = crt_solver({p[0], n}, {p[1], m});
		if (res != -1) cache.pb(res), cnt++;
	}
	ll l = 1, r = LINF, ans = 0;
	while (l <= r) {
		ll mid = l + (r - l) / 2;
		ll cur = cnt * (mid / lc);
		ll rem = mid % lc;
		cur += count_if(all(cache), [&](auto x){
			return x < rem;
		});
		if (mid - cur >= k) ans = mid, r = mid - 1;
		else l = mid + 1;
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
