// Problem: C. Fools and Roads
// Contest: Codeforces - Codeforces Round #121 (Div. 1)
// URL: https://codeforces.com/problemset/problem/191/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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
#define ub upper_bound

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

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

struct chash
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

const int N = 100001;
vi g[N];
int up[N][20], depth[N];
int a[N];

void dfs(int v,int pv){
	for (int e:g[v]){
		if (e!=pv){
			up[e][0] = v, depth[e] = depth[v]+1;
			for (int i=1;i<20;++i) up[e][i] = up[up[e][i-1]][i-1];
			dfs(e,v);
		}
	}
}
void dfsSum(int u, int pu){
	for (int e:g[u]){
		if (e!=pu){
			dfsSum(e,u);
			a[u] += a[e];
		}
	}
}

int lca(int a,int b){
	if (depth[a]<depth[b])swap(a,b);
	int d = depth[a]-depth[b];
	for (int i=19;i>=0;i--)if (d&(1<<i)) a = up[a][i];
	if (a==b) return a;
	for (int i=19;i>=0;--i) if (up[a][i]!=up[b][i]) a = up[a][i], b= up[b][i];
	return up[a][0];
}

struct Edge{
	int u, v;
};

void solve()
{
	int n;
	cin >> n;
	vector<Edge> edges(n-1);
	for (int i=0;i<n-1;++i){
		int u,v;
		cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
		edges[i] = {u,v};
	}
	dfs(1,0);
	int k;
	cin >> k;
	for (int i=0;i<k;++i){
		int u, v;
		cin >> u >> v;
		int t = lca(u,v);
		a[u]++, a[v]++, a[t]-=2;
	}
	dfsSum(1,0);
	for (int i=0;i<n-1;++i){
		Edge e = edges[i];
		if (depth[e.u]<depth[e.v]) swap(e.u, e.v);
		cout << a[e.u]<< " ";
	}
	cout << endl;
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