// Problem: D. Potion Brewing Class
// Contest: Codeforces - Codeforces Round #778 (Div. 1 + Div. 2, based on Technocup 2022 Final Round)
// URL: https://codeforces.com/contest/1654/problem/D
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2022 Youngmin Park. All rights reserved.
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
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


const int N = 2e5; // Only advised to use it under 1e7 (More Memory)
int lp[N + 1];
vector<int> pr;
vpi factor[N + 1];
int prID[N + 1];
int cur;
void linsieve()
{
    for (int i = 2; i <= N; i++)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            prID[i] = cur++;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
        {
            lp[i * pr[j]] = pr[j];
        }
    }
    FOR(i, 2, N + 1) {
    	factor[i] = factor[i / lp[i]];
    	if (lp[i] != lp[i / lp[i]]) {
    		factor[i].pb({lp[i], 1});
    	}else{
    		factor[i].back().se++;
    	}
    }
}

template<typename T, typename S>
struct LazySegTree{
	const T seg_initial = 0;
	const S seg_lazy_sentinel = 0;
	const T NEUTRAL = 0;
	int sz;
	vector<T> t;
	vector<S> lazy;
	
	
	// Change the inline function accordingly to the q
	inline T merge(T a, T b){
		return max(a, b);
	}
	inline S lazy_apply(S lazy_val, S new_val){
		return lazy_val + new_val;
	}
	inline T lazy_func(T cur_val, S lazy_val, ll l, ll r){
		return max(cur_val + lazy_val, 0LL);
	}
	
	
	void init(int n){
		sz = 1;
		while(sz<n) sz*=2;
		t.assign(2*sz, seg_initial);
		lazy.assign(2*sz, seg_lazy_sentinel);
	}
	void seg_eval_lazy(int i, ll l, ll r)
	{
	    if (lazy[i] == seg_lazy_sentinel)
	        return;
	
	    t[i] = lazy_func(t[i], lazy[i], l, r);
	
	    if (r-l>1)
	    {
	        lazy[i * 2 + 1] = lazy_apply(lazy[i * 2 + 1], lazy[i]);
	       	lazy[i * 2 + 2] = lazy_apply(lazy[i * 2 + 2], lazy[i]);
	    }
	
	    lazy[i] = seg_lazy_sentinel;
	}
	void build(vector<int> &vec, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        if (l < (int)vec.size())
	            t[x] = vec[l];
	        return;
	    }
	    int mid = (l + r) / 2;
	    build(vec, 2 * x + 1, l, mid);
	    build(vec, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void build(vector<int> &vec)
	{
	    build(vec, 0, 0, sz);
	}
	T upd(int x, int l, int r, int lx, int rx, S v)
	{
		seg_eval_lazy(x, lx, rx);
		if (lx>=r||rx<=l) return t[x];
		if (lx>=l&&rx<=r){
			lazy[x] = lazy_apply(lazy[x],v);
			seg_eval_lazy(x, lx ,rx);
			return t[x];
		}
		if (rx-lx==1) return t[x];
	    
	    int mid = (lx + rx) / 2;
	    T a = upd(2*x+1, l, r, lx, mid, v);
	    T b = upd(2*x+2, l, r, mid, rx, v);
	   	return t[x] = merge(a, b);
	}
	void upd(int l, int r, S v)
	{
	    upd(0, l, r, 0, sz, v);
	}
	T query(int l, int r, int x, int lx, int rx)
	{
		seg_eval_lazy(x, lx, rx);
	    if (lx >= r || rx <= l)
	        return NEUTRAL;
	    if (lx >= l && rx <= r)
	        return t[x];
	    int mid = (lx + rx) / 2;
	    T a = query(l, r, 2 * x + 1, lx, mid);
	    T b = query(l, r, 2 * x + 2, mid, rx);
	    return merge(a, b);
	}
	T query(int l, int r)
	{
	    return query(l, r, 0, 0, sz);
	}
};



void solve()
{
	int n;
	cin >> n;
	LazySegTree<ll, ll> st;
	st.init(2 * n);
	vi tin(n), tout(n);
	vector<vector<pair<int, pii>>> prime(sz(pr)), g(n);
	int timer{};
	REP(n - 1) {
		int u, v, x, y;
		cin >> u >> v >> x >> y;
		u--, v--;
		int gg = gcd(x, y);
		x /= gg, y /= gg;
		map<int, int> freq;
		for (auto &[pp, cnt] : factor[x]) {
			freq[pp] += cnt;
		}
		for (auto &[pp, cnt] : factor[y]) {
			freq[pp] -= cnt;
		}
		for (auto &[pp, cnt] : freq) {
			if (cnt) {
				prime[prID[pp]].pb({cnt, {u, v}});
			}
		}
		g[u].pb({v, {x, y}});
		g[v].pb({u, {y, x}});
	}
	Mint ans{};
	vi depth(n);
	auto dfs = y_combinator([&](auto dfs, int u, int pu) -> void {
		tin[u] = timer++;
		for (auto &[e, p]: g[u]) {
			if (e != pu) {
				depth[e] = depth[u] + 1;
				dfs(e, u);
			}
		}
		tout[u] = timer - 1;
	});
	auto calc = y_combinator([&](auto calc, int u, int pu, Mint val) -> void {
		ans += val;
		for (auto &[e, p] : g[u]) {
			if (e != pu) {
				calc(e, u, val * (Mint) p.se / (Mint) p.fi);
			}
		}
	});
	dfs(0, -1);
	Mint L = 1;
	F0R(i, sz(prime)) {
		auto &v = prime[i];
		if (!sz(v)) continue;
		for (auto &[cnt, p] : v) {
			if (depth[p.fi] < depth[p.se]) swap(p.fi, p.se);
			else cnt = -cnt;
		}
		sort(all(v), [&](auto p, auto q) {
			return depth[p.se.fi] > depth[q.se.fi];
		});

		dbg(v);
		for (auto &[cnt, p] : v) {
			auto [u, pu] = p;
			st.upd(tin[u], tout[u] + 1, cnt);
		}
		dbg(st.query(tin[0], tout[0] + 1));
		L *= pow((Mint) pr[i], st.query(tin[0], tout[0] + 1));
		st.upd(tin[0], tout[0] + 1, -INF);
	}
	dbg(L);
	calc(0, -1, L);
	cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    cin >> testcase;
    linsieve();
    while (testcase--)
    {
        solve();
    }
}