// Problem: Problem 1. Milk Pumping
// Contest: USACO - USACO 2019 December Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=969
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
const ld eps = 1e-9;

bool great(ld a, ld b){
	return (a-b>eps);
}
bool low(ld a, ld b){
	return (b-a>eps);
}
ld _div(int a, int b){
	return (ld)a/(ld)b;
}

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int,pi>>> g(n+1);
	vector<ld> flow(n+1, 0);
	for (int i=0;i<m;++i){
		int u, v, c, f;
		cin >> u >> v >> c >> f;
		g[u].pb({v,{c,f}});
		g[v].pb({u,{c,f}});
	}
	
	priority_queue<pair<ld, ar<int,3>>> dijk;
	flow[1] = LINF;
	dijk.push({LINF, {INF,0,1}});
	while(sz(dijk)){
		ld k = dijk.top().fi;
		auto [f,c,v] = dijk.top().se;
		dijk.pop();
		if (great(flow[v], k)) continue;
		for (auto x:g[v]){
			int e = x.fi;
			auto [C,F] = x.se;
			if (great(_div(min(F,f), C+c), flow[e])){
				flow[e] = _div(min(f,F), C+c);
				dijk.push({flow[e], {min(F,f), C+c, e}});
			}
		}
	}
	int x = flow[n]*(1000000);
	cout << x << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef LOCAL
    	setIO("pump");
    #endif
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}