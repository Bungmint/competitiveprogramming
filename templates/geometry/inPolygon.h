/**
 * Description: Checks if P is inside/on/outside of a polygon
    * Returns -1,0,1 and both CCW and CW polygons are okay
 * Source: Benq
 * Verification:
 * Time Complexity: O(number of vertices in the polygon)
 */

#include "point.h" 

int in_polygon(const Point& p, const vP& poly) {
    int n = sz(poly), ans = 0;
    for (int i = 0; i < n; i++) {
        Point x = poly[i], y = poly[(i + 1) % n];
        if (x.se > y.se) swap(x, y);
        if (on_seg(p, {x, y})) return 0;
        ans ^= (x.se <= p.se && p.se < y.se && cross(p, x, y) > 0);
    }
    return ans ? -1 : 1;
}