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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
const int N = 2e5+1;
vi G[N];
ar<int,3> Edge[N];
vi order;
bool vis[N];

void dfs(int V){
	vis[V] = 1;
	for (int e:G[V]){
		if (!vis[e]) dfs(e);
	}
	order.pb(V);
}


void solve()
{
	int n, m;
	cin >> n >> m;
	dbg(n,m);
	order.clear();
	vi v(n+1);
	for (int i=0;i<=n;++i) G[i].clear(), vis[i] = 0;
	for (int j=0;j<m;++j){
		int t, x, y;
		cin >> t >> x >> y;
		Edge[j] = {t, x,y};
		if (t) G[x].pb(y);
	}
	for (int i=1;i<=n;++i){
		if (!vis[i]) dfs(i);
	}
	reverse(all(order));
	for (int i=0;i<n;++i) v[order[i]] = i;
	for (int i=0;i<m;++i){
		if (Edge[i][0]){
			if (v[Edge[i][1]]>v[Edge[i][2]]){
				cout << "NO\n";
				return;
			}
		}else{
			if (v[Edge[i][1]]>v[Edge[i][2]]) swap(Edge[i][1], Edge[i][2]);
		}
	}
	cout << "YES\n";
	for (int i=0;i<m;++i) cout << Edge[i][1]<< " "<< Edge[i][2]<<"\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}