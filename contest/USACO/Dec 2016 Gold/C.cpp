// Problem: Problem 3. Lasers and Mirrors
// Contest: USACO - USACO 2016 December Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=671
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

const int N = 4e5 + 10;
int n, stx, sty, enx, eny;
vi ind;
pii points[N];
int dist[N][2];
vi xToY[N], yToX[N];

void solve()
{
	F0R(i, N) dist[i][0] = dist[i][1] = INF;
	cin >> n >> stx >> sty >> enx >> eny;
	ind.pb(stx), ind.pb(sty), ind.pb(enx), ind.pb(eny);
	FOR(i, 1, 1 + n) {
		cin >> points[i].fi >> points[i].se;
		ind.pb(points[i].fi), ind.pb(points[i].se);
	}
	points[0] = {stx, sty};
	points[n + 1] = {enx, eny};
	sort(all(ind)), ind.resize(unique(all(ind)) - ind.begin());
	F0R(i, n + 2) {
		auto &[x, y] = points[i];
		x = lb(all(ind), x) - ind.begin();
		y = lb(all(ind), y) - ind.begin();
		xToY[x].pb(y);
		yToX[y].pb(x);
	}
	queue<pii> q;
	dist[points[0].fi][0] = dist[points[0].se][1] = 0;
	q.push({points[0].fi, 0});
	q.push({points[0].se, 1});
	while (!q.empty()) {
		auto [u, tt] = q.front();
		dbg(u, tt);
		q.pop();
		if (tt) {
			for (auto &v : yToX[u]) {
				if (ckmin(dist[v][0], dist[u][1] + 1)) {
					q.push({v, 0});
				}
			}
		}else{
			for (auto &v : xToY[u]) {
				if (ckmin(dist[v][1], dist[u][0] + 1)) {
					q.push({v, 1});
				}
			}
		}
	}
	int ans = min(dist[points[n + 1].fi][0], dist[points[n + 1].se][1]);
	cout << (ans == INF ? -1 : ans) << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    setIO("lasers");
    while (testcase--)
    {
        solve();
    }
}