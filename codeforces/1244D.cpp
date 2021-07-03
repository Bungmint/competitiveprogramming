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
const int MOD = 1e9 + 7; //998244353
const int N = 1e5+1;
vi G[N], order;
int c[N][3];

void dfs(int V,int pV){
	order.pb(V);
	for (int e:G[V]){
		if (e!=pV) dfs(e,V);
	}
}

void solve()
{
	int n;
	cin >> n;
	for (int i=0;i<3;++i) for (int j=0;j<n;++j){
		cin >> c[j][i];
	}
	for (int i=0;i<n-1;++i){
		int u, v;
		cin >> u >> v;
		u--; v--;
		G[u].pb(v); G[v].pb(u);
	}
	int st = 0;
	for (int i=0;i<n;++i){
		if (sz(G[i])>=3){
			cout << -1 << "\n";
			return;
		}
		if (sz(G[i])==1) st = i;
	}
	dfs(st,-1);
	ll ans = LINF;
	ar<int,3> config;
	vector<ar<int,3>> v = {{0,1,2}, {1,0,2}, {0,2,1}, {1,2,0}, {2,0,1}, {2,1,0}};
	for (int i=0;i<6;++i){
		ar<int,3> cur = v[i];
		dbg(cur);
		ll val = 0;
		for (int j=0;j<n;++j){
			val += c[order[j]][cur[j%3]];
			dbg(cur[j%3]);
		}
		if (ans>val){
			ans = val;
			config = cur;
		}
	}
	dbg(order);
	
	cout << ans << "\n";
	vi vert(n);
	for (int i=0;i<n;++i){
		vert[order[i]] = config[i%3]+1;
	}
	for (int x:vert) cout << x << " ";
	cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}