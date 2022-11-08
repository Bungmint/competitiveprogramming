// Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
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
template <typename T>
ostream &operator<<(ostream &os, const deque<T> &v) {
	os << vector<T>(all(v));
	return os;
}
template <typename T, typename S, typename C>
ostream &operator<<(ostream &os, priority_queue<T, S, C> pq) {
	vector<T> v;
	while (sz(pq)) {
		v.pb(pq.top());
		pq.pop();
	}
	os << v;
	return os;
}
void dbg_out()
{
	cerr << "\033[0m" << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
	cerr << ' ' << H;
	dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "\033[1;35m" << __func__ << ':' << __LINE__ << " (" << #__VA_ARGS__ << "):\033[33m", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

inline namespace RecursiveLambda
{
	template <typename Fun>
	struct y_combinator_result
	{
		Fun fun_;
		template <typename T>
		explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}
		template <typename... Args>
		decltype(auto) operator()(Args &&...args)
		{
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun)
	{
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

inline namespace Range {
	class ForwardRange {
		int src, dst;

	  public:
	  	explicit constexpr ForwardRange(const int l, const int r) : src(l), dst(r) {}
		explicit constexpr ForwardRange(const int n) : src(0), dst(n) {}
		constexpr ForwardRange begin() const { return *this; }
		constexpr monostate end() const { return {}; }
		constexpr bool operator!=(monostate) const { return src < dst; }
		constexpr void operator++() const {}
		constexpr int operator*() { return src++; }
	};
	class BackwardRange {
		int src, dst;

	  public:
	  	explicit constexpr BackwardRange(const int l, const int r) : src(r), dst(l) {}
		explicit constexpr BackwardRange(const int n) : src(n), dst(0) {}
		constexpr BackwardRange begin() const { return *this; }
		constexpr monostate end() const { return {}; }
		constexpr bool operator!=(monostate) const { return src > dst; }
		constexpr void operator++() const {}
		constexpr int operator*() { return --src; }
	};
	using rep = ForwardRange;
	using per = BackwardRange;
};

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

constexpr int MOD = 1e9 + 7; // 998244353;
using Mint = mint<MOD, 5>; // 5 is primitive root for both common mods
using Combo = Combination<Mint>;
using vmi = vector<Mint>;

/**
 * Description: Tests primality up to SZ [1, SZ)
 * Source: Benq
 * Time complexity: O(SZ log log SZ) or O(SZ)
 */
template <int SZ>
struct Sieve {
    vi primes;
    int lp[SZ];
    Sieve() {
        for (int i : rep(2, SZ)) {
            if (lp[i] == 0) lp[i] = i, primes.pb(i);
            for (int p : primes) {
                if (p > lp[i] || i * p >= SZ) break;
                lp[i * p] = p;
            }
        }
    }
};

/*
 * Description: Generic Iterative Segment Tree 
 * Source: 
        * https://codeforces.com/blog/entry/18051
        * Benq
 * Verification:
 * Time Complexity: O(n) build, O(log n) updates/queries
**/
template <typename T>
struct SegTree{
    const T ID = {1}; 
    T comb(const T& a, const T& b) { return a * b; }
    vector<T> seg; int n;
    SegTree(int _n) {
        n = _n;
        seg.assign(2 * n, ID);
    }
    SegTree(const vector<T>& vec) : seg(sz(vec) * 2, ID), n(sz(vec)) {
        for (int i = 0; i < n; i++) seg[i + n] = vec[i];
		build();
    }
	void build() { for (int i = n - 1; i; i--) pull(i); }
    void pull(int p) { seg[p] = comb(seg[2 * p], seg[2 * p + 1]); }
    void upd(int p, const T& val) {
		p += n;
        seg[p] = comb(seg[p], val);
        for (p /= 2; p; p /= 2) pull(p);
    }
    T query(int l, int r) { // query interval: [l, r), must be associative
        T ra = ID, rb = ID;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2) ra = comb(ra, seg[l++]);
            if (r % 2) rb = comb(seg[--r], rb);
        }
        return comb(ra, rb);
    }
};
Sieve<1000001> sieve;
int id[1000001];
Mint pinv[1000001];
vector<vi> ind;

void precalc() {
	for (int i : rep(sz(sieve.primes))) {
		id[sieve.primes[i]] = i;
		pinv[sieve.primes[i]] = Mint(1) / Mint(sieve.primes[i]);
		// pinv[sieve.primes[i] - 1] = Mint(1) / Mint(sieve.primes[i] - 1);
	}
	ind.resize(sz(sieve.primes));
}

void solve()
{
	int n;
	cin >> n;
	vi a(n);
	vector<vi> primes(n); 
	vector<vpi> qs(n);
	SegTree<Mint> seg(n);
	for (int i : rep(n)) {
		cin >> a[i];
		int x = a[i];
		while (x > 1) {
			int p = sieve.lp[x];
			while (x % p == 0) {
				x /= p;
			}
			ind[id[p]].pb(i);
			primes[i].pb(p);
		}
		seg.seg[i + n] = a[i];
	}
	seg.build();
	for (int i : rep(sz(ind))) {
		if (sz(ind[i]) == 0) continue;
		reverse(all(ind[i]));
		int j = ind[i].back();
		int p = sieve.primes[i];
		seg.upd(j, pinv[p] * (p - 1));
	}
	int q;
	cin >> q;
	for (int i : rep(q)) {
		int l, r;
		cin >> l >> r; l--, r--;
		qs[l].pb({r, i});
	}
	vmi ans(q);
	for (int l : rep(n)) {
		for (auto &[r, i] : qs[l]) {
			ans[i] = seg.query(l, r + 1);
		}
		for (auto &p : primes[l]) {
			ind[id[p]].pop_back();
			if (sz(ind[id[p]])) {
				int nxt = ind[id[p]].back();
				seg.upd(nxt, pinv[p] * (p - 1));
			}
		}
	}
	for (int i : rep(q)) cout << ans[i] << "\n";

}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	precalc();
	// cin >> testcase;
	while (testcase--)
	{
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
