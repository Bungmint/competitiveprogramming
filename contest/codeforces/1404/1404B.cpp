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
const int N = 1e5+1, LOG = 20;
int up[N][LOG], dep[N], mxdep=0, mx=0, dist=0, l[N], res = 0;
vi G[N];


void dfs(int V, int pV){
	if (dep[V]>mxdep){
		mx = V;
		mxdep= dep[V];
	}
	for (int e:G[V]){
		if (e==pV) continue;
		dep[e] = dep[V] +1;
		up[e][0] =  V;
		for (int i=1;i<LOG;++i) up[e][i] = up[up[e][i-1]][i-1];
		dfs(e,V);
	}
}

int lca(int a, int b){
	if (dep[a]<dep[b]) swap(a, b);
	int k = dep[a]-dep[b];
	for (int i=LOG-1;i>=0;i--){
		if (k&(1<<i)) a = up[a][i];
	}
	if (a==b) return a;
	for (int i=LOG-1;i>=0;i--){
		if (up[a][i]!=up[b][i]){
			a = up[a][i];
			b = up[b][i];
		}
	}
	return up[a][0];
}

void dia(int V,int pV){
	if (l[V]>res) res = l[V];
	for (int e:G[V]){
		if (e!=pV){
			l[e] = l[V] +1;
			dia(e,V);
		}
	}
}

void solve()
{
	int n, a, b, da, db;
	cin >> n >> a >> b >> da >> db;
	for (int i=0;i<=n;++i) G[i].clear(), l[i] = 0;
	for (int i=0;i<n-1;++i){
		int u,v;
		cin >> u >> v;
		G[u].pb(v);G[v].pb(u);
	}
	mx = mxdep = 0;
	dist = res = 0;
	dfs(1,0);
	int p = lca(a, b);
	int d = dep[a]-dep[p] + dep[b]-dep[p];
	if (da>=d){
		cout << "Alice\n";
		return;
	}
	dia(mx, 0);
	if (da*2>=res){
		cout << "Alice\n";
		return;
	}
	if (db>da*2){
		cout << "Bob\n";
		return;
	}
	cout << "Alice\n";
	return;
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