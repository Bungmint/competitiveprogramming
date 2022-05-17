/**
 * Description: Offline BIT with coordinate compression
 * Source: USACO Guide
 * Verification:
 * Time complexity: O(log n) per query
 * Memory complexity: O(n)
 */
template <typename T>
struct BIToff {
    bool mode = 0;
    using V = int;
    vector<V> ind;
    vector<T> bit;
    int atMost(V x) {
        return ub(all(ind), x) - ind.begin();
    }
    void upd(V x, T v) {
        if (!mode) {
            ind.pb(x);
            return;
        }
        int p = atMost(x);
        assert(p && ind[p - 1] == x);
        for (; p <= sz(ind); p += p & -p) bit[p] = bit[p] + v;
    }
    void init() {
        mode = 1;
        sort(all(ind)), ind.resize(unique(all(ind)) - ind.begin());
    }
    T sum(V x) {
        assert(mode);
        T res = T();
        int p = atMost(x);
        for (; p; p -= p & -p) res = res + bit[p];
        return res;
    }
    T query(V l, V r) {
        return sum(r) - sum(l - 1);
    }
};