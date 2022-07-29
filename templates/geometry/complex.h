/**
 * Easy Geometry using complex library
 * Source: http://codeforces.com/blog/entry/22175, KACTL
    * https://codeforces.com/blog/entry/22175#comment-582178
    * Benq
 * Verification:
 */

using T = ld;
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

