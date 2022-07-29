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

using Point = pair<ld, ld>;
using ld = long double;

Point operator+(const Point& a, const Point& b) {
	return {a.fi+b.fi, a.se+b.se};
}
Point operator-(const Point& a, const Point& b) {
	return {a.fi-b.fi, a.se-b.se};
}
Point operator*(const Point& a, const Point& b) {
	return {a.fi*b.fi-a.se*b.se, a.fi*b.se+a.se*b.fi};
}
ld dot(Point a, Point b) {
	return a.fi*b.fi + a.se*b.se;
}
ld cross(Point a, Point b) {
	return a.fi*b.se - a.se*b.fi;
}
ld abs(Point a) {
	return sqrt(ld(dot(a, a)));
}
istream& operator>>(istream& is, Point& p) {
	is >> p.fi >> p.se;
	return is;
}
constexpr ld EPS = 1e-9;

void solve() {
	Point x, y, z;
	cin >> x >> y >> z;
	ll dotp = dot(y-x, z-x);
	ll crossp = cross(y-x, z-x);
	ld theta = acos(clamp(dotp/abs(y-x)/abs(z-x), ld(-1), ld(1)));
	ld oth = 2*PI - theta;
	ld ang;
	ang = crossp >= 0 ? theta : oth;
	dbg(theta, oth);
	ang /= ld(2);
	dbg(ang);
	Point w = x + (y-x)*Point({cos(ang), sin(ang)});
	dbg(w);
	cout << fixed << setprecision(12);
	ld a = w.se - (ld)x.se;
	ld b = (ld)x.fi - w.fi;
	ld c = (ld)w.fi*(ld)x.se - (ld)x.fi*w.se;
	if (b > EPS) a /= b, c /= b, b /= b;
	cout << a << ' ' << b << ' ' << c << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
#define FILE "bisector"
#ifndef LOCAL
    freopen(FILE ".in", "r", stdin);
    freopen(FILE ".out", "w", stdout);
#endif
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
