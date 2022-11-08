// Problem: Problem 3. Milk Pails
// Contest: USACO - USACO 2016 February Contest, Silver
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=620
// Memory Limit: 256 MB
// Time Limit: 4000 ms
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

void solve()
{
	int m;
	int x,y, k;
	cin >> x >> y >> k>>m;
	vector<vi> dp(x+1, vi(y+1, INF));
	dp[0][0] = 0;
	queue<pi> q;
	q.push({0,0});
	while(sz(q)){
		pi p = q.front();
		q.pop();
		if (dp[p.fi][p.se]==k) continue;
		if (dp[p.fi][y]>dp[p.fi][p.se]+1){
			dp[p.fi][y] = dp[p.fi][p.se]+1;
			q.push({p.fi,y});
		}
		if (dp[x][p.se]>dp[p.fi][p.se]+1){
			dp[x][p.se] = dp[p.fi][p.se]+1;
			q.push({x, p.se});
		}
		if (dp[p.fi][0]>dp[p.fi][p.se]+1){
			dp[p.fi][0] = dp[p.fi][p.se]+1;
			q.push({p.fi,0});
		}
		if (dp[0][p.se]>dp[p.fi][p.se]+1){
			dp[0][p.se] = dp[p.fi][p.se]+1;
			q.push({0, p.se});
		}
		int pourR = min(p.fi, y-p.se);
		int pourL = min(p.se, x-p.fi);
		if (dp[p.fi-pourR][p.se+pourR]>dp[p.fi][p.se]+1){
			dp[p.fi-pourR][p.se+pourR]= dp[p.fi][p.se]+1;
			q.push({p.fi-pourR, p.se+pourR});
		}
		if (dp[p.fi+pourL][p.se-pourL]>dp[p.fi][p.se]+1){
			dp[p.fi+pourL][p.se-pourL]= dp[p.fi][p.se]+1;
			q.push({p.fi+pourL, p.se-pourL});
		}
	}
	int res = INF;
	for (int i=0;i<=x;++i) for (int j=0;j<=y;++j){
		if (dp[i][j]!=INF){
			res = min(res, abs(i+j-m));
		}
	}
	cout << res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef LOCAL
    	setIO("pails");
    #endif
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}