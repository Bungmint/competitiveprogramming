/**
 * Description: Computes distance between P and line/segment AB
 * Source: Benq
 * Verification: https://open.kattis.com/problems/segmentdistance
 */

#include "point.h"

T line_dist(const Point& p, const Line& l) {
    return abs(cross(p, l.fi, l.se))/abs(l.se-l.fi);
}
T seg_dist(const Point& p, const Line& l) {
    if (sgn(dot(l.fi, p, l.se)) <= 0) return abs(p-l.fi);
    if (sgn(dot(l.se, p, l.fi)) <= 0) return abs(p-l.se);
    return line_dist(p, l);
}