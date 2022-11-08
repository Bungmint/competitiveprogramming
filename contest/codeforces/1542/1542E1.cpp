// Problem: E1. Abnormal Permutation Pairs (easy version)
// Contest: Codeforces - Codeforces Round #729 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1542/E1
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("Ofast")
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
#define left asdf
int n, mod;
int add(int a, int b){
	int v = a+b;
	if (v>=mod) v-=mod;
	return v;
}
int mul(int a, int b){return (1LL*a*b)%mod;}
int dp[51][1234], prefS[51][1234];
int choose[51][51];

int nCk(int n, int k){
	if (n<k||k<0) return 0;
	int&res= choose[n][k];
	dbg(n, k, res);
	if (res!=-1) return res;
	res = add(nCk(n-1, k-1),nCk(n-1, k));
	return res;
}

void solve()
{
	cin>> n >>mod;
	vi fact(n+1,1);	
	memset(choose, -1, sizeof(choose));
	F0R(i, n+1) choose[i][i] = choose[i][0] = 1;
	FOR(i, 1, n+1) fact[i] = mul(fact[i-1], i);
	dp[1][0] = 1;
	FOR(i, 2, n+1){
		F0R(j, (i-2)*(i-1)/2LL + 1){
			F0R(k, i){
				dp[i][j+k] = add(dp[i][j+k], dp[i-1][j]);
			}
		}
	}
	FOR(i,1, n+1){
		prefS[i][0] = dp[i][0];
		FOR(j,1, 1234) prefS[i][j] = add(prefS[i][j-1], dp[i][j]);
	}
	int ans = 0;
	F0R(i, n-1){
		int pref = mul(fact[i], nCk(n, i));
		int left = n-i;
		F0R(j, left){
			FOR(k, j+1, left){
				int v = 0;
				int diff = k-j;
				F0R(x, 1234-diff) v = add(v, mul(dp[left-1][x], prefS[left-1][1233]-prefS[left-1][x+diff]+mod));
				v = mul(v, pref);
				ans = add(ans, v);
			}
		}
	}
	cout << ans <<"\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}