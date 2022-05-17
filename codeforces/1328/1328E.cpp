#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;

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
const int N = 2e5+1, LOG = 20;
vi G[N];
int p[N], up[N][LOG], dep[N];

bool check(int u, int v){ //Checks if v is an ancestor of u
	int diff = dep[u] -dep[v];
	for (int i=LOG-1;i>=0;i--){
		if (diff&(1<<i)) u = up[u][i];
	}
	return u==v;
}

void dfs(int V, int pV){
	for (int e:G[V]){
		if (e==pV) continue;
		dep[e] = dep[V] +1;
		up[e][0] = p[e] = V;
		for (int i=1;i<LOG;i++) up[e][i] = up[up[e][i-1]][i-1];
		dfs(e,V);
	}
}

void solve()
{
	int n, m;
	cin >> n >> m;
	for (int i=0;i<n-1;i++){
		int u, v;
		cin >> u >> v;
		G[u].PB(v); G[v].PB(u);
	}
	dfs(1,0);
	while(m--){
		int k;
		cin >> k;
		vi vertex(k);
		for (int &e:vertex)cin >> e;
		sort(all(vertex), [&](int v1, int v2){
			return dep[v1]>dep[v2];
		});
		dbg(vertex);
		bool ok = 1;
		int st = 0;
		for (int i=0;i<k;i++){
			if (dep[vertex[i]]!= dep[vertex[0]]){
				st = i;
				break;
			}
			ok &= (p[vertex[i]]==p[vertex[0]]);
		}
		if (!ok){
			cout << "NO\n";
			continue;
		}
		for (int i=st;i<k;i++){
			if (vertex[i]==1) break;
			bool cool = check(vertex[0], vertex[i])||check(vertex[0], p[vertex[i]]);
			ok &= cool;
		}
		cout << (ok? "YES\n":"NO\n");
	}
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