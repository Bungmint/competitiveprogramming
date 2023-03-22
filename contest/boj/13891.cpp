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

pll ex_gcd(ll a, ll b) {
	if (b == 0) return {1, 0};
	auto [x, y] = ex_gcd(b, a % b);
	ll z = (y + b) % b;
	if (z < 0) z += b;
	return {z, (1 - a * z) / b};
}

void solve() {
	ll ax, ay, bx, by, k;
	cin >> ax >> ay >> bx >> by >> k;
	if (ax == bx) {
		for (int i = 0; i < k; i++) cout << ax + 1 << ' ' << i << '\n';
		return;
	}
	if (ay == by) {
		for (int i = 0; i < k; i++) cout << i << ' ' << ay + 1 << '\n';
		return;
	}
	ll aax, aay, bbx, bby;
	bbx = bx - ax, bby = by - ay;
	ll g = gcd(bbx, bby);
	bbx /= g, bby /= g;
	aax = aay = 0;
	auto [x, y] = ex_gcd(abs(bby), abs(bbx));
	dbg(x, y, bbx, bby);
	if (bbx < 0) x = -x;
	if (bby > 0) y = -y;
	for (ll i = 0; i < k; i++) cout << (ax + bbx * i + x) << ' ' << (ay + bby * i + y) << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}