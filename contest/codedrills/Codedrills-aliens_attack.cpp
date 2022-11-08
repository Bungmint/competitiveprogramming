#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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
const int N = 1e5+1;
int v[N];
int anc[N][101], dep[N], ans[N];
vector<int> adj[N];

void dfs(int V, int pV){
	anc[V][v[V]] = V;
	for (int &e:adj[V]){
		if (e==pV) continue;
		dep[e] = dep[V]+1;
		for (int i=1;i<=100;i++){
			anc[e][i] = anc[V][i];
			if (anc[e][i] != 0 &&gcd(i, v[e])==1){
				if (ans[e]==-1) ans[e] = anc[V][i];
				else if (dep[ans[e]]<dep[anc[V][i]]) ans[e] = anc[V][i];
			}
		}
		anc[e][v[e]] = e;
		
		dfs(e,V);
	}
}

void solve()
{
	for (int i=0;i<N;i++) adj[i].clear();
	memset(anc,0,sizeof(anc));
	memset(ans, -1, sizeof(ans));
	int n,tm;
	cin >> n;
	for (int i=1;i<=n;i++){
		cin >> v[i];
	}
	for (int i=0;i<n-1;i++){
		int u,v1;
		cin >> u >>v1;
		adj[u].PB(v1);
		adj[v1].PB(u);
	}
	dfs(1,0);
	for (int i=1;i<=n;i++){
		cout << ans[i]<<" ";
	}
	cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}