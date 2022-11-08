// Problem: Problem 1. Fine Dining
// Contest: USACO - USACO 2018 December Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=861
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<vpi> g(n);
	vi dist(n, INF), yum(n, INF);
	REP(m) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		g[u].pb({v, w}), g[v].pb({u, w});
	}
	pqg<pii> pq;
	dist[n - 1] = 0;
	pq.push({dist[n - 1], n - 1});
	while (sz(pq)) {
		auto [d, u] = pq.top();
		pq.pop();
		if (d > dist[u]) continue;
		for (auto &[v, w] : g[u]) {
			if (ckmin(dist[v], dist[u] + w)) {
				pq.push({dist[v], v});
			}
		}
	}
	dbg(dist);
	pqg<pii> q;
	bool good = 0;
	REP(k) {
		int x, y;
		cin >> x >> y;
		x--;
		{
			q.push({dist[x] - y, x}), yum[x] = dist[x] - y;
			if (y >= 2 * dist[x]) {
				good = 1;
			}
		}
	}
	if (good) {
		REP(n - 1) cout << 1 << "\n";
		return;
	}
	while (sz(q)) {
		auto [y, u] = q.top(); q.pop();
		if (y > yum[u]) continue;
		for (auto &[v, w] : g[u]) {
			if (ckmin(yum[v], yum[u] + w)) q.push({yum[v], v});
		}
	}
	F0R(i, n - 1) {
		dbg(yum[i]);
		cout << (yum[i] <= dist[i] ? 1 : 0) << "\n";
	}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    setIO("dining");
    while (testcase--)
    {
        solve();
    }
}