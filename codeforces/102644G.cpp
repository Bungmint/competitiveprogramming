// Problem: G. Recurrence With Square
// Contest: Codeforces - Matrix Exponentiation
// URL: https://codeforces.com/gym/102644/problem/G
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
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

struct Matrix{
	ll m[15][15];
	Matrix(){memset(m,0,sizeof(m));}
	Matrix operator*(const Matrix& other) const{
		Matrix c=Matrix();
		F0R(i,15)F0R(j,15)F0R(k,15){
			c.m[i][j]+=m[i][k]*other.m[k][j];
			c.m[i][j]%=MOD;
		}
		return c;
	}
};

Matrix bin_pow(const Matrix& c, ll n){
	if(n==1) return c;
	Matrix m = bin_pow(c,n>>1);
	return(n&1)?m*m*c:m*m;
}

void solve()
{
	int n;
	cin >>n;
	ll k;
	cin >> k;
	vi a(n), c(n);
	F0R(i,n)cin>>a[i];
	F0R(i,n)cin>>c[i];
	int p,q,r;
	cin >> p >> q>>r;
	if(k<n){
		cout << a[k]<<endl;
		return;
	}
	Matrix x=Matrix();
	x.m[0][0] = 1, x.m[1][0] = x.m[1][1]=x.m[2][0]=x.m[2][2]=1;
	x.m[2][1]=2;
	FOR(i,3,n+2){
		x.m[i][i+1]=1;
	}
	x.m[n+2][0] = p, x.m[n+2][1] = q, x.m[n+2][2] = r;
	FOR(i,3,n+3)x.m[n+2][i] =c[n-1-(i-3)];
	vl v(n+3);
	v[0]=1, v[1] = n, v[2] = n*n;
	FOR(i,3,n+3)v[i]=a[i-3];
	x = bin_pow(x, k-n+1);
	ll ans=0;
	F0R(i,n+3) ans = (ans+v[i]*x.m[n+2][i])%MOD;
	cout <<ans << endl;
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