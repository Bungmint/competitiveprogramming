// Problem: E. Stringforces
// Contest: Codeforces - Educational Codeforces Round 111 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1550/problem/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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
const int MN = 2e5+10;
int cnt[MN][17], nxt[MN][17];
int dp[1<<17], n, k;
string s;

bool good(int V){
	for (int i=0;i<k;++i) nxt[n][i] = n+1;
	for (int i=n-1;i>=0;i--){
		for (int j=0;j<k;++j){
			nxt[i][j] = nxt[i+1][j];
			if (i+V<=n&&cnt[i][j]+V==cnt[i+V][j]) nxt[i][j] = i;
		}
	}
	for (int mask=1;mask<(1<<k);++mask){
		dp[mask] = n+1;
		for (int last = 0;last<k;++last){
			if ((mask&(1<<last))==0) continue;
			int from = mask-(1<<last);
			int fromEnd = dp[from];
			if (fromEnd>=n) continue;
			int start = nxt[fromEnd][last];
			dp[mask] = min(dp[mask], start+V);
		}
	}
	return dp[(1<<k)-1]<=n;
}

void solve()
{
	cin >> n>>k;
	cin >> s;
	for (int i=1;i<=n;++i){
		for (int j=0;j<k;++j){
			cnt[i][j]= cnt[i-1][j];
			if (s[i-1]=='a'+j||s[i-1]=='?') cnt[i][j]++;
		}
	}
	int l = 0, r = n, ans = 0;
	while(l<=r){
		int m = l+(r-l)/2;
		if (good(m)){
			ans =m;
			l = m+1;
		}else r = m-1;
	}
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