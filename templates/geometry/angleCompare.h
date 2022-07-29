/**
 * Description: Sort points by arguments (CCW order) akin to atan2
    * which returns (-pi, pi] so points on negative x axis come last
 * Verification:
 * NEVER USE ATAN2, YOU WILL REGRET IT
 */

#include "point.h"

// Has to be int not bool
int half(const Point& x) {
    return x.se != 0 ? sgn(x.se) : -sgn(x.fi);
}
bool angle_cmp(const Point& a, const Point& b) {
    int A = half(a), B = half(b);
    return A == B ? sgn(cross(a, b)) > 0 : A < B;
}
