// Problem: E. Coins Exhibition
// Contest: Codeforces - Codeforces Round #468 (Div. 1, based on Technocup 2018 Final Round)
// URL: https://codeforces.com/problemset/problem/930/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2022 Youngmin Park. All rights reserved.
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

#define all(v) (v).begin(), (v).end()
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
const int MOD = 1e9 + 7; //998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
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
#define dbg(...) 42
#endif

inline namespace RecursiveLambda{
	template <typename Fun>
	struct y_combinator_result{
		Fun fun_;
		template <typename T> 
		explicit y_combinator_result(T &&fun): fun_(forward<T>(fun)){}
		template <typename...Args>
		decltype(auto) operator()(Args &&...args){
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun){
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

void setIO(string s) // USACO
{
	#ifndef LOCAL
	    freopen((s + ".in").c_str(), "r", stdin);
	    freopen((s + ".out").c_str(), "w", stdout);
	#endif
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
	bool operator==(const mint& o) const{
		return v == o.v; }
	friend bool operator!=(const mint& a, const mint& b) { 
		return !(a == b); }
	friend bool operator<(const mint& a, const mint& b) { 
		return a.v < b.v; }
	friend istream& operator>>(istream& is, const mint& o){
		ll v; is >> v; o = mint(v); return is; }
	friend ostream& operator<<(ostream& os, const mint& o){
		os << o.v; return os; }
	
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


vi ind;
int SZ = 1;
int getInd(int x) {return lb(all(ind), x) - ind.begin();}
void insert(int x) {ind.pb(x);}
void initialize() {
	sort(all(ind)), ind.resize(unique(all(ind)) - ind.begin());
	while (SZ < sz(ind)) SZ *= 2;
}


const int N = 5e5;
struct Seg {
	Mint t[N * 4];
	bool lazy[N * 4];
	void init(int n) {
		fill(t, t + 2 * SZ, 0);
		fill(lazy, lazy + 2 * SZ, 0);
	}
	Mint merge(const Mint& a, const Mint& b) {return a + b;}
	void push(int x, int lx, int rx) {
		if (lazy[x] == 0) return;
		t[x] = 0;
		if (rx - lx > 1) {
			lazy[2 * x + 1] = lazy[x];
			lazy[2 * x + 2] = lazy[x];
		}
		lazy[x] = 0;
	}
	void range_set(int l, int r, int x = 0, int lx = 0, int rx = SZ) {
		push(x, lx, rx);
		if (lx >= r || rx <= l) return;
		if (l <= lx && rx <= r) {
			lazy[x] = 1;
			push(x, lx, rx);
			return;
		}
		int m = (lx + rx) >> 1;
		range_set(l, r, 2 * x + 1, lx, m);
		range_set(l, r, 2 * x + 2, m, rx);
		t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void upd(int i, Mint v, int x = 0, int lx = 0, int rx = SZ) {
		push(x, lx, rx);
		if (rx - lx == 1) {
			t[x] = v;
			return;
		}
		int m = (lx + rx) >> 1;
		if (i < m) upd(i, v, 2 * x + 1, lx, m);
		else upd(i, v, 2 * x + 2, m, rx);
		t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	Mint query(int l, int r, int x = 0, int lx = 0, int rx = SZ) {
		push(x, lx, rx);
		if (lx >= r || rx <= l)	return 0;
		if (l <= lx && rx <= r) return t[x];
		int m = (lx + rx) >> 1;
		Mint a = query(l, r, 2 * x + 1, lx, m);
		Mint b = query(l, r, 2 * x + 2, m, rx);
		return merge(a, b);
	}
};
Seg head, tail;

void solve()
{
	int k, n, m;
	cin >> k >> n >> m;
	vpi ark(n), kir(m);
	// insert(0);
	insert(1), insert(k + 1);
	for (auto &e : ark) cin >> e.fi >> e.se, insert(e.fi), insert(e.se + 1);
	for (auto &e : kir) cin >> e.fi >> e.se, insert(e.fi), insert(e.se + 1);
	initialize();
	head.init(sz(ind));
	tail.init(sz(ind));
	vector<vi> h(sz(ind)), t(sz(ind));
	for (auto &[l, r] : ark) {
		l = getInd(l);
		r = getInd(r + 1) - 1;
		h[r].pb(l);
	}
	for (auto &[l, r] : kir) {
		l = getInd(l);
		r = getInd(r + 1) - 1;
		t[r].pb(l);
	}
	dbg(ind);
	// head.upd(0, 1);
	// tail.upd(0, 1);
	vector<Mint> dp(sz(ind));
	dp[0] = 1;
	FOR(i, 0, sz(ind) - 1) {
		sort(all(h[i])), sort(all(t[i]));
		dbg(h[i], t[i]);
		int L = ind[i], R = ind[i + 1] - 1;
		// both
		Mint z = (i ? dp[i - 1] : 1) * (pow(Mint(2), R - L + 1) - 2);
		Mint hOnly = 0;
		Mint tOnly = 0;
		if (sz(t[i])) {
			int j = t[i].back();
			hOnly = tail.query(j, i + 1);
			tail.range_set(0, j);
		}else hOnly = (i ? dp[i - 1] : 1);
		if (sz(h[i])) {
			int j = h[i].back();
			dbg(j);
			tOnly = head.query(j, i + 1);
			head.range_set(0, j);
		}else tOnly = (i ? dp[i - 1] : 1);
		head.upd(i, hOnly + z);
		tail.upd(i, tOnly + z);
		dp[i] = hOnly + tOnly + z;
		dbg(dp[i], L, R, hOnly, tOnly, z);
	}
	cout << dp[sz(ind) - 2] << '\n';
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}