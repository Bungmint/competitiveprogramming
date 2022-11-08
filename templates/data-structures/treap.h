/**
 * Description: Randomized BBST
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/Treap%20(15.3).h
 * Verification: https://codeforces.com/gym/102787
 * Time complexity: O(log n) per split/merge
 */

using pt = struct Treap*;
struct Treap {
    int pri, val; pt c[2]; // basics
    int sz; ll sum; // range
    bool flip = 0; // lazy
    Treap(int _val) {
        pri = rng(), sum = val = _val;
        sz = 1;
        c[0] = c[1] = nullptr;
    }
    ~Treap() {
        for (int i = 0; i < 2; i++) delete c[i];
    }
};

// Just for myself: If you are going to change what the pointer is pointing, use pt&

int get_size(pt x) { return x ? x->sz : 0; }
ll get_sum(pt x) {return x ? x->sum : 0; }
void prop(pt x) {
    if (!x || !x->flip) return;
    swap(x->c[0], x->c[1]);
    x->flip = 0;
    for (int i = 0; i < 2; i++) if (x->c[i]) x->c[i]->flip ^= 1;
}
void calc(pt x) {
    pt a = x->c[0], b = x->c[1];
    prop(a), prop(b);
    x->sz = 1 + get_size(a) + get_size(b);
    x->sum = x->val + get_sum(a) + get_sum(b);
}
pair<pt, pt> split(pt t, int v) { // <= v goes to the left
    if (!t) return {t, t};
    prop(t);
    if (t->val > v) {
        auto [l, r] = split(t->c[0], v);
        t->c[0] = r;
        calc(t);
        return {l, t};
    }else{
        auto [l, r] = split(t->c[1], v);
        t->c[1] = l;
        calc(t);
        return {t, r};
    }
}
pair<pt, pt> split_size(pt t, int v) { // size v goes to the left
    if (!t) return {t, t};
    prop(t);
    if (get_size(t->c[0]) >= v) {
        auto [l, r] = split_size(t->c[0], v);
        t->c[0] = r;
        calc(t);
        return {l, t};
    }else{
        auto [l, r] = split_size(t->c[1], v - get_size(t->c[0]) - 1);
        t->c[1] = l;
        calc(t);
        return {t, r};
    }
}
pt merge(pt l, pt r) { // all keys in l < all keys in r
    if (!l || !r) return l ? l : r;
    prop(l), prop(r); 
    pt t;
    if (l->pri > r->pri) {
        l->c[1] = merge(l->c[1], r);
        t = l;
        calc(t);
        return t;
    }else{
        r->c[0] = merge(l, r->c[0]);
        t = r;
        calc(t);
        return t;
    }
}
void heapify(pt t) {
    if (!t) return;
    pt mx = t;
    for (int i = 0; i < 2; i++) {
        if (t->c[i] && t->c[i]->pri > mx->pri) mx = t->c[i];
    }
    if (mx != t) {
        swap(mx->pri, t->pri);
        heapify(mx);
    }
}
pt build(vi& a, int l, int r) {
    if (r == l) return nullptr;
    int m = (l + r) / 2;
    pt t = new Treap(a[m]);
    t->c[0] = build(a, l, m);
    t->c[1] = build(a, m + 1, r);
    heapify(t);
    calc(t);
    return t;
}