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

using Mint1 = mint<MOD,5>; // 5 is primitive root for both common mods
using Mint2 = mint<998244353, 5>;
using pmm = pair<Mint1, Mint2>;

const int N = 500;
const int B = 9973;
const pii d[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
bool vis[N][N][8];
Mint1 pow1[N + 1];
Mint2 pow2[N + 1];

void precalc() {
	pow1[0] = 1;
	pow2[0] = 1;
	FOR(i, 1, N + 1) {
		pow1[i] = pow1[i - 1] * B;
		pow2[i] = pow2[i - 1] * B;
	}
}

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<string> grid(n);
	for (auto &e : grid) cin >> e;
	ll denom = (1LL * 8 * n * m) * (1LL * 8 * n * m);
	ll num {};
	vpi res;
	F0R(i, 8) {
		F0R(r, n) {
			F0R(c, m) {
				if (vis[r][c][i]) continue;
				int rr = r, cc = c;
				vpi a;
				vector<pmm> hsh;
				do{
					a.pb({rr, cc});
					vis[rr][cc][i] = 1;
					rr += d[i].fi;
					cc += d[i].se;
					if (rr >= n) rr -= n;
					if (cc >= m) cc -= m;
					if (rr < 0) rr += n;
					if (cc < 0) cc += m;
				}while (rr != r || cc != c);
				hsh.resize(sz(a) * 2 + 1);
				F0R(ii, sz(a) * 2) {
					auto [x, y] = a[ii % sz(a)];
					hsh[ii + 1].fi = hsh[ii].fi * B + grid[x][y];
					hsh[ii + 1].se = hsh[ii].se * B + grid[x][y];
				}
				int nn = sz(a);
				int q = k / nn;
				int r = k % nn;
				pmm Base;
				Base.fi = (pow((Mint1)B, nn * (q)) - 1) / (pow((Mint1)B, nn) - 1) * pow((Mint1)B, r);
				Base.se = (pow((Mint2)B, nn * (q)) - 1) / (pow((Mint2)B, nn) - 1) * pow((Mint2)B, r);
				dbg(nn, q, r, Base);
				F0R(ii, sz(a)) {
					pmm power{};
					power.fi = hsh[ii + sz(a)].fi - hsh[ii].fi * pow1[sz(a)];
					power.se = hsh[ii + sz(a)].se - hsh[ii].se * pow2[sz(a)];
					power.fi *= Base.fi;
					power.se *= Base.se;
					power.fi += hsh[ii + r].fi - hsh[ii].fi * pow1[r];
					power.se += hsh[ii + r].se - hsh[ii].se * pow2[r];
					res.pb({(int)power.fi, (int)power.se});
				}
				dbg(res.back());
				dbg(hsh);
			}
		}
	}
	sort(all(res));
	F0R(i, sz(res)) {
		int cnt = 1;
		while (i + 1 < sz(res) && res[i] == res[i + 1]) {
			cnt++, i++;
		}
		num += 1LL * cnt * cnt;
	}
	ll g = gcd(denom, num);
	denom /= g, num /= g;
	cout << num << '/' << denom << '\n';
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    precalc();
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}