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



Mint dp[1001][1001][5]; 
/*
	Connected Component DP
	dp_i,j,k - i: 1 to i
			   j: j components
			   k: 0: Merged
			 	  1: New inside (Has two neighboring components)
			 	  2: New outside (Only one neighbor)
			 	  3: Front/back inside 
			 	  4: Front/back outside (The very outskirt)
			
*/

void solve()
{
	int n;
	cin >> n;
	dp[0][0][0] = 1;
	for (int i=1;i<=n;++i){ 
		for (int j=1;j<=n;++j){
			//Merged
			if (j+1<=n){
				dp[i][j][0] += dp[i-1][j+1][0]*(j);
				dp[i][j][0] += dp[i-1][j+1][1]*(j-2);
				dp[i][j][0] += dp[i-1][j+1][2]*(j-1);
				dp[i][j][0] += dp[i-1][j+1][3]*(j-1);
				dp[i][j][0] += dp[i-1][j+1][4]*(j);
			}
			//New
			//Inside
			if (j-1>=2) dp[i][j][1] += (dp[i-1][j-1][0] + dp[-1+i][j-1][1]+dp[-1+i][j-1][2] + dp[i-1][j-1][3] + dp[i-1][j-1][4])*(j-2);
			
			//Outside
			
			dp[i][j][2] += (dp[i-1][j-1][0] + dp[i-1][j-1][1]+dp[i-1][j-1][2] + dp[i-1][j-1][3] + dp[i-1][j-1][4]);
			if (j-1) dp[i][j][2] += (dp[i-1][j-1][0] + dp[i-1][j-1][1]+dp[i-1][j-1][2] + dp[i-1][j-1][3] + dp[i-1][j-1][4]);
			
			//Front/back
			//Inside
			if (j>=2){
				dp[i][j][3] += dp[i-1][j][0]*(2*j-2);
				dp[i][j][3] += dp[i-1][j][1]*(2*j-4);
				dp[i][j][3] += dp[i-1][j][2]*(2*j-3);
				dp[i][j][3] += dp[i-1][j][3]*(2*j-3);
				dp[i][j][3] += dp[i-1][j][4]*(2*j-2);
			}
			
			//Outside
			if (j>=1){
				dp[i][j][4] += dp[i-1][j][0]*(2);
				dp[i][j][4] += dp[i-1][j][1]*(2);
				if (j>=2)dp[i][j][4] += dp[i-1][j][2]*(1);
				dp[i][j][4] += dp[i-1][j][3]*(2);
				dp[i][j][4] += dp[i-1][j][4]*(1);
			}
			dbg(i, j,dp[i][j][0], dp[i][j][1], dp[i][j][2],dp[i][j][3], dp[i][j][4]);
		}
	}
	dbg(dp[n][1][0], dp[n][1][1], dp[n][1][2],dp[n][1][3], dp[n][1][4]);
	cout << dp[n][1][0]+dp[n][1][1]+dp[n][1][2]+dp[n][1][3]+dp[n][1][4]<<"\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}