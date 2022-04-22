//Copyright © 2022 Youngmin Park. All rights reserved.
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

struct Edge{
	int to, c;
	int p;
};

const int N = 1e5;
map<int, vector<Edge>> adj[N];
ll dp[N];
map<int, ll> psum[N], dp2[N];

void solve()
{
	int n, m;
	cin >> n >> m;
	REP(m) {
		int u, v, c, p;
		cin >> u >> v >> c >> p;
		u--, v--;
		adj[u][c].pb({v, c, p});
		adj[v][c].pb({u, c, p});
		psum[u][c] += p, psum[v][c] += p;
	}
	memset(dp, 0x3f, sizeof(dp));
	pqg<tuple<ll, int, int>> pq;
	dp[0] = 0;
	pq.push({0LL, 0, 0});
	while (sz(pq)) {
		auto [cost, u, c] = pq.top(); pq.pop();
		if (c) {
			if (cost != dp2[u][c]) continue;
			for (auto &e : adj[u][c]) {
				ll add = psum[u][c] - e.p;
				if (ckmin(dp[e.to], cost + add)) {
					pq.push({dp[e.to], e.to, 0});
				}
			}
		}else{
			if (cost != dp[u]) continue;
			for (auto &v : adj[u]) {
				for (auto &e : v.se) {
					ll case1 = psum[u][e.c] - e.p;
					if (ckmin(dp[e.to], case1 + cost)) {
						pq.push({dp[e.to], e.to, 0});
					}
					ll case2 = e.p + cost;
					if (ckmin(dp[e.to], case2)) {
						pq.push({dp[e.to], e.to, 0});
					}
					if (!dp2[e.to].count(e.c) || ckmin(dp2[e.to][e.c], cost)) {
						dp2[e.to][e.c] = cost;
						pq.push({dp2[e.to][e.c], e.to, e.c});
					}
				}
			}
		}
	}
	cout << (dp[n - 1] > LINF ? -1 : dp[n - 1]);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}