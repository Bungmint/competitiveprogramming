// Problem: E. Blood Cousins Return
// Contest: Codeforces - Codeforces Round #151 (Div. 2)
// URL: https://codeforces.com/contest/246/problem/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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
const int MOD = 1e9 + 7; //998244353;
const int N = 1e5+1;
vi g[N];
int a[N];
string b[N];
vector<string> order;
int subtree[N], st[N], ft[N], ver[N], timer = 0, depth[N];
int ans[N];
vpi queries[N];
map<int, int> cnt[2*N+1];

void dfsS(int v, int pv){
	subtree[v] = 1;
	st[v] = timer++;
	ver[st[v]] = v;
	for (int e:g[v]) if (e!=pv) depth[e] = depth[v]+1,dfsS(e,v), subtree[v] += subtree[e];
	ft[v] = timer;
}
void dfs(int v,int pv,bool keep){
	int bigChild = -1, mx = 0;
	for (int e:g[v]) if (e!=pv&&subtree[e]>mx) mx = subtree[e], bigChild = e;
	for (int e:g[v]) if (e!=pv&&e!=bigChild) dfs(e,v,0);
	if (bigChild!=-1) dfs(bigChild, v, 1);
	for (int e:g[v])
		if (e!=pv&&e!=bigChild){
			for (int j=st[e];j<ft[e];++j){
				cnt[depth[ver[j]]][a[ver[j]]]++;
			}
		}
	cnt[depth[v]][a[v]]++;
	for (auto [k, id]:queries[v]){
		ans[id] = sz(cnt[depth[v]+k]);
	}
	if (!keep) for (int j=st[v];j<ft[v];++j){
		cnt[depth[ver[j]]][a[ver[j]]]--;
		if (cnt[depth[ver[j]]][a[ver[j]]]==0) cnt[depth[ver[j]]].erase(a[ver[j]]);
	} 
}

void solve()
{
	int n, m;
	cin >> n;
	vi root;
	for (int i=1;i<=n;++i){
		int r;
		cin >> b[i]>>r;
		order.pb(b[i]);
		if (r) g[r].pb(i), g[i].pb(r);
		else root.pb(i);
	}
	sort(all(order));
	for (int i=1;i<=n;++i){
		a[i] = lb(all(order), b[i])-order.begin();
	}
	cin >> m;
	for (int i=0;i<m;++i){
		int v, k;
		cin >> v >> k;
		queries[v].pb({k,i});
	}
	dbg(root);
	for (int i:root){
		timer=0;
		dfsS(i,0);
		dfs(i,0,0);
	}
	for (int i=0;i<m;++i) cout << ans[i]<<"\n";
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