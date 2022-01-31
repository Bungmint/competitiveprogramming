template<typename T, int lg>
struct SparseTable{
	vector<vector<T>> spar;
	inline T merge(const T& a, const T& b){ // change this
		return min(a,b);
	} 
	SparseTable(const vector<T>& a){
		spar.assign(sz(a), vi(lg,0));
		for (int i=0;i<sz(a);++i) spar[i][0] = a[i];
		for (int j=1;j<lg;++j) for (int i=0;i+(1<<j)<=sz(a);++i)
			spar[i][j] = merge(spar[i][j-1], spar[i+(1<<(j-1))][j-1]);
	}
	T query(int a,int b){
		assert(a<=b);
		int dif = 31- __builtin_clz(b-a+1);
		return merge(spar[a][dif], spar[b-(1<<dif)+1][dif]);
	}
};