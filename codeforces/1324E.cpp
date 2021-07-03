#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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
const int N = 2e5+1;
vector<int> adj[N];
int dp[N], ans[N];
bool c[N];
void dfs(int V,int pV){
	dp[V] = (c[V]? 1: -1);
	for (int &e:adj[V]){
		if (e==pV)continue;
		dfs(e,V);
		dp[V] += (dp[e]>0? dp[e]:0);
	}
	dbg(V, dp[V]);
}
void RR(int V, int pV){
	for (int &e:adj[V]){
		if (e==pV) continue;
		int tmp1 = dp[e], tmp2 = dp[V];
		dp[V] -= max(0, tmp1);
		dp[e] += max(0, dp[V]);
		ans[e] = dp[e];
		RR(e,V);
		dp[e] -= max(0,dp[V]);
		dp[V]+=max(0,tmp1);
	}
}




void solve()
{
	int n;
	cin >> n;
	for (int i=1;i<=n;i++) cin >> c[i];
	for (int i=1;i<=n-1;i++){
		int u,v;
		cin >> u >> v;
		adj[u].PB(v);
		adj[v].PB(u);
	}
	dfs(1,0);
	RR(1,0);
	ans[1] = dp[1];
	for (int i=1;i<=n;i++){
		cout << ans[i]<<" ";
	}
	cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}