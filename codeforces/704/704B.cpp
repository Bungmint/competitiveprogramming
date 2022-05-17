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
const int N = 5011;

ll dp[N][N];
ll a[N], b[N], c[N],d[N], x[N];


void solve()
{
	int n, s,e;
	cin >> n >> s >> e;
	for (int i=1;i<=n;++i) cin >> x[i];
	for (int i=1;i<=n;++i) cin >> a[i];
	for (int i=1;i<=n;++i) cin >> b[i];
	for (int i=1;i<=n;++i) cin >> c[i];
	for (int i=1;i<=n;++i) cin >> d[i];
	
	for (int i=0;i<=n+10;++i) for (int j=0;j<=n+10;++j) dp[i][j] = LINF;
	
	dp[0][0] = 0;
	for (ll i=1;i<=n;++i){
		for (ll j=1;j<=n;++j){
			ll here = LINF;
			if (i==s){
				if (dp[i-1][j]!=LINF)here = min(here, dp[i-1][j]+x[i]+c[i]);
				if (dp[i-1][j-1]!=LINF)here = min(here, dp[i-1][j-1]-x[i]+d[i]);
			}else if (i==e){
				if (dp[i-1][j]!=LINF)here = min(here, dp[i-1][j]+x[i]+a[i]);
				if (dp[i-1][j-1]!=LINF)here = min(here, dp[i-1][j-1]-x[i]+b[i]);
			}else{
				if (j+1<=n&&dp[i-1][j+1]!=LINF)here = min(here, dp[i-1][j+1]+2*x[i]+c[i]+a[i]);
				int s_great=!!(i>s);
				int e_great=!!(i>e);
				if (dp[i-1][j-1]!=LINF&&j-s_great-e_great>=1)here = min(here, dp[i-1][j-1] + d[i]+b[i]-2*x[i]);
				
				if (j-s_great>=1&&dp[i-1][j]!=LINF)here = min(here, dp[i-1][j]+c[i]+b[i]);
				if (j-e_great>=1&&dp[i-1][j]!=LINF)here = min(here, dp[i-1][j]+a[i]+d[i]);
			
			}
			dp[i][j] = here;
		}
	}
	
	
	cout << dp[n][1]<<"\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}