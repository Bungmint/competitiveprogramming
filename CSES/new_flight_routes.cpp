// Problem: New Flight Routes
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1685
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
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
using ld = long double;

#define all(v) (v).begin(), (v).end()
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define REP(a) F0R(_, a)

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
#define dbg(...) 42
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
    size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

const int N = 1e5+1;
vi g[N], revg[N], order,comp,condense[N];
int indeg[N], outdeg[N], root[N];
bool vis1[N], vis2[N], vis3[N];
set<int> sink[N], source[N];

void dfs1(int v){
	vis1[v] = true;
	for (auto e:g[v]) if (!vis1[e]) dfs1(e);
	order.pb(v);
}
void dfs2(int v){
	vis2[v] = true;
	comp.pb(v);
	for(auto e:revg[v]) if (!vis2[e]) dfs2(e);
}
void dfs3(int v, int cnt){
	vis3[v] = 1;
	for(auto e:condense[v]) if (!vis3[e]) dfs3(e, cnt);
	if (outdeg[v]==0) sink[cnt].insert(v);
	if (indeg[v]==0) source[cnt].insert(v);
}


void solve()
{
	int n, m;
	cin >> n >> m;
	REP(m){
		int u,v;
		cin >> u >> v;
		g[u].pb(v);
		revg[v].pb(u);
	}
	FOR(i, 1, n+1){
		if (!vis1[i]) dfs1(i);
	}
	reverse(all(order));
	dbg(order);
	int cc = 0;
	for (auto x:order){
		if (!vis2[x]){
			comp.clear();
			dfs2(x);
			for (auto y:comp) root[y] = x;
			cc++;
			dbg(root[x]);
		}
	}
	if (cc==1){
		cout << "0"<<"\n";
		return;
	}
	FOR(i, 1, n+1){
		for (auto j:g[i]){
			if (root[i]!=root[j]){
				indeg[root[j]]++;
				outdeg[root[i]]++;
				condense[root[i]].pb(root[j]);
			}
		}
	} 
	int cnt = 0;
	FOR(i, 1, n+1){
		if (!vis3[root[i]]){
			dfs3(root[i], cnt);
			cnt++;
		}
	}
	vpi ans;
	int coom = 0;
	F0R(i, cnt){
		coom = *sink[i].begin();
		dbg(sink[i], source[(i+1)%cnt]);
		ans.pb({*sink[i].begin(), *source[(i+1)%cnt].begin()});
		sink[i].erase(sink[i].begin());
		source[(i+1)%cnt].erase(source[(i+1)%cnt].begin());
	}
	dbg();
	set<int> snk,src;
	F0R(i, cnt){
		for (auto x:sink[i]) snk.insert(x);
		for(auto x:source[i]) src.insert(x);
	}
	while(sz(snk)&&sz(src)){
		int u = *snk.begin(), v = *src.begin();
		ans.pb({u,v});
		snk.erase(u), src.erase(v);
		coom = u;
	}
	while(sz(snk)){
		int u = *snk.begin();
		snk.erase(u);
		ans.pb({u, coom});
	}
	while(sz(src)){
		int u = *src.begin();
		src.erase(u);
		ans.pb({coom, u});
	}
	cout << sz(ans)<<"\n";
	for (auto [u,v]: ans) cout << u << " "<< v << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}