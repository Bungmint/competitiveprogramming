// Problem: Coding Company
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1665
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
 
int dp[11000][52];
int nxt[11000][52];
 
void add(int &x, int y){x = (x+y)%MOD;}
int mul(int x, int y){return ((ll)x*(ll)y)%MOD;}
 
int c(int x){return x+5000;}
 
void solve()
{
	int n, x;
	cin >> n>>x;
	vi a(n+1);
	for (int i=1;i<=n;++i) cin >> a[i];
	sort(all(a));
	dp[c(0)][0] = 1;
	for (int i=1;i<=n;++i){
		memset(nxt, 0, sizeof(nxt));
		for (int j=-5000;j<=5000;++j){
			for (int k=0;k<=50;++k){
				// Creating a new group
				if (k<50&&j-a[i]>=-5000)add(nxt[c(j-a[i])][k+1], dp[c(j)][k]);
				// Finishing an existing group
				if (k)add(nxt[c(j+a[i])][k-1], mul(dp[c(j)][k], k));
				// Vlone
				add(nxt[c(j)][k], dp[c(j)][k]);
				// Adding it to an existing group
				add(nxt[c(j)][k], mul(dp[c(j)][k],k));
			}
		}
		for (int j=-5000;j<=5000;++j) for (int k=0;k<=50;++k) dp[c(j)][k] = nxt[c(j)][k];
	}
	int ans = 0;
	for (int i=0;i<=x;++i) add(ans, dp[c(i)][0]);
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