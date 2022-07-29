/**
 * Description: Computes the intersection between two lines/segments
 * Source: https://victorlecomte.com/cp-geo.pdf
 * Verification: https://open.kattis.com/problems/segmentintersection
 */

#include "point.h"

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