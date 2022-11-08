/**
 * Description: Segment trees of Segment trees
    * Half-open intervals are used
 * Source: USACO Guide
 * Verification:
 * Time complexity: O(log^2 n) per query
 * Memory complexity: O(nlog^2 n) -> Too much for N = 1e5
 */

#include "sparseSeg.h"

template <typename T>
struct SegSeg {
    Node<T> seg;
    SegSeg *l, *r;
    SegSeg() { l = r = nullptr; }
    void upd(int x, int y, T v, int lx, int rx) {
        if (rx - lx == 1) {
            seg.upd(y, val);
            return;
        }
        int mx = (lx + rx) / 2;
        if (x < mx) {
            if (!l) l = new SegSeg();
            l->upd(x, y, v, lx, mx);
        }else {
            if (!r) r = new SegSeg();
            r->upd(x, y, v, mx, rx);
        }
        seg.parllel_upd(y, (l ? &l->seg : nullptr), (r ? &r->seg : nullptr));
    }
    T query(int x1, int x2, int y1, int y2, int lx, int rx) {
        if (x1 >= rx || x2 <= lx) return T();
        if (x1 <= lx && rx <= x2) return seg.query(y1, y2);
        int mx = (lx + rx) / 2;
        T res = T();
        if (l) res += l->query(x1, x2, y1, y2, lx, mx);
        if (r) res += r->query(x1, x2, y1, y2, mx, rx);
        return res;
    }
};