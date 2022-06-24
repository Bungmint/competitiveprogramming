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
	constexpr mint() { v = 0; }
	constexpr mint(ll _v) noexcept { v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
		if (v < 0) v += MOD; }
	constexpr bool operator==(const mint& o) const noexcept{
		return v == o.v; }
	constexpr friend bool operator!=(const mint& a, const mint& b) noexcept { 
		return !(a == b); }
	constexpr friend bool operator<(const mint& a, const mint& b) noexcept { 
		return a.v < b.v; }
	
	constexpr mint& operator+=(const mint& m) noexcept { 
		if ((v += m.v) >= MOD) v -= MOD; 
		return *this; }
	constexpr mint& operator-=(const mint& m) noexcept { 
		if ((v -= m.v) < 0) v += MOD; 
		return *this; }
	constexpr mint& operator*=(const mint& m) noexcept { 
		v = int((ll)v * m.v % MOD); return *this; }
	constexpr mint& operator/=(const mint& m) noexcept { return (*this) *= inv(m); }
	constexpr friend mint pow(mint a, ll p) noexcept {
		mint ans = 1; assert(p >= 0);
		for (; p; p /= 2, a *= a) if (p & 1) ans *= a;
		return ans; }
	constexpr friend mint inv(const mint& a) noexcept { assert(a.v != 0); 
		return pow(a, MOD - 2); }
		
	constexpr mint operator-() const noexcept { return mint(-v); }
	constexpr mint& operator++() noexcept { return *this += 1; }
	constexpr mint& operator--() noexcept { return *this -= 1; }
	constexpr friend mint operator+(mint a, const mint& b) noexcept { return a += b; }
	constexpr friend mint operator-(mint a, const mint& b) noexcept { return a -= b; }
	constexpr friend mint operator*(mint a, const mint& b) noexcept { return a *= b; }
	constexpr friend mint operator/(mint a, const mint& b) noexcept { return a /= b; }

	friend istream& operator>>(istream& is, mint& o){
		ll v; is >> v; o = mint(v); return is; }
	friend ostream& operator<<(ostream& os, const mint& o){
		os << o.v; return os; }
};

constexpr int MOD = 1e9 + 7; // 998244353;

template <typename M>
struct Combination {
	static const int mod = M::mod;
	vector<M> fact, invFact, inv;
	Combination(int N) noexcept {
		fact.resize(N + 1), invFact.resize(N + 1), inv.resize(N + 1);
		fact[0] = 1;
		for (int i = 1; i <= N; i++) {
				fact[i] =  fact[i - 1] * i;
		}
		inv[1] = 1;
		for (int i = 2; i <= N; ++i) {
			inv[i] = mod - (mod / i) * inv[mod % i];
		}
		invFact[0] = invFact[1] = 1;
		for (int i = 2; i <= N; ++i){
			invFact[i] = invFact[i - 1] * inv[i];
		}
	}
	constexpr M binom(int n, int k) const noexcept {
		if (n < k || n < 0) return 0;
		return fact[n] * invFact[k] * invFact[n - k];
	}
};

using Mint = mint<MOD,5>; // 5 is primitive root for both common mods
using Combo = Combination<Mint>;
using vmi = vector<Mint>;
