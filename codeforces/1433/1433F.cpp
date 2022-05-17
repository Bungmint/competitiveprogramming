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
int mx[71], nxt[71], cur[71];
int dp[71][71], n, m,k, grid[71][71];

void solve()
{
	cin >> n >> m>>k;
	for (int i=1;i<=n;++i)for(int j=1;j<=m;++j) cin >> grid[i][j];
	memset(mx, -1, sizeof(mx));
	mx[0] = 0;
	int lim = m/2;
	for (int i=1;i<=n;++i){
		memset(dp, -1, sizeof(dp));
		memset(cur, -1, sizeof(cur));
		dp[0][0] = 0;
		for (int j=1;j<=m;++j){
			for (int chose = lim-1;chose>=0;--chose){
				for (int rem=0;rem<k;++rem){
					if (dp[chose][rem]==-1) continue;
					dp[chose+1][(rem+grid[i][j])%k] = max(dp[chose+1][(rem+grid[i][j])%k], dp[chose][rem]+grid[i][j]);
					cur[(rem+grid[i][j])%k] = max(cur[(rem+grid[i][j])%k], dp[chose+1][(rem+grid[i][j])%k]);
				}
			}
		}
		memset(nxt, -1, sizeof(nxt));
		nxt[0] = 0;
		for (int j=0;j<k;++j) for(int rem=0;rem<k;++rem){
			if (cur[j]==-1||mx[rem]==-1) continue;
			nxt[(j+rem)%k] = max(nxt[(j+rem)%k], cur[j]+mx[rem]);
		}
		
		for (int i=0;i<k;++i) mx[i] = max(mx[i], nxt[i]);
		
	}
	cout << mx[0]<<endl;
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