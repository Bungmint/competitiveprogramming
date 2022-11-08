// Problem: Problem 1. Fine Dining
// Contest: USACO - USACO 2018 December Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=861
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

void solve()
{
	int n, m, k;
	cin >> n>>m >> k;
	vector<vpi> g(n+1);
	vi dist(n, INT_MAX), distH(n+1, INT_MAX);
	vpi haybales(k);
	for (int i=0;i<m;++i){
		int u,v, w;
		cin >> u >> v >> w;
		u--, v--;
		g[u].pb({v,w});
		g[v].pb({u,w});
	}
	for (int i=0;i<k;++i){
		int id, b;
		cin >> id >> b;
		id--;
		haybales[i] = {id, b};

	}
	dist[n-1] = 0;
	pqg<pi> pq;
	pq.push({dist[n-1], n-1});
	while(sz(pq)){
		auto [d, u] = pq.top();
		pq.pop();
		if (d>dist[u]) continue;
		for (auto [v, w]:g[u]){
			if (dist[v]>d+w){
				dist[v] = d+w;
				pq.push({dist[v], v});
			}
		}
	}
	for (int i=0;i<k;++i){
		auto [id, b] = haybales[i];
		g[n].pb({id, dist[id]-b});
	}
	distH[n] = 0;
	pq.push({distH[n], n});
	while(sz(pq)){
		auto [d, u] = pq.top();
		dbg(d,u);
		pq.pop();
		if (d>distH[u]) continue;
		for (auto [v, w]:g[u]){
			if (distH[v]>d+w){
				distH[v] = d+w;
				pq.push({distH[v], v});
			}
		}
	}
	for (int i=0;i<n-1;++i){
		cout << (dist[i]>=distH[i]? 1:0)<<"\n";
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef LOCAL
    	setIO("dining");
    #endif
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}