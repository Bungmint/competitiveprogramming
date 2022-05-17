/**
 * Description: Data structure that supports range idempotent queries on a static array
 * Source: Own
 * Verification:
 * Time Complexity: O(nlogn) build, O(1) query
 */
template<typename T>
struct SparseTable{
	vector<vector<T>> spar;
	inline T merge(const T& a, const T& b) { // change this
		return min(a, b);
	} 
	SparseTable(const vector<T>& a) {
		int lg = 32 - __builtin_clz(sz(a));
		spar.assign(lg, vi(sz(a), 0));
		for (int i = 0; i < sz(a); ++i) spar[0][i] = a[i];
		for (int j = 1; j < lg; ++j) 
			for (int i = 0; i + (1 << j) <= sz(a); ++i)
				spar[j][i] = merge(spar[j - 1][i], spar[j - 1][i + (1 << (j - 1))]);
	}
	SparseTable(T a[], int n) {
		int lg = 32 - __builtin_clz(n);
		spar.assign(lg, vi(n, 0));
		for (int i = 0; i < n; ++i) spar[0][i] = a[i];
		for (int j = 1; j < lg; ++j) 
			for (int i = 0; i + (1 << j) <= n; ++i)
				spar[j][i] = merge(spar[j - 1][i], spar[j - 1][i + (1 << (j - 1))]);
	}
	T query(int a, int b) {
		assert(a <= b);
		int dif = 31 - __builtin_clz(b - a + 1);
		return merge(spar[dif][a], spar[dif][b - (1 << dif) + 1]);
	}
};