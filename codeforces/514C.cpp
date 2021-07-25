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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
char a[3] = {'a', 'b', 'c'};
int n, m;

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
using Mint9 = mint<998244353, 5>;
ostream &operator<<(ostream &os, Mint x){
	os << x.v;
	return os;
}

const int N = 6e5+10;
const int B = 37;
Mint p[N], inverse[N];
Mint9 p2[N], inverse2[N];
set<pi> st;

void precalc()
{
	p[0] =1;
    for (int i=1;i<N;++i) p[i] = p[i-1]*B;
    inverse[0] = 1;
    inverse[1] = inv((Mint)B);
    for (int i=2;i<N;++i) inverse[i] = inverse[i-1] * inverse[i-1];
    p2[0] =1;
    for (int i=1;i<N;++i) p2[i] = p2[i-1]*B;
    inverse2[0] = 1;
    inverse2[1] = inv((Mint9)B);
    for (int i=2;i<N;++i) inverse2[i] = inverse2[i-1] * inverse2[i-1];
}



void solve()
{
	cin >> n >> m;
	for (int i=0;i<n;++i){
		string s;
		cin >> s;
		Mint hsh1=0;
		Mint9 hsh2 = 0;
		for (int j=0;j<sz(s);++j){
			hsh1 += p[j]*(s[j]-'a'+1);
			hsh2 += p2[j]*(s[j]-'a'+1);
		}
		st.insert({(int)hsh1, (int)hsh2});
	}
	while(m--){
		string s;
		cin >> s;
		Mint hsh1 = 0;
		Mint9 hsh2 = 0;
		for (int j=0;j<sz(s);++j){
			hsh1 += p[j]*(s[j]-'a'+1);
			hsh2 += p2[j]*(s[j]-'a'+1);
		}
		bool ok = 0;
		for (int i=0;i<sz(s);++i){
			for (int j=0;j<3;++j){
				Mint h1 = hsh1;
				Mint9 h2 = hsh2;
				if (a[j]==s[i]) continue;
				h1 -= p[i]*(s[i]-'a'+1);
				h1 += p[i] *(a[j]-'a'+1);
				h2 -= p2[i]*(s[i]-'a'+1);
				h2 += p2[i] *(a[j]-'a'+1);
				if (st.count({(int)h1, (int)h2})) ok = 1;
			}
			if (ok) break;
		}
		cout << (ok? "YES\n":"NO\n");
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    precalc();
    int testcase=1;
    //cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}