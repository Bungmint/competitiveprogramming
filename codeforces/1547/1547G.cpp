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
const int N = 4e5+1;
vi G[N], revG[N];
int infinite[N], dp[N], loop[N];
vi order, comp;
bool vis[N], reach[N];

void simple_dfs(int v){
	reach[v] = 1;
	for (int e:G[v]){
		if (!reach[e]) simple_dfs(e);
	}
	order.pb(v);
}

void dfs2(int v){
	vis[v] = 1;
	comp.pb(v);
	for(int e:revG[v]){
		if (!vis[e]&&reach[e]) dfs2(e);
	}
}

void dfs(int v){
	if (dp[v]==2) return;
	dp[v]++;
	for (int e:G[v]){
		dfs(e);
	}
}


void solve()
{
	int n, m;
	cin >> n >> m;
	order.clear();
	for (int i=1;i<=n;++i){
		G[i].clear();
		revG[i].clear();
		vis[i] = 0;
		reach[i] = 0;
		infinite[i] = 0;
		loop[i] = 0;
		dp[i] = 0;
	}
	for (int i=0;i<m;++i){
		int u,v;
		cin >> u >> v;
		if (u==v){
			loop[u] = 1;
		}else{
			G[u].pb(v);
			revG[v].pb(u);
		}
	}
	simple_dfs(1);
	reverse(all(order));
	dbg(order);
	for (int x:order){
		if (!vis[x]){
			comp.clear();
			dfs2(x);
			dbg(comp);
			queue<int>q;
			if (sz(comp)==1&&loop[x]==0) continue;
			for (int y:comp){
				infinite[y] = 1;
				q.push(y);
			}
			while(!q.empty()){
				int v = q.front();
				q.pop();
				for (int e:G[v]){
					if (!infinite[e]){
						q.push(e);
						infinite[e] = 1;
					}
				}
			}
		}
	}
	dfs(1);
	for (int i=1;i<=n;++i){
		if (!reach[i]) cout << 0 << " ";
		else if (infinite[i]) cout << -1 << " ";
		else  cout << dp[i] << " ";	
	}
	cout << "\n";
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