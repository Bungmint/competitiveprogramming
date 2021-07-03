#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;

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
const int MOD = 10007; //998244353

void solve()
{
	int n;
	cin >> n;
	vvi G(n+1), dp(n+1, vi(2)), f(n+1, vi(2));
	for (int i=0;i<n-1;i++){
		int u, v;
		cin >> u >> v;
		G[u].PB(v);
		G[v].PB(u);
	}
	function<void(int,int)> DFS = [&](int V, int pV){
		dp[V][0] = 1;
		f[V][0] = f[V][1] = 1;
		for (int e:G[V]){
			if (e==pV) continue;
			DFS(e,V);
			if (dp[e][0]==dp[e][1]){
				f[V][0] = (f[V][0]*(f[e][0]+f[e][1]))%MOD;
			}else if (dp[e][0]>dp[e][1]){
				f[V][0] = (f[V][0]*f[e][1])%MOD;
			}else{
				f[V][0] = (f[V][0]*f[e][0])%MOD;
			}
			dp[V][0] += min(dp[e][0], dp[e][1]);
			
			dp[V][1] += dp[e][0];
			
			f[V][1] = (f[V][1]*f[e][0])%MOD;
		}
	};
	DFS(1,0);
	int ans = 0;
	if (dp[1][0]==dp[1][1]) ans = (f[1][0]+f[1][1])%MOD;
	else if (dp[1][0]>dp[1][1]) ans = f[1][1];
	else ans = f[1][0];
	cout << min(dp[1][0], dp[1][1])<<" "<< ans<<"\n";
	
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}