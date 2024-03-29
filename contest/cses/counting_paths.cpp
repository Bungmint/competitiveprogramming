// Problem: Counting Paths
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1136
// Memory Limit: 512 MB
// Time Limit: 1000 ms
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

const int LOG = 20;

void solve()
{
	int n,q;
	cin >> n>>q;
	vector<vi> g(n+1), up(n+1, vi(LOG));
	vi a(n+1), b(n+1),man(n+1), depth(n+1), ans(n+1);
	for (int i=0;i<n-1;++i){
		int u,v;
		cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	function<void(int,int)> dfs = [&](int v, int pv){
		for (int e:g[v]){
			if (e!=pv){
				depth[e] = depth[v]+1;
				up[e][0] = v;
				for (int i=1;i<LOG;++i) up[e][i] = up[up[e][i-1]][i-1];
				dfs(e,v);
			}
		}
	};
	function<void(int,int)> sub = [&](int v, int pv){
		for (int e:g[v]){
			if (e!=pv){
				sub(e,v);
				ans[v]+=a[e];
			}
		}
		ans[v] +=man[v]+ a[v];
		a[v] = ans[v]+b[v];
	};
	auto lca = [&](int a, int b){
		if (depth[a]<depth[b]) swap(a,b);
		int d = depth[a]-depth[b];
		for (int i=LOG-1;i>=0;i--) if ((1<<i)&d) a = up[a][i];
		if (a==b) return a;
		for (int i=LOG-1;i>=0;i--) if (up[a][i]!=up[b][i]) a = up[a][i], b = up[b][i];
		return up[a][0];
	};
	dfs(1,0);
	while(q--){
		int u,v,w;
		cin >> u >> v;
		w = lca(u,v);
		if (depth[u]<depth[v])swap(u,v);
		if (v==w){
			a[u]++; b[w]--;
		}else a[u]++, a[v]++, b[w]--, man[w]--;
	}
	dbg(a, b);
	sub(1,0);
	for (int i=1;i<=n;++i) cout << ans[i]<<" ";
	
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}