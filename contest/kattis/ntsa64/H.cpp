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


/**
 * Description: Implementation of 2D points using std::pair
 * Source: Benq
 * Verification: Various
 */
using T = ld; // Can be ll
constexpr T EPS = 1e-6;
using Point = pair<T, T>; 
using vP = vector<Point>;
using Line = pair<Point, Point>;
int sgn(T a) { return (a > EPS) - (a < -EPS); }
T sq(T a) { return a*a; }

bool close(const Point& a, const Point& b) {
    return sgn(a.fi-b.fi) == 0 && sgn(a.se-b.se) == 0;
}
T norm(const Point& a) { return sq(a.fi) + sq(a.se); }
T abs(const Point& a) { return sqrt(norm(a)); }
T arg(const Point& a) { return atan2(a.se, a.fi); }
Point conj(const Point& a) { return Point(a.fi, -a.se); }
Point perp(const Point& a) { return Point(-a.se, a.fi); }
Point dir(T ang) { return Point(cos(ang), sin(ang)); }

Point operator-(const Point& l) { return Point(-l.fi, -l.se); }
Point operator+(const Point& l, const Point& r) {
    return Point(l.fi+r.fi, l.se+r.se);
}
Point operator-(const Point& l, const Point& r) {
    return Point(l.fi-r.fi, l.se-r.se);
}
Point operator*(const Point& l, const T& r) {
    return Point(r*l.fi, r*l.se);
}
Point operator*(const T& l, const Point& r) {
    return r*l;
}
Point operator/(const Point& l, const T& r) {
    return Point(l.fi/r, l.se/r);
}
Point operator*(const Point& l, const Point& r) {
    return Point(l.fi*r.fi-l.se*r.se, l.fi*r.se+l.se*r.fi);
}
Point operator/(const Point& l, const Point& r) {
    return l*conj(r)/norm(r);
}
Point& operator+=(Point& l, const Point& r) { return l = l + r; }
Point& operator-=(Point& l, const Point& r) { return l = l - r; }
Point& operator*=(Point& l, const T& r)     { return l = l * r; }
Point& operator/=(Point& l, const T& r)     { return l = l / r; }
Point& operator*=(Point& l, const Point& r) { return l = l * r; }
Point& operator/=(Point& l, const Point& r) { return l = l / r; }

Point unit(const Point& p) { return p/abs(p); }
T dot(const Point& a, const Point& b) { return a.fi*b.fi + a.se*b.se; }
T dot(const Point& p, const Point& a, const Point& b) {
    return dot(a-p, b-p);
}
T cross(const Point& a, const Point& b) { return a.fi*b.se - a.se*b.fi; }
T cross(const Point& p, const Point& a, const Point& b) {
    return cross(a-p, b-p);
}
Point reflect(const Point& p, const Line& l) { // Check EGMO for the proof
    Point a = l.fi, b = l.se;
    Point d = b - a;
    return a + conj((p-a)/d)*d;
}
Point foot(const Point& p, const Line& l) {
    return (p+reflect(p, l))/T(2);
}
bool on_seg(const Point& p, const Line& l) {
    return sgn(cross(p, l.fi, l.se)) == 0 &&
           sgn(dot(p, l.fi, l.se)) <= 0;
}
istream& operator>>(istream& is, Point& a) {
    is >> a.fi >> a.se;
    return is;
}


/**
 * Description: Computes the intersection between two lines/segments
 * Source: https://victorlecomte.com/cp-geo.pdf
 * Verification: https://open.kattis.com/problems/segmentintersection
 */


// intersection point is in the interior of two segments
vP strict_intersect(const Line& a, const Line& b) {
    T a0 = cross(a.fi, a.se, b.fi), a1 = cross(a.fi, a.se, b.se);
    T b0 = cross(b.fi, b.se, a.fi), b1 = cross(b.fi, b.se, a.se);
    if (sgn(a0)*sgn(a1) < 0 && sgn(b0)*sgn(b1) < 0) {
        return {(b.se*a0-b.fi*a1)/(a0-a1)};
    }
    return {};
}

// intersection of segments
vP seg_intersect(const Line& a, const Line& b) {
    vP v = strict_intersect(a, b); 
    if (sz(v)) return v;
    set<Point> s;
    #define ins(x, y) if (on_seg(x, y)) s.insert(x);
    ins(a.fi, b); ins(a.se, b); ins(b.fi, a); ins(b.se, a);
    return {all(s)};
}

pii edge[] = {{0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 4}, {2, 5}, {2, 6}, {3, 5}, {3, 6}, {4, 6}};
ld area(const vP& poly) {
    ld area = 0;
    for (int i = 0; i < 7; i++) {
        int j = (i + 1) % 7;
        area += cross(poly[i], poly[j]);
    }
    return (area > EPS ? area : -area) / (ld)2.0;
}
bool is_simple(const vP& p) {
    bool ok = 1;
    for (auto &[i, j] : edge) {
        Line l1 = {p[i], p[i + 1]};
        Line l2 = {p[j], p[(j + 1) % 7]};
        ok &= !sz(seg_intersect(l1, l2));
        if (!ok) break;
    } 
    return ok;
}



void solve() {
    vP poly(7);
    for (auto &e : poly) {
        cin >> e;
    }
    ld p; 
    cin >> p;
    vi ind(7);
    iota(all(ind), 0);
    do {
        ld a;
        vP res;
        for (auto &i : ind) res.pb(poly[i]);
        if (!is_simple(res)) continue;
        a = area(res);
        ld prob = a * a * a;
        dbg(prob, p);
        if (prob - 64 * p < 64e-5 && 64 * p - prob < 64e-5) {
            for (int i = 0; i < 7; i++) cout << ind[i] + 1 << " \n"[i == 6];
            return;
        }
    }while(next_permutation(all(ind)));
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

