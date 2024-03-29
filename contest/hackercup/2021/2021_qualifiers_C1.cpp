// Problem: C1: Gold Mine - Chapter 1
// Contest: Facebook Coding Competitions - Facebook Hacker Cup 2021 Qualification Round
// URL: https://www.facebook.com/codingcompetitions/hacker-cup/2021/qualification-round/problems/C1
// Memory Limit: 1024 MB
// Time Limit: 360000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
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
#define dbg(...) 42
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
    size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

const int LOG = 6;

void solve()
{
	int n;
	cin >> n;
	vi a(n+1),pathSum(n+1), depth(n+1);
	static int up[51][LOG];
	vector<vi> g(n+1);
	FOR(i, 1, n+1) cin >> a[i];
	REP(n-1){
		int u, v;
		cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	function<void(int,int)> dfs = [&](int v, int pv){
		for (auto e:g[v]){
			if (e==pv) continue;
			up[e][0] = v;
			FOR(i, 1, LOG) up[e][i] = up[up[e][i-1]][i-1];
			depth[e] = depth[v] + 1;
			pathSum[e] = pathSum[v] + a[e], dfs(e,v);
		}
	};
	auto lca = [&](int a, int b)->int{
		if (depth[a]<depth[b])swap(a, b);
		int d = depth[a]-depth[b];
		R0F(i, LOG) if (d&(1<<i)) a = up[a][i];
		if (a==b) return a;
		R0F(i, LOG)if (up[a][i]!=up[b][i]) a = up[a][i], b = up[b][i];
		return up[a][0];
	};
	dfs(1,0);
	int ans = 0;
	// Going straight back up
	FOR(i, 1, n+1) ckmax(ans, pathSum[i]+a[1]);
	//Yoink
	FOR(u, 2, n+1)FOR(v, 2, n+1){
		if (lca(u,v)==1){
			ckmax(ans, pathSum[u]+pathSum[v]+a[1]);
		}
	}
	cout << ans << "\n";
	
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    cin >> testcase;
    FOR(i, 1, testcase+1)
    {
    	cout << "Case #"<<i<< ": ";
        solve();
    }
}