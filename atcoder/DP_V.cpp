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
int n, MOD;
vi G[100001];
vl L[100001], R[100001];
int id[100001];
int f[100001], g[100001];

void add(int &a, int b){
	a = ((ll)a+(ll)b)%MOD;
}
void mult(int &a,int b){
	a = ((ll)a*(ll)b)%MOD;
}
int mul(int a,int b){
	return ((ll)a*(ll)b)%MOD;
}

void dfs1(int v, int pv){
	f[v] = 1;
	vi child;
	for (int e:G[v]){
		if (e!=pv){
			dfs1(e,v);
			child.pb(e);
			mult(f[v], 1+f[e]);
		}
	}
	L[v].resize(sz(child));
	R[v].resize(sz(child));
	for (int i=0;i<sz(child);++i){
		id[child[i]] = i;
		L[v][i] = (i? mul(L[v][i-1], 1+f[child[i]]):(1+f[child[i]]));
	}
	for (int i=sz(child)-1;i>=0;i--){
		R[v][i] = (i==sz(child)-1?(1+f[child[i]]): mul(R[v][i+1], 1+f[child[i]]));
	}
}
void dfs2(int v,int pv){
	if (pv){
		g[v] = 1+g[pv];
		int SZ = sz(L[pv]);
		int j = id[v];
		int val = 1;
		if (j>0) mult(val, L[pv][j-1]);
		if (j<SZ-1) mult(val, R[pv][j+1]);
		mult(g[v], val);
	}
	for (int e:G[v]) if (e!=pv) dfs2(e,v);
}

void solve()
{
	cin >> n >> MOD;
	for (int i=0;i<n-1;++i){
		int u,v;
		cin >> u >> v;
		G[u].pb(v), G[v].pb(u);
	}
	dfs1(1,0);
	dfs2(1,0);
	for (int i=1;i<=n;++i){
		cout << mul(f[i], g[i]+1)<<"\n";
	}
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