/**
 * Description: A fully persistent data structure that supports range updates/queries
 * Source: Benq
 * Verification: https://cses.fi/problemset/task/1737
 * Time Complexity: O(log n) time per update/query, O(log n) memory per query
 */

template <typename T, int SZ>
struct PST {
    struct Node {
        T val;
        int c[2];
        Node() {
            val = T();
            c[0] = c[1] = 0;
        }
    };
    static const int LIM = 2e7;
    Node d[LIM];
    int nxt = 0;
    int copy(int t) { d[nxt] = d[t]; return nxt++; }
    T comb(const T& a, const T& b) { return a + b; }
    void pull(int c) { d[c].val = comb(d[d[c].c[0]].val, d[d[c].c[1]].val); }
    T query(int lo, int hi, int t, int l, int r) {
        if (lo >= r || hi <= l) return T();
        if (lo <= l && r <= hi) return d[t].val;
        int m = (l + r) / 2;
        T lef = query(lo, hi, d[t].c[0], l, m);
        T rig = query(lo, hi, d[t].c[1], m, r);
        return comb(lef, rig);
    }
    int upd(int i, const T& v, int t, int l, int r) {
        int x = copy(t);
        if (r - l == 1) {
            d[x].val = v;
            return x;
        }
        int m = (l + r) / 2;
        if (i < m) {
            d[x].c[0] = upd(i, v, d[x].c[0], l, m);
        }else{
            d[x].c[1] = upd(i, v, d[x].c[1], m, r);
        }
        pull(x);
        return x;
    }
    int build(const vector<T>& a, int l, int r) {
        int c = nxt++;
        if (r - l == 1) {
            if (l < sz(a)) d[c].val = a[l];
            return c;
        }
        int m = (l + r) / 2;
        d[c].c[0] = build(a, l, m);
        d[c].c[1] = build(a, m, r);
        pull(c);
        return c;
    }
    vi rts;
    void update_time(int ti, int i, const T& v) {
        rts.pb(upd(i, v, rts[ti], 0, SZ));
    }
    void build(const vector<T>& a) {
        rts.pb(build(a, 0, SZ));
    }
    T query_time(int ti, int lo, int hi) {
        return query(lo, hi, rts[ti], 0, SZ);
    }
};