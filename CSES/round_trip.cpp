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
const int N = 1e5+1;
vi G[N];
int p[N];
bool vis[N];

void dfs(int V, int pV, int &a, int &b){
	if (vis[V]) return;
	vis[V] = true;
	for (int e:G[V]){
		if (e==pV) continue;
		if (vis[e]&&p[e]!=V){
			a = e, b = V;
			continue;
		}
		p[e] = V;
		dfs(e,V, a,b);
	}
}

void solve()
{
	int n, m;
	cin >> n >> m;
	for (int i=1;i<=m;i++){
		int u, v;
		cin >> u >> v;
		G[u].PB(v);
		G[v].PB(u);
	}
	for (int i=1;i<=n;i++){
		if (!vis[i]){
			int u=-1,v=-1;
			dfs(i,-1, u, v);
			if (u!=-1){
				vi r1, r2;
				while(u){
					r1.PB(u);
					u = p[u];
				}
				while(v){
					r2.PB(v);
					v = p[v];
				}
				while(sz(r1)&&sz(r2)&&r1[sz(r1)-1]==r2[sz(r2)-1]){
					u = r1.back();
					r1.pop_back();
					r2.pop_back();
				}
				r1.PB(u); r2.PB(u);
				reverse(all(r1));
				cout << sz(r1)+sz(r2)<<"\n";
				for (int x:r1) cout << x << " ";
				for (int x:r2) cout << x << " ";
				cout << "\n";
				return; 
			}
		}
	}
	cout << "IMPOSSIBLE\n";
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