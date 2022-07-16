// TODO: Test imp
/**
 * Description: Offline BIT with coordinate compression
 * Source: USACO Guide
 * Verification:
 * Time complexity: O(log n) per query
 * Memory complexity: O(n)
 */

template <typename T>
struct BIToff {
    bool mode = 0; vi ind;
    vector<T> bit;
    int at_most(int x) {
        return ub(all(ind), x) - ind.begin();
    }
    void upd(int x, T v) {
        if (!mode) {
            ind.pb(x);
            return;
        }
        int p = at_most(x);
        assert(p && ind[p - 1] == x);
        for (; p <= sz(ind); p += p & -p) bit[p] = bit[p] + v;
    }
    void init() {
        mode = 1;
        sort(all(ind)), ind.erase(unique(all(ind)), end(ind));
        bit.resize(sz(ind) + 1);
    }
    T sum(int x) {
        assert(mode);
        T res = T();
        int p = at_most(x);
        for (; p; p -= p & -p) res = res + bit[p];
        return res;
    }
    T query(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};