// Problem: A. Fancy Fence
// Contest: Codeforces - Central-European Olympiad in Informatics, CEOI 2020, Day 1 (IOI, Unofficial Mirror Contest, Unrated)
// URL: https://codeforces.com/contest/1402/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;
using pl = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pl>;
using ld = long double;

#define all(v) (v).begin(), (v).end()
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound

template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
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

struct custom_hash
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
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;

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

Mint nC2(ll n){
	return (Mint)n*(Mint)(n-1)/(Mint)2;
}


void solve()
{
	int n;
	cin >> n;
	vector<ll> h(n+1), w(n+1), pref(n+1);
	vi l(n+1), r(n+1), leftmost(n+1);
	for (int i=1;i<=n;++i){
		cin >> h[i];
	}
	// sort(all(order));
	// order.resize(unique(all(order))-order.begin());
	// for (int i=1;i<=n;++i) h[i] = lb(all(order), h[i])-order.begin();
	for (int j=1;j<=n;++j) cin >> w[j], pref[j] = pref[j-1] + w[j];
	stack<int>st;
	for (int i=1;i<=n;++i){
		while(!st.empty()&&h[st.top()]>=h[i]){
			if (h[st.top()]==h[i]){
				leftmost[i] =st.top();
			}
			st.pop();
		}
		l[i] = (st.empty()? 0:st.top());
		st.push(i);
		if (!leftmost[i]) leftmost[i] = i;
	}
	while(sz(st))st.pop();
	for (int i=n;i>=1;i--){
		while(!st.empty()&&h[st.top()]>=h[i])st.pop();
		r[i] = (st.empty()? n+1:st.top());
		st.push(i);
	}
	Mint ans = 0;
	for (int i=1;i<=n;++i){
		int L = l[i], R = r[i]; //L+1~R-1
		if (leftmost[i]!=i) L = max(L, leftmost[i]);
		dbg(L,R);
		Mint wL = pref[i-1] - pref[L];
		Mint wR = pref[R-1] - pref[i];
		dbg(wL,wR);
		Mint x = nC2(h[i]+1);
		dbg(x);
		Mint y = wL*w[i] + (Mint)w[i]*(Mint)(w[i]+1)/(Mint)2 + (wL+(Mint)w[i])*(Mint)wR;
		ans += x*y;
		dbg(y);
	}
	cout << ans;
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