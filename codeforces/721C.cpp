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
const int N = 5001;
pi dp[N][N];
vpi G[N];
bool vis[N];
vi order;

void dfs(int V){
	vis[V] = 1;
	for (auto &[u, w]:G[V]){
		if (!vis[u]) dfs(u);
	}
	order.pb(V);
}


void solve()
{
	int n, m, t;
	cin >> n >> m >> t;
	for (int i=0;i<m;++i){
		int u, v, w;
		cin >> u >> v>>w; 
		G[u].pb({v,w});
	}
	dfs(1);
	reverse(all(order));
	for (int i=0;i<=n;++i){
		for (int j=0;j<=n;++j){
			dp[i][j] = {2*INF, -1};
		}
	}
	dp[1][1] = {0,0};
	dbg(order);
	for (int x:order){
		for (auto &[y, w]:G[x]){
			for (int k=1;k<=n;++k){
				if (dp[x][k].fi<INF+1){
					if (dp[x][k].fi+w<dp[y][k+1].fi){
						dp[y][k+1] = {dp[x][k].fi + w,x};
					}
				}
			}
		}
	}
	for (int i=n;i>=0;--i){
		if (dp[n][i].fi<=t){
			cout << i << "\n";
			vi ans;
			int cur = n;
			int cnt = i;
			while(cur!=0){
				ans.pb(cur);
				cur=dp[cur][cnt].se;
				cnt--;
			}
			reverse(all(ans));
			for (int x:ans) cout << x << " ";
			cout << "\n";
			return;
		}
	}
	
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}