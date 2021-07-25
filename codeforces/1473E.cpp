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
int n, m;
ll d[200000][2][2];
vpi G[200000];

void dijkstra(int v=0){
	pqg<pair<ll, ar<int,3>>> pq;
	memset(d, 0x3f, sizeof(d));
	d[0][0][0] = 0;
	pq.push({d[0][0][0],{ 0, 0, 0}});
	while(!pq.empty()){
		pair<ll,ar<int,3>> a = pq.top();
		auto [v, mx, mn] = a.se;
		pq.pop();
		if (a.fi>d[v][mx][mn]) continue;
		for (auto [e, w]:G[v]){
			for (int i=0;i<=1-mx;++i){
				for (int j=0;j<=1-mn;++j){
					
					if (d[e][mx|i][mn|j]>a.fi+(1-i+j)*w){
						d[e][mx|i][mn|j]=a.fi+(1-i+j)*w;
						pq.push({d[e][mx|i][mn|j], {e, mx|i, mn|j}});
					}
				}
			}
		}
	}
}

void solve()
{
	cin >> n >> m;
	for (int i=0;i<m;++i){
		int u,v,w;
		cin >> u >> v>>w;
		u--;v--;
		G[u].pb({v,w});
		G[v].pb({u,w});
	}
	dijkstra(0);
	for (int i=1;i<n;++i){
		cout << d[i][1][1]<<" ";
	}
	cout << "\n";
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