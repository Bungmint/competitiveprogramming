#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
#define REP(i,s,n) for (int i=s;i<n;i++)
using ll = long long;
typedef vector<int> vi;
typedef pair<int, int> pi;

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
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

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353
const int N=1e5+1;
int c[N], vis[N], u, v, col, n,m;
vi adj[N];
unordered_set<int,custom_hash> s1[N];

void dfs(int V){
	if (vis[V]) return;
	vis[V] = true;
	for (auto &e:adj[V]){
		dfs(e);
		if (c[e]!=c[V]){
			s1[c[V]].insert(c[e]);
			s1[c[e]].insert(c[V]);
		}
	}
}

void solve()
{
	cin >> n>>m;
	set<int> colors;
	REP(i,1,n+1){cin >>c[i];colors.insert(c[i]);}
	REP(i,0,m)cin >> u >> v, adj[u].PB(v), adj[v].PB(u);
	int ans=-1, num = -1;
	REP(i,1,n+1){
		if (!vis[i]) dfs(i);
	}
	for (auto &x:colors){
		dbg(s1[x]);
		if (ans<(int)s1[x].size())ans = (int)s1[x].size(), num = x;
	}
	cout << num << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}