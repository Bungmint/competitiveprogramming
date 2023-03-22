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


// TODO: Test implementation
/**
 * Description: Implementation of 2D points using std::pair
 * Source: Benq
 * Verification: Various
 */

// #include "miscellaneous/template.h"

using T = ll; // Can be ll
constexpr T EPS = 0;
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

// #include "point.h"

// {unique line intersection} if exists
// {b.fi, b.se} if a and b are identical
// empty if they do not intersect
vP line_intersect(const Line& a, const Line& b) {
    T x = cross(a.fi, a.se, b.fi), y = cross(a.fi, a.se, b.se);
    if (sgn(x-y) == 0) return sgn(x) == 0 ? vP{b.fi, b.se} : vP{};
    return {(b.se*x-b.fi*y)/(x-y)};
}

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

void solve() {
    int n;
    cin >> n;
    vector<Line> lines(n), no_dupe;
    vP direction(n);
    Point zero = {0, 0};
    for (auto &[p1, p2] : lines) cin >> p1 >> p2;
    for (int i = 0; i < n; i++) direction[i] = lines[i].se - lines[i].fi;
    vi vis(n);    
    vi cc;
    auto dfs = y_combinator([&](auto self, int u) -> void {
                                cc.pb(u);
                                vis[u] = 1;
                                for (int i = 0; i < n; i++) {
                                    if (direction[i] == zero) continue;
                                    if (!vis[i] && sgn(cross(direction[i], direction[u])) == 0) {
                                        if (sz(seg_intersect(lines[i], lines[u]))) {
                                            self(i);    
                                        } 
                                    }
                                }
                            });
    for (int i = 0; i < n; i++) {
        if (!vis[i] && direction[i] != zero) {
            cc.clear();
            dfs(i);
            Point mx = {-2 * INF, -2 * INF}, mi = {2 * INF, 2 * INF};
            for (auto &id : cc) {
                ckmax(mx, lines[id].fi);
                ckmax(mx, lines[id].se);
                ckmin(mi, lines[id].fi);
                ckmin(mi, lines[id].se);
            }
            no_dupe.pb({mi, mx});
        }
    }
    dbg(no_dupe);
    int k = sz(no_dupe);
    int E = 0, V = 0;
    vector<set<Point>> seg(k);
    set<Point> st;
    for (int i = 0; i < k; i++) st.insert(no_dupe[i].fi), st.insert(no_dupe[i].se);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (on_seg(lines[j].fi, lines[i])) {
                seg[i].insert(lines[j].fi); 
            } 
            if (on_seg(lines[j].se, lines[i])) {
                seg[i].insert(lines[j].se);
            }
        }
    }
    V = sz(st);
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            if (sz(strict_intersect(no_dupe[i], no_dupe[j]))) {
                V++;
                E += 2;
            }
        }
    }
    for (int i = 0; i < k; i++) {
        E += sz(seg[i]) - 1;
    }
    vi visvis(k);
    int cc_cnt = 0;
    auto dfs_final = y_combinator([&](auto self, int u) -> void {
                                    visvis[u] = 1;
                                    for (int i = 0; i < k; i++) {
                                          if (!visvis[i] && sz(seg_intersect(no_dupe[u], no_dupe[i]))) {
                                              self(i);
                                          }
                                      }
                                  });
    for (int i = 0; i < k; i++) {
        if (!visvis[i]) {
            dfs_final(i);
            cc_cnt++;
        }
    }
    cout << E - V + cc_cnt << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;

	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

