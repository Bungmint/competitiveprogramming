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
 * Description: Basic I/O for the builtin 128bit integer
 * Source: https://codeforces.com/blog/entry/75044
 * Verification: https://atcoder.jp/contests/abc129/tasks/abc129_f
 */
using i128 = __int128_t;
istream& operator>>(istream& in, i128& num) { 
    i128 x = 0, f = 1;
    char ch = in.peek();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        in.get();
        ch = in.peek();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        in.get();
        ch = in.peek();
    }
    num = x * f;
    return in;
}
ostream& operator<<(ostream& out, i128 num) {
    string res;
    bool neg = num < 0;
    if (neg) num = -num;
    do {
        res += '0' + (num % 10);
        num /= 10;
    }while (num > 0);
    if (num < 0) {
        res += '-';
    }
    reverse(all(res));
    out << res;
    return out;
}

i128 ex_gcd(i128 a, i128 b, i128& x, i128& y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	i128 g = ex_gcd(b, a % b, x, y);
	x = (y + b) % b;
	if (x < 0) x += b;
	y = (1LL - (__int128_t)x * a) / b;
	return g;
}

i128 my_gcd(i128 a, i128 b) {
	if (b == 0) return a;
	else return my_gcd(b, a % b);
}

void solve() {
	i128 a, b, s;
	cin >> a >> b >> s;
	if (a == 0 || b == 0) {
		if (a == b) {
			cout << (s == 0 ? "YES" : "NO") << '\n';
			return;
		}
		if (a == 0) swap(a, b);
		cout << (s % a == 0 ? "YES" : "NO") << '\n';
		return;
	}
	i128 g = my_gcd(a, b);
	if (s % g || (a > s && b > s)) {
		cout << "NO\n";
		return;
	}
	if (a == s || b == s) {
		cout << "YES\n";
		return;
	}
	a /= g, b /= g, s /= g; // gcd(a, b) = 1
	i128 x, y;
	ex_gcd(a, b, x, y);
	x *= s, y *= s;
	dbg((b - x) / b);
	i128 t = (b - x) / b;
	if (x + b * t < 0) {
		t++;
	}else if (x + b * t >= b) {
		t--;
	}
	x += b * t, y -= a * t;
	for (i128 i = 0; ; i++) {
		i128 xx = x + i * b, yy = y - (i * a);
		if (xx <= 0) continue;
		if (yy <= 0) break;
		if (my_gcd(xx, yy) == 1) {
			cout << "YES\n";
			return;
		}
	}
	cout << "NO\n";

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
