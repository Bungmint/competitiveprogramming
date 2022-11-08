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
 * Easy Geometry using complex library
 * Source: http://codeforces.com/blog/entry/22175, KACTL
    * https://codeforces.com/blog/entry/22175#comment-582178
    * Benq
 * Verification:
 * Not done
 */

using T = long double;
int sgn(T x) { return (x > 0) - (x < 0); }
T sq(T x) { return x * x; }

#define x() real()
#define y() imag()
using Point = complex<T>;
using vP = vector<Point>;

Point dir(T ang) { return polar((T)1, ang); }
Point unit(Point p) { return p / abs(p); }
T dot(Point a, Point b) {
    return a.x()*b.x() + a.y()*b.y();
}
T cross(Point a, Point b) {
    return a.x()*b.y() - a.y()*b.x();
}
T cross(Point p, Point a, Point b) {
    return cross(a - p, b - p);
}
Point reflect(Point p, Point a, Point b) {
    return a + conj((p-a)/(b-a))*(b-a);
}
Point foot(Point p, Point a, Point b) {
    return (a + reflect(p, a, b)) / T(2);
}
bool on_segment(Point p, Point a, Point b) {
    return cross(p, a, b) == 0 && dot(a-p, b-p) <= 0;
}

void solve() {
	vP trig(3);
	for (auto &e : trig) {
		int x, y; cin >> x >> y;
		e = {x, y};
	}
	cout << fixed << setprecision(20);
	cout << abs(cross(trig[2]-trig[0], trig[1]-trig[0])/T(2)) << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	#ifndef LOCAL
		freopen("area1.in", "r", stdin);
		freopen("area1.out", "w", stdout);
	#endif
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
