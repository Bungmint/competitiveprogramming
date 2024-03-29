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

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
#define sz(x) (int)(x).size()

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
const int MOD = 1e9 + 7; //998244353
pi p[2501];
int dp[2501][2501];


bool cmp(pi p1, pi p2){
	return p1.second<p2.second;
}



void solve()
{
	int n;
	cin >> n;
	for (int i=0;i<n;i++) cin >> p[i].first >> p[i].second;
	sort(p, p+n);
	for (int i=0;i<n;i++) p[i].first = i+1;
	sort(p, p+n, cmp);
	for (int i=0;i<n;i++) p[i].second = i+1;
	for (int i=0;i<n;i++) dp[p[i].second][p[i].first]++;
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++){
		dp[i][j] += dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
		dbg(dp[i][j], i, j);
	}
	ll ans = 0LL;
	for (int i=0;i<n;i++) for (int j=i;j<n;j++){
		
		int top = max(p[i].second, p[j].second);
		int bot = min(p[i].second, p[j].second);
		int left = min(p[i].first, p[j].first);
		int right = max(p[i].first, p[j].first);
		
		int lcnt = dp[top][left-1] - dp[bot-1][left-1], rcnt = dp[top][n] - dp[top][right] - (dp[bot-1][n]- dp[bot-1][right]);
		dbg(lcnt, rcnt);
		ans += (lcnt+1)*(rcnt+1); 
	}
	cout << ans+1 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int testcase=1;
    //cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}