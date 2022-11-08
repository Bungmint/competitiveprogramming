// Problem: E. Knight Paths
// Contest: Codeforces - Matrix Exponentiation
// URL: https://codeforces.com/gym/102644/problem/E
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
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define REP(a) F0R(_, a)

const int INF = 1e9;
const ll LINF = 1e18;
const ld PI = acos((ld)-1.0);
const int dx[8] ={-1, 1, 2, 2, -1, 1, -2,-2} ,dy[8] = {2,2,-1,1,-2,-2,-1,1};
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
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}
using ull = unsigned long long;
const ull MOD = (1LL<<32);

ull add(ull a, ull b){return (a+b)%MOD;}
ull mul(ull a, ull b){return (a%MOD)*(b%MOD)%MOD;}

struct Matrix{
	ull m[64][64];
	Matrix(){memset(m, 0LL, sizeof(m));}
	Matrix operator*(Matrix& other){
		Matrix c = Matrix();
		F0R(i, 64)F0R(j,64)F0R(k,64)
			c.m[i][j] = add(c.m[i][j], mul(m[i][k], other.m[k][j]));
		return c;
	}
	void operator+=(const Matrix& other){
		F0R(i, 64)F0R(j,64)
			m[i][j] = add(m[i][j], other.m[i][j]);
	}
};
Matrix add(const Matrix& a, const Matrix& other){
	Matrix c = Matrix();
	F0R(i, 64)F0R(j,64)
		c.m[i][j] = add(a.m[i][j], other.m[i][j]);
	return c;
}
using pma = pair<Matrix,Matrix>;
pma bin_pow(Matrix c, int n){
	if (n==1) return {c,c};
	pma p = bin_pow(c,n/2);
	pma res;
	res.se = ((n&1)? p.se*p.se*c:p.se*p.se);
	res.fi = add(p.fi,p.se*p.fi);
	Matrix m = p.se*p.fi;
	if(n&1){
		res.fi += p.se*p.se*c;
	}
	return res;
}
pi c(int x){return {x/8, x%8};}
int c(int x, int y){return x*8+y;}
bool good(int x,int y){return x>=0&&x<8&&y>=0&&y<8;}

void solve()
{
	int n;
	cin >>n;
	Matrix mat = Matrix();
	F0R(i,64){
		auto [x,y] = c(i);
		F0R(j,8){
			int nx = x+dx[j],ny=y+dy[j];
			if(good(nx,ny)) mat.m[i][c(nx,ny)]++;
		}
	}
	ull ans=1;
	if(n==0){cout << ans << endl;return;}
	pma res = bin_pow(mat, n);
	F0R(j, 64) ans+=res.fi.m[0][j], ans%=MOD;
	cout << ans << endl;
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