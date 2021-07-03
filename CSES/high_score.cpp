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
const int MOD = 1e9 + 7; //998244353
vi G[3000];
bool vis[3000];

bool dfs(int v, int targ){
	if (v==targ) return 1;
	if (vis[v]) return 0;
	vis[v] = 1;
	bool res = 0;
	for (int e:G[v]){
		res |= dfs(e,targ);
	}
	return res;
}
 
void solve()
{
	int n, m;
	cin >> n >> m;
	vector<ar<int,3>> Edge;
	vector<ll> dist(n+1);
	fill(all(dist), LINF);
	dist[1] = 0;
	for (int i=0;i<m;i++){
		int u, v, w;
		cin >> u >> v >> w;
		w = -w;
		Edge.PB({u,v,w});
		G[u].PB(v);
	}
	for (int i=0;i<n;i++){
		for (ar<int,3> a:Edge){
			int u = a[0], v = a[1], w= a[2];
			if (dist[v]>dist[u] + w){
				if (i==n-1){
					dbg(u,v);
					memset(vis, 0, sizeof(vis));
					if (dfs(v, n))
					{
						memset(vis, 0, sizeof(vis));
						if (dfs(1,v)||vis[u]){
						cout <<-1 << "\n";
						return;
						}
					}
				}
				dist[v] = dist[u] + w;
			}
		}
	}
	cout << -dist[n]<<"\n";
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