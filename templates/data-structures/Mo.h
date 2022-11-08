/**
 * Description: Mo's Trick using the Hilbert curve
 * Source: 
 	* https://cp-algorithms.com/data_structures/sqrt_decomposition.html#mos-algorithm
	* https://en.wikipedia.org/wiki/Hilbert_curve#Applications_and_mapping_algorithms
 * Verification: Various
 * Time complexity: O(q\sqrt{n})
 */

ll hilbertorder(int x, int y) {
	constexpr int LOGN = 20, MAXN = 1 << LOGN;
	ll d = 0;
	for (int s = 1 << (LOGN - 1); s; s >>= 1) {
		bool rx = x & s, ry = y & s;
		d = d << 2 | (rx * 3 ^ static_cast<int>(ry));
		if (!ry) {
			if (rx) x = MAXN - x, y = MAXN - y;
			swap(x, y);
		}
	}
	return d;
}

struct Query {
    int l, r, idx;
    ll ord;
	inline void calcOrder() {
		ord = hilbertorder(l, r);
	}
};
inline bool operator<(const Query &a, const Query &b) {
	return a.ord < b.ord;
}

void remove(int idx){}
void add(int idx){}
ll get_answer(){}

vl mo(vector<Query> queries) {
   	vl answers(queries.size());
    for (auto &e : queries) e.calcOrder();
    sort(queries.begin(), queries.end());

    int cur_l = 0;
    int cur_r = -1;
    for (Query q : queries) {
        while (cur_l > q.l) { cur_l--; add(cur_l); }
        while (cur_r < q.r) { cur_r++; add(cur_r); }
        while (cur_l < q.l) { remove(cur_l); cur_l++; }
        while (cur_r > q.r) { remove(cur_r); cur_r--; }
        answers[q.idx] = get_answer();
    }
    return answers;
}