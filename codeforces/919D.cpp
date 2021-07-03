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
const int N = 3e5+1;
vi G[N];
int c[N], dp[N][26], n, m;
string s;
bool cycle = 0, vis[N];
vi top;

void cyc_check(int V){
	c[V] = 1;
	for (int u:G[V]){
		if (c[u]==0){
			cyc_check(u);
		}else if (c[u]==1){
			cycle = 1;
		}
	}
	c[V] = 2;
}

void dfs(int V){
	vis[V] = 1;
	for (int u:G[V]){
		if (vis[u]) continue;
		dfs(u);
	}
	top.PB(V);
}


void solve()
{
	cin >> n >> m>>s;
	for (int i=0;i<m;i++){
		int u, v;
		cin >> u >> v;
		G[u].PB(v);
	}
	for (int i=1;i<=n;i++){
		if (c[i]==0) cyc_check(i);
	}
	if (cycle){
		cout << -1 << "\n";
		return;
	}
	for (int i=1;i<=n;i++){
		if (!vis[i]) dfs(i);
	}
	reverse(all(top));
	for (int i=0;i<n;i++){
		dp[top[i]][s[top[i]-1]-'a']++;
		for (int u:G[top[i]]){
			for (int j=0;j<26;++j){
				dp[u][j] = max(dp[u][j], dp[top[i]][j]);
			}
		}
	}
	int ans = 0;
	for (int i=0;i<n;i++){
		for (int j=0;j<26;j++){
			ans =max(ans, dp[top[i]][j]);
		}
	}
	cout << ans << "\n";
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