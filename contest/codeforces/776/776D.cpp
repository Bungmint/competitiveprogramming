// Problem: D. The Door Problem
// Contest: Codeforces - ICM Technex 2017 and Codeforces Round #400 (Div. 1 + Div. 2, combined)
// URL: https://codeforces.com/contest/776/problem/D
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
const int N = 2e5+1;
vi order, comp, g[N], revg[N];
int id[N];
vi doors[N];
int open[N], n, m;
bool vis[N];

void dfs1(int v){
	vis[v] = 1;
	for (int e:g[v]) if(!vis[e])dfs1(e);
	order.pb(v);
}
void dfs2(int v){
	vis[v] = 1;
	comp.pb(v);
	for (int e:revg[v])if(!vis[e]) dfs2(e);
}

void solve()
{
	cin >> n >> m;
	for (int i=1;i<=n;++i) cin >> open[i];
	for (int i=1;i<=m;++i){
		int t;
		cin >> t;
		for (int j=0;j<t;++j){
			int k;
			cin >> k;
			doors[k].pb(i);
		}
	}
	for (int i=1;i<=n;++i){
		int x = doors[i][0], y = doors[i][1];
		if (open[i]){
			g[x].pb(y),g[x+m].pb(y+m), g[y+m].pb(x+m), g[y].pb(x);
			revg[y].pb(x), revg[y+m].pb(x+m), revg[x+m].pb(y+m), revg[x].pb(y);
		}else{
			g[y+m].pb(x), g[x+m].pb(y), g[x].pb(y+m), g[y].pb(x+m);
			revg[x].pb(y+m), revg[y].pb(x+m), revg[y+m].pb(x), revg[x+m].pb(y);
		}
	}
	for (int i=1;i<=2*m;++i){
		dbg(g[i]);
		if (!vis[i]) dfs1(i);
	}
	reverse(all(order));
	memset(vis, 0, sizeof(vis));
	int cnt = 0;
	for (int x:order){
		dbg(x);
		if (!vis[x]){
			comp.clear();
			dfs2(x);
			dbg(comp);
			for (int y:comp){
				id[y] = cnt;
			}
			cnt++;
		}
	}
	for (int i=1;i<=m;++i){
		if (id[i]==id[i+m]){
			cout << "NO\n";
			return;
		}
	}
	cout << "YES\n";
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