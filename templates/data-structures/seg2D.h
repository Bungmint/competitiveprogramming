/**
 * Description: Segment trees of Segment trees (SegTree inception)
 * Source: USACO Guide/Benq
 * Verification:
 * Time complexity: O(log^2 n) per query
 * Memory complexity: O(nlog^2 n) -> Too much for N = 1e5
 */

#include "sparseSeg.h"

template <typename T>
struct SegSeg {
    SparseSeg<T> seg;
    SegSeg* c[2];
    static constexpr int SZ = 1 << 17;
    SegSeg() {
        c[0] = c[1] = nullptr;
    }
    void upd(int x, int y, T v, int L = 0, int R = SZ) {
        if (R - L == 1) {
            seg.upd(y, v);
            return;
        }
        int M = (L + R) / 2;
        if (x < M) {
            if (!c[0]) c[0] = new SegSeg();
            c[0]->upd(x, y, v, L, M);
        }else{
            if (!c[1]) c[1] = new SegSeg();
            c[1]->upd(x, y, v, M, R);
        }
        seg.upd(y, v); // only for addition
        // seg.parallel_upd(y, c[0] ? &c[0]->seg : nullptr, c[1] ? &c[1]->seg : nullptr); 
    }
    void query(int x1, int x2, int y1, int y2, int L = 0, int R = SZ) {
        if (x1 >= R || x2 <= L) return T();
        if (x1 <= L && R <= x2) return seg.query(y1, y2);
        int M = (L + R) / 2;
        T res = 0;
        if (c[0]) res = res + c[0]->query(x1, x2, y1, y2, L, M);
        if (c[1]) res = res + c[1]->query(x1, x2, y1, y2, M, R);
        return res;
    }
};
