/**
 * Description: modular arithmetic operations 
 * Source: 
	* KACTL
	* https://codeforces.com/blog/entry/63903
	* https://codeforces.com/contest/1261/submission/65632855 (tourist)
	* https://codeforces.com/contest/1264/submission/66344993 (ksun)
	* also see https://github.com/ecnerwala/cp-book/blob/master/src/modnum.hpp (ecnerwal)
 * Verification: 
	* https://open.kattis.com/problems/modulararithmetic
 */
template<int MOD, int RT> struct mint {
	static const int mod = MOD;
	static constexpr mint rt() { return RT; } // primitive root for FFT
	int v; explicit operator int() const { return v; } // explicit -> don't silently convert to int
	mint() { v = 0; }
	mint(ll _v) { v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
		if (v < 0) v += MOD; }
	friend bool operator==(const mint& a, const mint& b) { 
		return a.v == b.v; }
	friend bool operator!=(const mint& a, const mint& b) { 
		return !(a == b); }
	friend bool operator<(const mint& a, const mint& b) { 
		return a.v < b.v; }
	mint& operator+=(const mint& m) { 
		if ((v += m.v) >= MOD) v -= MOD; 
		return *this; }
	mint& operator-=(const mint& m) { 
		if ((v -= m.v) < 0) v += MOD; 
		return *this; }
	mint& operator*=(const mint& m) { 
		v = int((ll)v*m.v%MOD); return *this; }
	mint& operator/=(const mint& m) { return (*this) *= inv(m); }
	friend mint pow(mint a, ll p) {
		mint ans = 1; assert(p >= 0);
		for (; p; p /= 2, a *= a) if (p&1) ans *= a;
		return ans; }
	friend mint inv(const mint& a) { assert(a.v != 0); 
		return pow(a,MOD-2); }
		
	mint operator-() const { return mint(-v); }
	mint& operator++() { return *this += 1; }
	mint& operator--() { return *this -= 1; }
	friend mint operator+(mint a, const mint& b) { return a += b; }
	friend mint operator-(mint a, const mint& b) { return a -= b; }
	friend mint operator*(mint a, const mint& b) { return a *= b; }
	friend mint operator/(mint a, const mint& b) { return a /= b; }
};
using Mint = mint<MOD,5>; // 5 is primitive root for both common mods

ostream &operator<<(ostream &os, Mint x){
	os << x.v;
	return os;
}

const int N = 1e6+10;
Mint fact[N], inv_fact[N], inverse[N];

void precalc()
{
    for (int i = 0; i < N; i++)
    {
        if (i == 0)
            fact[i] = 1LL;
        else
            fact[i] =  fact[i - 1] *i;
    }
    inverse[1] = 1;
    for (int i=2;i<N;++i){
    	inverse[i] = MOD-(MOD/i)*inverse[MOD%i];
    }
    inv_fact[0] = inv_fact[1] = 1;
    for (ll i=2;i<N;++i){
    	inv_fact[i] = inv_fact[i-1] * inverse[i];
    }
}

Mint nCk(ll n, ll k)
{
    if (n < k)
        return 0LL;
    return fact[n] * inv_fact[k] * inv_fact[n - k];
}
