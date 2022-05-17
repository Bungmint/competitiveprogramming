/**
 * Description: Performs range prefix sum queries and point updates. lower_bound returns the first prefix sum >= v
 * Source: Own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=693
 * Time Complexity: O(log n) for query and update
 * 0-indexing
 */
template <typename T>
struct BIT
{
	int N;
	vector<T> bit;
	BIT(int n)
	{
		bit.resize(n + 1);
		N = n;
	}
	void upd(int id, T v)
	{
		for (id++; id <= N; id += id & -id)
			bit[id] += v;
	}
	T query(int id)
	{
		T res = 0;
		for (id++; id > 0; id -= id & -id)
			res += bit[id];
		return res;
	}
	T query(int l, int r)
	{
		return l > r ? 0 : query(r) - query(l - 1);
	}
	T lower_bound(T v)
	{
		int id = 0;
		T sum = 0;
		int lg = 31 - __builtin_clz(N);
		for (int j = lg; ~j; j--)
		{
			if (id + (1 << j) <= N && sum + bit[id + (1 << j)] < v)
			{
				id += (1 << j);
				sum += bit[id];
			}
		}
		return id;
	}
};
