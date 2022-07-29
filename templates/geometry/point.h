// TODO: Test implementation
/**
 * Description: Implementation of 2D points using std::pair
 * Source: Benq
 * Verification: Various
 */

#include "miscellaneous/template.h"

using T = ld; // Can be ll
constexpr T EPS = 1e-9;
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
