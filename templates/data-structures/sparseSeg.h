/**
 * Description: Dynamic Segment Tree with no lazy propagation
    * Half-open intervals are used for ranges 
 * Source: USACO Guide
 * Verification: https://oj.uz/problem/view/IZhO12_apple
 * Time Complexity: O(log SZ)
 * Memory Complexity: O(QlogSZ)
 */

template <typename T, int SZ = 1 << 20>
struct Node {
    T ans;
    Node *l, *r;  
    Node() : ans(T()), l(nullptr), r(nullptr) {}

    void upd(int ind, T val, int lx = 0, int rx = SZ) {
        if (rx - lx == 1) {
            ans = val;
            return;
        }
        int mx = (lx + rx) / 2;
        if (ind < mx) {
            if (!l) l = new Node();
            l->upd(ind, val, lx, mx);
        }else {
            if (!r) r = new Node();
            r->upd(ind, val, mx, rx);
        }
        ans = l->ans + r->ans;
    }
    T query(int lo, int hi, int lx = 0, int rx = SZ) {
        if (lo >= rx || hi <= lx) return T();
        if (lo <= lx && rx <= hi) return ans;
        int mx = (lx + rx) / 2;
        T lef = (l ? l->query(lo, hi, lx, mx) : T());
		T rig = (r ? r->query(lo, hi, mx, rx) : T());
        return lef + rig;
    }
    // For 2D updates
    void parallel_upd(int ind, Node* lef, Node* rig, int lx = 0, int rx = SZ) {
        if (rx - lx > 1) {
            int mx = (lx + rx) / 2;
            if (ind < mx) {
                if (!l) l = new Node();
                l->parllel_upd(ind, (lef ? lef->l : nullptr), (rig ? rig->l : nullptr), lx, mx);
            }else{
                if (!r) r = new Node();
                r->parllel_upd(ind, (lef ? lef->r : nullptr), (rig ? rig->r : nullptr), mx, rx);
            }
        }
        ans = (lef ? lef->ans : T()) + (rig ? rig->ans : T());
    }
};