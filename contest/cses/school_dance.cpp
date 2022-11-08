// Problem: School Dance
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1696
// Memory Limit: 512 MB
// Time Limit: 1000 ms
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

const int MX = 1002; //change this
template<typename T, int N>
struct EdmondKarp{
	T cap[N][N];
	vi g[N];
	T bfs(int s, int t, vi &p){
		fill(all(p), -1);
		p[s]=-2;
		queue<pair<T,T>> q;
		q.push({s, INF});//change this
		while(sz(q)){
			auto [cur, flow] = q.front();
			q.pop();
			for (int e:g[cur]){
				if (p[e]==-1&&cap[cur][e]){
					p[e] = cur;
					T newflow = min(flow, cap[cur][e]);
					if (e==t){
						return newflow;
					}
					q.push({e, newflow});
				}
			}
		}
		return 0;
	}
	T maxFlow(int s, int t){
		T flow = 0;
		vi p(N+1);
		T newflow = 0;
		while((newflow=bfs(s,t,p))){
			flow += newflow;
			int cur = t;
			while(cur!=s){
				int prev = p[cur];
				cap[prev][cur]-=newflow;
				cap[cur][prev] += newflow;
				cur = prev;
			}
		}
		return flow;
	}
	void dfs(int v, vector<bool>& vis, vi &ans){
		vis[v] = 1;
		ans.pb(v);
		for (int e:g[v]){
			dbg(cap[v][e],v,e);
			if (cap[v][e]&&!vis[e]) dfs(e, vis,ans);
		}
	}
	pair<T,vi> minCut(int s,int t){
		T x = maxFlow(s,t);
		vi ans;
		vector<bool> vis(N, false);
		dfs(s, vis, ans);
		return {x, ans};
	}
};

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	EdmondKarp<int, MX> ek;
	vpi y(k);
	for (int i=0;i<k;++i){
		int u, v;
		cin >> u >> v;
		v+=n;
		y[i] = {u,v};
		
		ek.g[0].pb(u),ek.g[u].pb(0);
		ek.g[u].pb(v), ek.g[v].pb(u);
		ek.g[v].pb(n+m+1), ek.g[n+m+1].pb(v);
		ek.cap[0][u] =1,  ek.cap[u][v] =1, ek.cap[v][n+m+1] = 1;
	}
	int x = ek.maxFlow(0, n+m+1);
	cout << x << endl;
	for (auto p:y){
		if (ek.cap[p.fi][p.se]==0){
			cout << p.fi <<" "<< p.se-n << "\n";
		}
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