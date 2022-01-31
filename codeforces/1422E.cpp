// Problem: E. Minlexes
// Contest: Codeforces - Codeforces Round #675 (Div. 2)
// URL: https://codeforces.com/contest/1422/problem/E
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

const int N = 1e5+10, LOG = 20;
Mint power[N], inverse[N], dp[N], B;
string ans[N];
int up[N][LOG], len[N];
void precalc()
{
    power[0] = inverse[0] = 1;
    FOR(i, 1, N)power[i] = power[i-1]*B;
    inverse[1] = inv(B);
    FOR(i, 1, N) inverse[i] = inverse[i-1]*inverse[1];
}

string comb(char c, string& s){
	if (sz(s)==10){
		string res = "";
		res += c;
		F0R(i, 4)res += s[i];
		FOR(i, 5, sz(s)) res += s[i];
		return res;
	}else return c + s;
}

int binlift(int x, int d){
	R0F(j, LOG)if (d&(1<<j)) x = up[x][j];
	return x;
}

void solve()
{
	string s;
	cin >> s;
	int n = sz(s);
	F0R(i, LOG) up[n-1][i] = up[n][i] = n;
	R0F(i, n){
		if (i==n-1){
			dp[i] = s[i]-'a'+1;
			len[i] = 1;
			ans[i] = s[i];
		}else{
			if (s[i]==s[i+1]){
				//Compare 
				if (ans[i+2].empty()||s[i]>ans[i+2][0]){
					dp[i] = dp[i+2];
					len[i] = len[i+2];
					ans[i] = ans[i+2];
					up[i][0] = up[i+2][0];
					FOR(j, 1, LOG) up[i][j] = up[up[i][j-1]][j-1];
				}else if (s[i]<ans[i+2][0]){
					dp[i] = dp[i+1]*power[1] + s[i]-'a'+1;
					len[i] = len[i+1] +1;
					ans[i] = comb(s[i], ans[i+1]);
					up[i][0] = i+1;
					FOR(j,1, LOG) up[i][j] =up[up[i][j-1]][j-1];
				}else{
					int l = 1, r = min(len[i+1]+1, len[i+2]), res = 1;
					Mint val = dp[i+1]*power[1] + s[i]-'a'+1;
					while(l<=r){
						int mid = l + (r-l)/2LL;
						int p = binlift(i+1, mid-1), q = binlift(i+2, mid);
						dbg(p, q, mid, l, r);
						if (val-dp[p]*power[mid]==dp[i+2]-dp[q]*power[mid]){
							res = mid;
							l = mid+1;
						}else r = mid-1;
						dbg(l, r);
					}
					dbg(i, res);
					if (res==min(len[i+1]+1, len[i+2])){
						if (len[i+1]+1<len[i+2]){
							dp[i] = dp[i+1]*power[1] + s[i]-'a'+1;
							len[i] = len[i+1] +1;
							ans[i] = comb(s[i], ans[i+1]);
							up[i][0] = i+1;
							FOR(j,1, LOG) up[i][j] =up[up[i][j-1]][j-1];
						}else{
							dp[i] = dp[i+2];
							len[i] = len[i+2];
							ans[i] = ans[i+2];
							up[i][0] = up[i+2][0];
							FOR(j, 1, LOG) up[i][j] = up[up[i][j-1]][j-1];
						}
					}else{
						int x = binlift(i+1, res-1), y = binlift(i+2, res);
						dbg(x, y);
						if(ans[y].empty()||(!ans[x].empty()&&ans[y][0]<ans[x][0])) {
							dp[i] = dp[i+2];
							len[i] = len[i+2];
							ans[i] = ans[i+2];
							up[i][0] = up[i+2][0];
							FOR(j, 1, LOG) up[i][j] = up[up[i][j-1]][j-1];
						}else{
							dp[i] = dp[i+1]*power[1] + s[i]-'a'+1;
							len[i] = len[i+1] +1;
							ans[i] = comb(s[i], ans[i+1]);
							up[i][0] = i+1;
							FOR(j,1, LOG) up[i][j] =up[up[i][j-1]][j-1];
						}
					}
				}
			}else{
				dp[i] = dp[i+1]*power[1] + s[i]-'a'+1;
				len[i] = len[i+1] +1;
				ans[i] = comb(s[i], ans[i+1]);
				up[i][0] = i+1;
				FOR(j,1, LOG) up[i][j] =up[up[i][j-1]][j-1];
			}
		}
	}
	F0R(i, n){
		cout << len[i]<<" ";
		if (len[i]>10){
			F0R(j, 5) cout << ans[i][j];
			F0R(j,3) cout << '.';
			F0R(j, 2) cout << ans[i][sz(ans[i])-2+j];
			cout << "\n";
		}
		else cout << ans[i]<<"\n";
	}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    while((int)B<=100) B = rng()%MOD;
    precalc();
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}