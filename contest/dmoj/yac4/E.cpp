// Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

#pragma region TEMPLATE

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
using ld = long double;
template <typename T, size_t SZ>
using ar = array<T, SZ>;
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

#define all(v) (v).begin(), (v).end()
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound

constexpr int INF = 1e9;
constexpr ll LINF = 1e18;
const ld PI = acos((ld)-1.0);
constexpr int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
constexpr bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
constexpr bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }
ll cdiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // divide a by b rounded down

#ifdef LOCAL
#include "miscellaneous/debug.h"
#else
#define dbg(...) 42
#endif

inline namespace RecursiveLambda {
	template <typename Fun>
	struct y_combinator_result {
		Fun fun_;
		template <typename T>
		explicit constexpr y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}
		template <typename... Args>
		constexpr decltype(auto) operator()(Args &&...args) const {
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun) {
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

#pragma endregion TEMPLATE


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
	static constexpr int mod = MOD;
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

	friend istream& operator>>(istream& is, mint& o) {
		ll v; is >> v; o = mint(v); return is; }
	friend ostream& operator<<(ostream& os, const mint& o) {
		os << o.v; return os; }
};

template <typename M>
struct Combination {
	static const int mod = M::mod;
	vector<M> fact, inv_fact, inv;
	Combination(int N) noexcept {
		fact.resize(N + 1), inv_fact.resize(N + 1), inv.resize(N + 1);
		fact[0] = 1;
		for (int i = 1; i <= N; i++) {
				fact[i] =  fact[i - 1] * i;
		}
		inv[1] = 1;
		for (int i = 2; i <= N; ++i) {
			inv[i] = mod - (mod / i) * inv[mod % i];
		}
		inv_fact[0] = inv_fact[1] = 1;
		for (int i = 2; i <= N; ++i){
			inv_fact[i] = inv_fact[i - 1] * inv[i];
		}
	}
	constexpr M binom(int n, int k) const noexcept {
		if (n < k || n < 0) return 0;
		return fact[n] * inv_fact[k] * inv_fact[n - k];
	}
};

constexpr int MOD = 1e9 + 7; // 998244353;
using Mint = mint<MOD, 5>; // 5 is primitive root for both common mods
using Mint998 = mint<998244353, 5>;
using Combo = Combination<Mint>;
using vmi = vector<Mint>;


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

int freq[1'000'100];
vector<Mint998> a(1 << 19);
vector<Mint998> b;

void solve() {
	int n; cin >> n;
	vi p(n);
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		a[p[i]] += 1;
	}
	b = mul(a, a);
	b.resize(1 << 20);
	for (int i = 0; i < n; i++) {
		b[2*p[i]] -= 1;
	}
	Mint ans = 1;
	for (int i = 0; i < sz(b); i++) {
		if (b[i].v) {
			dbg(b[i]);
			ans += 1;
			ans += pow(Mint(2), b[i].v / 2) - 2;
		}
	}
	cout << ans << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
