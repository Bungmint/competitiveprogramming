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

string weekday[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int time_to_int() {
    string s;
    cin >> s;
    dbg(s);
    int h = (s[0] - '0') * 10 + (s[1] - '0');
    int m = (s[3] - '0') * 10 + (s[4] - '0');
    return 60 * h + m;
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

/**
 * Chinese Remainder Theorem Solver
 * Source: rkm0959's github
 * Verification: BOJ rkm0959's third problemset
 * Time complexity: O(log(A.se, B.se))
 */

pll crt(pll A, pll B) {
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

string int_to_time(int x) {
    int h = x / 60, m = x % 60;
    string res;
    if (h < 10) {
        res += '0';
        res += (char)('0' + h);
    }else{
        res += to_string(h);
    }
    res += ':';
    if (m < 10) {
        res += '0';
        res += (char)('0' + m);
    }else{
        res += to_string(m);
    }
    return res;
}


void solve() {
    int a1 = time_to_int(), a2 = time_to_int();
    int b1 = time_to_int(), b2 = time_to_int();
    pll res = crt({a1 % b1, b1}, {a2 % b2, b2});
    if (res.fi == -1 && res.se == -1) {
        cout << "Never" << '\n';
        return;
    }
    ll x = max(0LL, cdiv(max(a1, a2) - res.fi, res.se));
    ll y = x * res.se + res.fi;
    cout << weekday[(6 + y / 1440) % 7] << '\n';
    cout << int_to_time(y % 1440) << '\n';
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

