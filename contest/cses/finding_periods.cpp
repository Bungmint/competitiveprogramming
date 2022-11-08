// Problem: Finding Borders
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1732
// Memory Limit: 512 MB
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

struct SuffixArray{
	vi p, c, c_new, p_new, cnt, pos, lcp;
	int n;
	vector<pair<char,int>> a;
	
	void count_sort(){
		for (int i=0;i<n;++i) cnt[i] = 0;
		for (int i=0;i<n;++i){
			cnt[c[i]]++;
		}
		pos[0] = 0;
		for (int i=1;i<n;++i) pos[i] = pos[i-1]+cnt[i-1];
		for (int i=0;i<n;++i){
			int x = c[p[i]];
			p_new[pos[x]] = p[i];
			pos[x]++;
		}
		for (int i=0;i<n;++i) p[i] = p_new[i];
	}
	
	SuffixArray(string &s)
	{
		s+='$';
		n = sz(s);
		p.resize(n), c.resize(n), c_new.resize(n);
		p_new.resize(n), cnt.resize(n), pos.resize(n);
		lcp.resize(n), a.resize(n);
		for (int i=0;i<n;++i) a[i] = {s[i], i};
		sort(a.begin(), a.begin()+n);
		for (int i=0;i<n;++i) p[i] = a[i].second;
		c[p[0]] = 0;
		for (int i=1;i<n;++i){
			if (a[i].first==a[i-1].first){
				c[p[i]] = c[p[i-1]];
			}else{
				c[p[i]] = c[p[i-1]] + 1;
			}
		}
		int k=0;
		while((1<<k)<n){
			for (int i=0;i<n;++i) p[i] = (p[i]-(1<<k)+n)%n;
			count_sort();
			c_new[p[0]] = 0;
			for (int i=1;i<n;++i){
				pii prev = {c[p[i-1]], c[(p[i-1]+(1<<k))%n]};
				pii cur = {c[p[i]], c[(p[i]+(1<<k))%n]};
				if (prev==cur){
					c_new[p[i]] = c_new[p[i-1]];
				}else c_new[p[i]] = c_new[p[i-1]]+1;
			}
			
			for (int i=0;i<n;++i) c[i] = c_new[i];
			k++;
		}
		k = 0;
		for (int i=0;i<n-1;++i){
			int posi = c[i];
			int j = p[posi-1];
			while(s[i+k]==s[j+k])k++;
			lcp[posi-1] = k;
			k = max(0, k-1);
		}
	}
};

template<typename T, int lg>
struct SparseTable{
	vector<vector<T>> spar;
	inline T merge(const T& a, const T& b){ // change this
		return min(a,b);
	} 
	SparseTable(const vector<T>& a){
		spar.assign(sz(a), vi(lg,0));
		for (int i=0;i<sz(a);++i) spar[i][0] = a[i];
		for (int j=1;j<lg;++j) for (int i=0;i+(1<<j)<=sz(a);++i)
			spar[i][j] = merge(spar[i][j-1], spar[i+(1<<(j-1))][j-1]);
	}
	T query(int a,int b){
		assert(a<=b);
		int dif = 31- __builtin_clz(b-a+1);
		return merge(spar[a][dif], spar[b-(1<<dif)+1][dif]);
	}
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
Mint power[N],hsh[N], inverse[N],B;

void precalc()
{
    power[0]=inverse[0]=1;
    FOR(i,1,N)power[i]=power[i-1]*B;
    inverse[1] = inv(B);
    FOR(i,2,N)inverse[i]=inverse[i-1]*inverse[1];
}


void solve()
{
	string s;
	cin >> s;
	int n= sz(s);
	FOR(i,1,n+1)hsh[i]=hsh[i-1]+power[i-1]*(s[i-1]-'a'+1);
	FOR(i,1,n+1){
		Mint x = hsh[i];
		int k = n/i * i, len =n-k;
		Mint y=hsh[len];
		bool ok = 1;
		for(int j=2*i;j<=n;j+=i)ok&=(x==(hsh[j]-hsh[j-i])*inverse[j-i]);
		ok&=(y==(hsh[n]-hsh[k])*inverse[k]);
		if(ok)cout << i << " ";
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while((int)B<=100) B = rng()%MOD;
    precalc();
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}