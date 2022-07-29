/**
 * Description: Multiply polynomials of ints for any modulus $<2^{31}$. 
 	* For XOR convolution ignore \texttt{m} within \texttt{fft}. 
 * Time: O(N\log N)
 * Source: 
 	* KACTL (https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/NumberTheoreticTransform.h)
 	* https://cp-algorithms.com/algebra/fft.html
 	* https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it
 	* maroonrk
 	* https://github.com/atcoder/ac-library/blob/master/atcoder/convolution.hpp
 	* Benq ORZ
 * Verification: 
	* https://judge.yosupo.jp/problem/convolution_mod
	* SPOJ polymul, CSA manhattan, CF Perfect Encoding
	* http://codeforces.com/contest/632/problem/E
 */

template<typename T> void ntt(vector<T>& a){
	int n = sz(a); assert((T::mod-1)%n==0);
	int L = 31 - __builtin_clz(n);
	static vector<T> rt(2, (T)1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++){
		rt.resize(n);
		T z[] = {1, pow(T::rt(), (ll)T::mod>>s)};
		for (int i = k; i < 2*k; i++)
			rt[i] = rt[i/2]*z[i&1];
	}
	vi rev(n);
	for (int i = 0; i < n; i++)
		rev[i] = (rev[i/2]|(i&1)<<L)/2;
	for (int i = 0; i < n; i++) 
		if (i < rev[i]) swap(a[rev[i]], a[i]);
	for (int k = 1; k < n; k *= 2){
		for (int i = 0; i < n; i += 2*k) 
			for (int j = 0; j < k; j++) {
			T z = rt[j+k]*a[i+j+k], &ai = a[i+j];
			a[i+j+k] = ai - z;
			a[i+j] += z;
		}
	}
}
template<typename T> vector<T> mul(const vector<T> &a, const vector<T> &b){ //only for nice primes
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
	vector<T> L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	for (int i = 0; i < n; i++) 
		out[-i & (n - 1)] = L[i] * R[i] / (T)n;
	ntt(out);
	return {out.begin(), out.begin() + s};
}
template<typename M, typename T> vector<M> mulMod(vector<T> x, vector<T> y) {
	auto con = [](const vector<T>& v) {
		vector<M> w(sz(v)); 
		for (int i = 0; i < sz(v); i++) w[i] = (int)v[i];
		return w;
	};
	return mul(con(x),con(y));
}
template<typename T> vector<T> MUL(const vector<T>& A, const vector<T>& B) { // arbitrary moduli
	using m0 = mint<(119<<23)+1,62>; auto c0 = mulMod<m0>(A, B);
	using m1 = mint<(5<<25)+1,  62>; auto c1 = mulMod<m1>(A, B);
	using m2 = mint<(7<<26)+1,  62>; auto c2 = mulMod<m2>(A, B);
	int n = sz(c0); vector<T> res(n);
	m1 r01 = 1/m1(m0::mod); m2 r02 = 1/m2(m0::mod), r12 = 1/m2(m1::mod);
	for (int i = 0; i < n; i++) { // a is remainder mod m0::mod, b fixes it mod m1::mod
		int a = c0[i].v, b = ((c1[i]-a)*r01).v, c = (((c2[i]-a)*r02 - b)*r12).v;
		res[i] = (T(c)*m1::mod+b)*m0::mod + a; // c fixes it mod m2::mod
	}
	return res;
}