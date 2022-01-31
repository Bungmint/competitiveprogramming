template<typename T>
struct BIT{
	int N;
	vector<T> bit;
	BIT(int n){bit.resize(n+1);N = n;}
	void upd(int i, T v){
		for (;i<=N;i+=i&-i) bit[i]+=v;	
	}
	T query(int i){
		T res = 0;
		for (;i>0;i-=i&-i) res+=bit[i];
		return res;
	}
};
