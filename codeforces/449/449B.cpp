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
ll n,m,k, d[N],p[N];
vector<pair<ll,ll>> adj[N];

void dijkstra(){
	fill(d+1, d+n+1, LINF);
	fill(p+1, p+n+1, 0);
	pqg<pair<ll,ll>> pq;
	d[1] = 0;
	pq.push({d[1], 1});
	while(!pq.empty()){
		ll ds = pq.top().first, v=pq.top().second;
		pq.pop();
		if (ds>d[v]) continue;
		dbg(adj[v]);
		for (auto [dist, u]:adj[v]){
			if (d[u]>d[v]+dist){
				d[u] = d[v] + dist;
				pq.push({d[u], u});
				p[u] = 1;
			}else if (d[u] == d[v]+dist){
				p[u]++;
			}
		}
	}
}


void solve()
{
	cin >> n >> m>> k;
	for (int i=0;i<m;i++){
		int u,v,w;
		cin>> u >> v>>w;
		adj[u].PB({w,v});
		adj[v].PB({w,u});
	}
	vector<pair<int,int>> r(k);
	for (int i=0;i<k;i++) {
		cin >> r[i].first >> r[i].second;
		adj[1].PB({r[i].second, r[i].first});
		adj[r[i].first].PB({r[i].second,1});
	}
	
	int ans = 0LL;
	dijkstra();
	for (int i=0;i<k;i++){
		dbg(r[i].first, d[r[i].first], r[i].second);
		if (d[r[i].first]<r[i].second)ans++;
		else{
			if (r[i].second == d[r[i].first]){
				if (p[r[i].first]>1){
					ans++;
					p[r[i].first]--;
				}
			}
		}
	}
	cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}