// Problem: Problem 2. Moorio Kart
// Contest: USACO - USACO 2019 February Contest, Platinum
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=925
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2021 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
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
template <typename T, size_t SZ>
using ar = array<T, SZ>;

#define all(v) (v).begin(), (v).end()
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

inline namespace RecursiveLambda{
	template <typename Fun>
	struct y_combinator_result{
		Fun fun_;
		template <typename T> 
		explicit y_combinator_result(T &&fun): fun_(forward<T>(fun)){}
		template <typename...Args>
		decltype(auto) operator()(Args &&...args){
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun){
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

void setIO(string s) // USACO
{
	#ifndef LOCAL
	    freopen((s + ".in").c_str(), "r", stdin);
	    freopen((s + ".out").c_str(), "w", stdout);
	#endif
}

void add_(pii& a, pii b) {
	a = make_pair((a.fi + b.fi) % MOD, (a.se + b.se) % MOD);
}
pii mul(pii a, pii b) {
	return {1LL * a.fi * b.fi % MOD, (1LL * a.fi * b.se + 1LL * a.se * b.fi) % MOD};
}
void mul_(int& a, int b){
	a = 1LL * a * b % MOD;
}

bool vis[1500], yur[1500][1500];
int dist[1500];
pii ways[2501];
pii dp[2][2501];
int cc, n, m, x, y, current, previous = 1;
vi gg;

void solve()
{
	cin >> n >> m >> x >> y;
	vector<vpi> g(n);
	REP(m) {
		int u, v, d;
		cin >> u >> v >> d;
		u--, v--;
		g[u].pb(make_pair(v, d)), g[v].pb(make_pair(u, d)); 
	}
	auto dfsInit = y_combinator([&](auto dfsInit, int u)->void{
		vis[u] = 1;
		gg.pb(u);
		for (auto &[v, d] : g[u]) {
			if (!vis[v]) {
				dfsInit(v);
			}
		}
	});
	auto dfs = y_combinator([&](auto dfs, int u, int pu)->void{
		vis[u] = 1;
		for (auto &[v, d] : g[u]) {
			if (v != pu) {
				dist[v] = dist[u] + d;
				dfs(v, u);
			}
		}
	});
	dp[previous][min(y, (n - m) * x)] = {1, (n - m) * x % MOD};
	F0R(i, n) {
		if (!vis[i]) {
			dbg();
			gg.clear(); 
			fill(dp[current], dp[current] + y + 1, make_pair(0, 0));
			fill(ways, ways + y + 1, make_pair(0, 0));
			dfsInit(i);
			for (auto &v : gg) {
				dist[v] = 0;
				dfs(v, -1);
				for (auto &u : gg) {
					if (u != v && !yur[u][v]) {
						add_(ways[min(y, dist[u])], make_pair(1, dist[u]));
						// dbg(ways[min(y, dist[u])]);
						yur[u][v] = yur[v][u] = 1;
					}
				}
			}
			FOR(j, 0, y + 1) {
				if (ways[j].fi == 0 && ways[j].se == 0) continue;
				{
					F0R(k, y + 1) {
						add_(dp[current][min(y, k + j)], mul(dp[previous][k], ways[j]));
						// dbg(dp[current][min(y, k + j)]);
					}
				}
			}
			swap(previous, current);
		}
	}
	int ans = dp[previous][y].se;
	dbg(ans);
	FOR(i, 1, n - m) mul_(ans, i * 2);
	cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    setIO("mooriokart");
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}