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
vi order;
bool vis[1000], dp1[1000][1000], dp2[1000][1000];

void topsort(int v, vector<vi>& g){
	vis[v] = 1;
	for (int e:g[v]){
		if (!vis[e]) topsort(e, g);
	}
	order.pb(v);
}

void solve()
{
	int n1, n2, m1, m2;
	cin >> n1 >> n2 >> m1 >> m2;
	vector<vi> g1(n1), g2(n2);
	for (int i=0;i<m1;++i){
		int u,v;
		cin >> u >> v;
		u--;v--;
		g1[u].pb(v);
	}
	for (int i=0;i<m2;++i){
		int u,v;
		cin >> u >> v;
		u--;v--;
		g2[u].pb(v);
	}
	topsort(0, g1);
	reverse(all(order));
	dp1[0][0] = 1;
	for (int x:order){
		for (int e:g1[x]){
			for (int j=1;j<n1;++j){
				if (dp1[x][j-1]) dp1[e][j] = 1;
			}
		}
	}
	
	memset(vis, 0, sizeof(vis));
	order.clear();
	topsort(0, g2);
	reverse(all(order));
	dp2[0][0] = 1;
	for (int x:order){
		for (int e:g2[x]){
			for (int j=1;j<n2;++j){
				if (dp2[x][j-1]) dp2[e][j] = 1;
			}
		}
	}
	int q;
	cin >> q;
	while(q-->0){
		int k;
		cin >> k;
		bool ok = 0;
		for (int i=0;i<n1;++i){
			if (k-i>=0&&k-i<n2&&dp2[n2-1][k-i]&&dp1[n1-1][i]) ok = 1;
		}
		cout << (ok ? "Yes":"No")<<"\n";
	}
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