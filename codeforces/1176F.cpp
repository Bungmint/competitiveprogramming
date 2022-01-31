// Problem: F. Destroy it!
// Contest: Codeforces - Codeforces Round #565 (Div. 3)
// URL: https://codeforces.com/problemset/problem/1176/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

const int N = 2e5+1;
ll n, dp[N][10];
ar<vl,4> a[N];

void solve()
{
	cin >> n;
	FOR(i, 1, n+1){
		int k;
		cin >> k;
		F0R(j, k){
			int c, d;
			cin >> c >> d;
			a[i][c].pb(d);
		}
		F0R(j, 4) sort(all(a[i][j]), greater<int>());
	}
	memset(dp, -1, sizeof(dp));
	dp[0][0] = 0;
	FOR(i, 1, n+1){
		F0R(j, 10) dp[i][j] = dp[i-1][j];
		// 1+1+1
		if (sz(a[i][1])>=3){
			ll sum = a[i][1][0]+a[i][1][1]+a[i][1][2], mx = a[i][1][0];
			F0R(j, 10){
				if (dp[i-1][j]!=-1) ckmax(dp[i][(j+3)%10],dp[i-1][j]+(j>=7? sum+mx:sum));
			}
		}
		//1+1, 1+2, 2+1 Two Cards
		if (sz(a[i][1])>=2){
			ll mx = a[i][1][0], mx2 = a[i][1][1];
			F0R(j, 10)if (dp[i-1][j]!=-1)ckmax(dp[i][(j+2)%10], dp[i-1][j]+(j>=8? mx*2+mx2:mx+mx2));
		}
		if (sz(a[i][1])&&sz(a[i][2])){
			ll mx = max(a[i][1][0], a[i][2][0]), mx2 = min(a[i][1][0], a[i][2][0]);
			F0R(j, 10)if (dp[i-1][j]!=-1)ckmax(dp[i][(j+2)%10], dp[i-1][j]+(j>=8? mx*2+mx2:mx+mx2));
		}
		// 1, 2, 3 Single Card
		ll single = 0;
		if(sz(a[i][1])) ckmax(single, a[i][1].front());
		if(sz(a[i][2])) ckmax(single, a[i][2].front());
		if(sz(a[i][3])) ckmax(single, a[i][3].front());
		if (single){
			F0R(j, 10){
				if (dp[i-1][j]!=-1)ckmax(dp[i][(j+1)%10],dp[i-1][j] +(j==9? 2*single:single));
			}
		}
	}
	ll ans = 0;
	F0R(j, 10) ckmax(ans, dp[n][j]);
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