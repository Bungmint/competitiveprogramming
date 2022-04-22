// Problem: Problem 3. Lights Out
// Contest: USACO - USACO 2016 January Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=599
// Memory Limit: 256 MB
// Time Limit: 4000 ms
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

inline namespace Hash {
	const int N = 801;
	const Mint B = 9973;
	Mint pow[N + 1];
	vector<Mint> hsh;
	void precalc() {
		pow[0] = 1;
		FOR(i, 1, 1 + N) pow[i] = pow[i - 1] * B;
	}
	void hashVector(vpi& a) {
		precalc();
		int n = sz(a);
		hsh.pb(0);
		vi order;
		F0R(i, n) {
			pii cur = a[i];
			pii nxt = a[(i + 1) % n];
			order.pb(abs(cur.fi - nxt.fi) + abs(cur.se - nxt.se));
		}
		sort(all(order)), order.resize(unique(all(order)) - order.begin());
		F0R(i, n) {
			pii prev = (i ? a[i - 1] : a[n - 1]);
			pii cur = a[i];
			pii nxt = (i == n - 1 ? a[0] : a[i + 1]);
			int ang{};
			if (prev.fi > cur.fi) {
				if (cur.se > nxt.se) {
					ang = 2;
				}else{
					ang = 1;
				}
			}else if (prev.fi < cur.fi) {
				if (cur.se > nxt.se) {
					ang = 1;
				}else{
					ang = 2;
				}
			}else if (prev.se > cur.se) {
				if (cur.fi > nxt.fi) {
					ang = 1;
				}else{
					ang = 2;
				}
			}else{
				if (cur.fi > nxt.fi) {
					ang = 2;
				}else{
					ang = 1;
				}
			}
			hsh.pb(hsh.back() * B + ang);
			int x = lb(all(order), abs(cur.fi - nxt.fi) + abs(cur.se - nxt.se)) - order.begin();
			hsh.pb(hsh.back() * B + x);
		}
	}
	Mint hashRange(int i, int j) {
		return hsh[2 * j + 1] - hsh[2 * i] * pow[2 * j - 2 * i + 1];
	}
};

void solve()
{
	int n;
	cin >> n;
	vpi a(n);
	vi dist(n), b(n, 2 * INF);
	for (auto &[x, y] : a) cin >> x >> y;
	F0R(i, n) {
		if (i) dist[i] = dist[i - 1] + abs(a[i].fi - a[i - 1].fi) + abs(a[i].se - a[i - 1].se);
	}
	int d = abs(a[0].fi - a[n - 1].fi) + abs(a[0].se - a[n - 1].se);
	hashVector(a);
	int ans = 0;
	FOR(len, 1, n) {
		map<int, int> cnt;
		FOR(l, 1, n - len) {
			int r = l + len - 1;
			cnt[(int)hashRange(l, r)]++;
		}
		FOR(l, 1, n - len) {
			int r = l + len - 1;
			if (cnt[(int)hashRange(l, r)] == 1) {
				int pref = dist[r] - dist[l];
				int mi = min(dist[r], dist[n - 1] - dist[r] + d);
				ckmin(b[l], pref + mi);
			}
		}
	}
	FOR(i, 1, n) {
		int val = min(dist[i], dist[n - 1] - dist[i] + d);
		ckmin(b[i], dist[n - 1] - dist[i] + d);
		dbg(b[i]);
		ckmax(ans, b[i] - val);
	}
	cout << ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    setIO("lightsout");
    while (testcase--)
    {
        solve();
    }
}