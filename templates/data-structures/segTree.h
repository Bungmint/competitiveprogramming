/**
 * Description: Generic segment tree without lazy propagation
 * Source: Inspired by Jiangly - https://codeforces.com//contest/1672/submission/154766851
 * Verification:
 * Time Complexity: O(n) build, O(log n) per update/query
 */

template <typename T, typename Merge = plus<T>>
struct SegTree{
	int sz;
	const Merge merge;
	vector<T> t;
	SegTree(int n) : merge(Merge()) {
		sz = 1;
		while (sz < n) sz *= 2;
		t.resize(sz * 2);
	}
	void build(const vector<T> &vec, int x, int l, int r) {
	    if (r - l == 1) {
	        if (l < (int)vec.size())
	            t[x] = vec[l];
	        return;
	    }
	    int mid = (l + r) / 2;
	    build(vec, 2 * x + 1, l, mid);
	    build(vec, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void build(const vector<T> &vec) {
	    build(vec, 0, 0, sz);
	}
	void upd(int i, const T& v, int x, int l, int r) {
	    if (r - l == 1) {
	        t[x] = v;
	        return;
	    }
	    int mid = (l + r) / 2;
	    if (i < mid)
	        upd(i, v, 2 * x + 1, l, mid);
	    else
	        upd(i, v, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void upd(int i, const T& v) {
	    upd(i, v, 0, 0, sz);
	}
	T query(int l, int r, int x, int lx, int rx) {
	    if (lx >= r || rx <= l)
	        return T();
	    if (lx >= l && rx <= r)
	        return t[x];
	    int mid = (lx + rx) / 2;
	    T a = query(l, r, 2 * x + 1, lx, mid);
	    T b = query(l, r, 2 * x + 2, mid, rx);
	    return merge(a, b);
	}
	T query(int l, int r) {
	    return query(l, r, 0, 0, sz);
	}
};