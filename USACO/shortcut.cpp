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
const int N  =1e4+1;
int c[N], dist[N];
vpi G[N];
vi DAG[N];
int indeg[N], cnt[N];

void solve()
{
	int n, m, t;
	cin >> n >> m>>t;
	for (int i=1;i<=n;++i) cin >> c[i];
	for (int i=0;i<m;++i){
		int u,v, w;
		cin >> u >> v>> w;
		G[u].pb({v,w});
		G[v].pb({u,w});
	}
	pqg<pi> pq;
	fill(dist, dist+N, INF);
	dist[1] = 0;
	pq.push({0, 1});
	while(!pq.empty()){
		auto [d, u] = pq.top();
		pq.pop();
		if (dist[u]<d) continue;
		for (auto [v, w]:G[u]){
			if (dist[v]>d+w){
				dist[v] = d+w;
				pq.push({dist[v],v});
			}
		}
	}
	for (int u=2;u<=n;++u){
		int nxt = INF;
		for (auto [v,w]:G[u]){
			if (dist[v]+w==dist[u]&&v<nxt){
				nxt = v;
			}
		}
		assert(nxt!=INF);
		DAG[u].pb(nxt);
		indeg[nxt]++;
	}
	queue<int> q;
	for (int i=1;i<=n;++i){
		cnt[i] = c[i];
		if (!indeg[i]) q.push(i);
	}
	while(sz(q)){
		int v = q.front();q.pop();
		for (int u:DAG[v]){
			cnt[u] += cnt[v];
			indeg[u]--;
			if (!indeg[u]) q.push(u);
		}
	}
	ll res = 0;
	for (int i=1;i<=n;++i){
		res = max(res, (ll)(dist[i]-t)*cnt[i]);
	}
	cout << res << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef LOCAL
    	setIO("shortcut");
    #endif
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}