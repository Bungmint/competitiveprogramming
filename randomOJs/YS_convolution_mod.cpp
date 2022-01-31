// Problem: Convolution
// Contest: Library Checker
// URL: https://judge.yosupo.jp/problem/convolution_mod
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
using ld = long double;

#define all(v) (v).begin(), (v).end()
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define REP(a) F0R(_, a)

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v)
{
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}
void dbg_out()
{
    cerr << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

struct chash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
    size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

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
	int n = sz(a); assert((T::mod-1)%n==0);int L = 31-__builtin_clz(n);
	static vector<T> rt(2,(T)1);
	for (static int k = 2, s=2;k<n;k*=2, s++){
		rt.resize(n);
		T z[] = {1, pow(T::rt(), (ll)T::mod>>s)};
		FOR(i, k, 2*k) rt[i] = rt[i/2]*z[i&1];
	}
	vi rev(n);
	F0R(i, n) rev[i] = (rev[i/2]|(i&1)<<L)/2;
	F0R(i, n) if (i<rev[i]) swap(a[rev[i]], a[i]);
	for (int k=1;k<n;k*=2){
		for (int i=0;i<n;i+=2*k) F0R(j, k){
			T z = rt[j+k]*a[i+j+k], &ai = a[i+j];
			a[i+j+k] = ai-z;
			a[i+j]+=z;
		}
	}
}
template<typename T> vector<T> mul(const vector<T> &a, const vector<T> &b){ //only for nice primes
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
	vector<T> L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	F0R(i, n) out[-i & (n - 1)] = L[i] * R[i] / (T)n;
	ntt(out);
	return {out.begin(), out.begin() + s};
}
template<typename M, typename T> vector<M> mulMod(vector<T> x, vector<T> y) {
	auto con = [](const vector<T>& v) {
		vector<M> w(sz(v)); F0R(i,sz(v)) w[i] = (int)v[i];
		return w; };
	return mul(con(x),con(y));
}
template<typename T> vector<T> MUL(const vector<T>& A, const vector<T>& B) { // arbitrary moduli
	using m0 = mint<(119<<23)+1,62>; auto c0 = mulMod<m0>(A,B);
	using m1 = mint<(5<<25)+1,  62>; auto c1 = mulMod<m1>(A,B);
	using m2 = mint<(7<<26)+1,  62>; auto c2 = mulMod<m2>(A,B);
	int n = sz(c0); vector<T> res(n);
	m1 r01 = 1/m1(m0::mod); m2 r02 = 1/m2(m0::mod), r12 = 1/m2(m1::mod);
	F0R(i,n) { // a is remainder mod m0::mod, b fixes it mod m1::mod
		int a = c0[i].v, b = ((c1[i]-a)*r01).v, c = (((c2[i]-a)*r02-b)*r12).v;
		res[i] = (T(c)*m1::mod+b)*m0::mod+a; // c fixes it mod m2::mod
	}
	return res;
}

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<Mint> a(n), b(m), res;
	F0R(i, n){
		int t;
		cin >> t;
		a[i] = t;
	}
	F0R(i, m){
		int t;
		cin >> t, b[i] = t;
	}
	res = mul(a, b);
	F0R(i, sz(res)) cout << res[i]<<" ";
	cout <<"\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}