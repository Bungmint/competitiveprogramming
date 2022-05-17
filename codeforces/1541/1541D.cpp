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
vi G[201];
const int LOG = 10;
int up[201][LOG], F[201][201], dep[201];

ll mod_pow(ll base, ll exp)
{
    if (exp == 0)
        return 1LL;
    if (exp == 1)
        return base;
    ll m = mod_pow(base, exp / 2);
    if (exp % 2 == 0)
        return (m * m) % MOD;
    return (((m * m) % MOD) * base) % MOD;
}

ll inv_mod(ll a)
{
    return mod_pow(a, MOD - 2);
}

ll mul(ll a, ll b){
	return	(((a)%MOD)*(b)%MOD)%MOD;
}

void dfs(int V,int pV){
	for (int e:G[V]){
		if (e==pV)continue;
		dep[e] = dep[V]+1;
		up[e][0] = V;
		for (int i=1;i<LOG;++i) up[e][i] = up[up[e][i-1]][i-1];
		dfs(e,V);
	}
}

int lca(int a, int b){
	if (dep[a]<dep[b]) swap(a,b);
	int d = dep[a]-dep[b];
	for(int i=LOG-1;i>=0;i--){
		if ((1<<i)&d){
			a = up[a][i];
		}
	}	
	if (a==b)return a;
	for(int i=LOG-1;i>=0;i--){
		if (up[a][i]!=up[b][i]){
			a = up[a][i]; b= up[b][i];
		}
	}	
	return up[a][0];
}



void solve()
{
	int n;
	cin >> n;
	for (int i=0;i<n-1;++i){
		int u, v;
		cin >> u >> v;
		G[u].PB(v);
		G[v].PB(u);
	}
	ll ans = 0LL;
	for (int x=0;x<=n;x++){
		for (int y=0;y<=n;y++){
			if (x==0) F[x][y] = 0;
			else if (y==0) F[x][y] = 1;
			else{
				F[x][y] = mul(F[x-1][y]+F[x][y-1], inv_mod(2));
			}
		}
	}
	for (int i=1;i<=n;++i){
		memset(up, 0, sizeof(up));
		dfs(i,0);
		for (int j=1;j<=n;++j) for (int k=j+1;k<=n;++k){
			int l = lca(j, k);
			ans = (ans+ F[dep[j]-dep[l]][dep[k]-dep[l]])%MOD;
		}
	}
	cout << mul(ans, inv_mod(n))<< "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}