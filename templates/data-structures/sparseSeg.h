/**
 * Description: Dynamic Segment Tree with no lazy propagation
 * Source: USACO Guide
 * Verification: https://oj.uz/problem/view/IZhO12_apple
 * Time Complexity: O(log SZ)
 * Memory Complexity: O(QlogSZ)
 */
template <typename T> 
struct SparseSeg {
    T val = T();
    SparseSeg<T>* c[2];
    SparseSeg() { c[0] = c[1] = nullptr; }
    using V = int;
    static constexpr V SZ = 1 << 17; // change SZ accordingly
    
    void upd(V ind, T v, V L = 0, V R = SZ) {
        if (R - L == 1) {
            val = val + v;
            return;
        }
        V M = (L + R) / 2;
        if (ind < M) {
            if (!c[0]) c[0] = new SparseSeg();
            c[0]->upd(ind, v, L, M);
        }else{
            if (!c[1]) c[1] = new SparseSeg();
            c[1]->upd(ind, v, M, R);
        }
        val = T();
        for (int i : rep(2)) if (c[i]) val = val + c[i]->val;
    }
    T query(V lo, V hi, V L = 0, V R = SZ) {
        if (hi <= L || lo >= R) return T();
        if (lo <= L && R <= hi) return val;
        V M = (L + R) / 2;
        T res = T();
        if (c[0]) res = res + c[0]->query(lo, hi, L, M);
        if (c[1]) res = res + c[1]->query(lo, hi, M, R);
        return res;
    }
    void parallelUpd(V ind, SparseSeg* c0, SparseSeg* c1, V L = 0, V R = SZ) {
        if (R - L > 1) {
            V M = (L + R) / 2;
            if (ind < M) {
                if (!c[0]) c[0] = new SparseSeg();
                c[0]->parallelUpd(ind, c0 ? c0->c[0] : nullptr, c1 ? c1->c[0] : nullptr, L, M);
            }else{
                if (!c[1]) c[1] = new SparseSeg();
                c[1]->parallelUpd(ind, c0 ? c0->c[1] : nullptr, c1 ? c1->c[1] : nullptr, M, R);
            }
        }
        val = (c0 ? c0->val : T()) + (c1 ? c1->val : T());
    }
};