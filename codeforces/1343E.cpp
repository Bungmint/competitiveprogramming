// Problem: E. Weights Distributing
// Contest: Codeforces - Codeforces Round #636 (Div. 3)
// URL: https://codeforces.com/problemset/problem/1343/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define REP(a) F0R(_, a)

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

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

struct chash
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

void bfs(vi&dist, int source, vector<vi>&g){
	dist[source] = 0;
	queue<pi> q;
	q.push({0,source});
	while(sz(q)){
		auto [d, v] = q.front();
		q.pop();
		for (int e:g[v]){
			if (dist[e]>d+1){
				dist[e] = d+1;
				q.push({dist[e], e});
			}
		}
	}
}


void solve()
{
	int n, m, a, b, c;
	cin >>n >> m>>a>>b>>c;
	vl p(m+1), pref(m+1);
	vector<vi> g(n+1);
	vi distFA(n+1,INF), distFC(n+1,INF), distFB(n+1,INF);
	FOR(i,1,m+1) cin >> p[i];
	sort(all(p));
	FOR(i,1,m+1) pref[i]=pref[i-1]+p[i];
	F0R(i,m){
		int u,v;
		cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	bfs(distFA, a,g), bfs(distFC,c,g),bfs(distFB,b,g);
	ll ans = LLONG_MAX;
	FOR(i,1,n+1){
		int sum = distFA[i]+distFC[i];
		int overlap = distFB[i];
		if(sum+overlap<=m)ckmin(ans,pref[sum+overlap]+pref[overlap]);
	}
	cout << ans << "\n";
	
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}