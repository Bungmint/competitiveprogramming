/**
 * Description: Generic Iterative Segment Tree 
 * Source: 
        * https://codeforces.com/blog/entry/18051
        * Benq
 * Verification:
 * Time Complexity: O(n) build, O(log n) updates/queries
 */

template <typename T>
struct SegTree{
    const T ID = {}; 
    T comb(const T& a, const T& b) { return a + b; }
    vector<T> seg; int n;
    SegTree(int _n) {
        n = _n;
        seg.assign(2 * n, ID);
    }
    SegTree(const vector<T>& vec) : seg(sz(vec) * 2, ID), n(sz(vec)) {
        for (int i = 0; i < n; i++) seg[i + n] = vec[i];
        for (int i = n - 1; i; i--) pull(i);
    }
    void pull(int p) { seg[p] = comb(seg[2 * p], seg[2 * p + 1]); }
    void upd(int p, const T& val) {
        seg[p += n] = val;
        for (p /= 2; p; p /= 2) pull(p);
    }
    void build() { for (int i = n - 1; i; i--) pull(i); }
    T query(int l, int r) { // query interval: [l, r), must be associative
        T ra = ID, rb = ID;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2) ra = comb(ra, seg[l++]);
            if (r % 2) rb = comb(seg[--r], rb);
        }
        return comb(ra, rb);
    }
};