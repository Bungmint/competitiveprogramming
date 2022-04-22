// Problem: Problem 3. Cow Navigation
// Contest: USACO - USACO 2017 January Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=695
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

const int N = 20;
int grid[N][N];
bool vis[N][N][4][N][N][4];
bool v[N][N][4];
int n;
const pii dr[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
vi ang = {-1, 1};

bool good(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < n && !grid[x][y];
}
int dist(int x, int y, int dir) {
	memset(v, 0, sizeof(v));
	queue<pair<ar<int, 3>, int>> q;
	v[x][y][dir] = 1;
	q.push({{x, y, dir}, 0});
	while (sz(q)) {
		auto [r, c, d] = q.front().fi;
		auto cnt = q.front().se;
		q.pop();
		if (r == 0 && c == n - 1) {
			return cnt;
		}
		for (auto &e : ang) {
			int nd = (d + 4 + e) % 4;
			if (!v[r][c][nd]) {
				v[r][c][nd] = 1;
				q.push({{r, c, nd}, cnt + 1});
			}
		}
		int nr = r + dr[d].fi, nc = c + dr[d].se;
		if (good(nr, nc)) r = nr, c = nc;
		if (!v[r][c][d]) {
			v[r][c][d] = 1;
			q.push({{r, c, d}, cnt + 1});
		}
	}
}

void solve()
{
	cin >> n;
	F0R(i, n) F0R(j, n) {
		char c;
		cin >> c;
		grid[i][j] = (c == 'H');
	}
	queue<pair<pair<ar<int, 3>, ar<int, 3>>, int>> q;
	q.push({{{n - 1, 0, 0}, {n - 1, 0, 1}}, 0});
	vis[n - 1][0][0][n - 1][0][1] = 1;
	int ans = INF;
	while (sz(q)) {
		auto [x, y, d] = q.front().fi.fi;
		auto [r, c, dd] = q.front().fi.se;
		auto cnt = q.front().se;
		q.pop();
		if (x == 0 && y == n - 1) {
			ckmin(ans, cnt + dist(r, c, dd));
			continue;
		}
		if (r == 0 && c == n - 1) {
			ckmin(ans, cnt + dist(x, y, d));
			continue;
		}
		// Turn
		for (auto e : ang) {
			int nd = (d + e + 4) % 4;
			int ndd = (dd + e + 4) % 4;
			if (!vis[x][y][nd][r][c][ndd]) {
				vis[x][y][nd][r][c][ndd] = 1;
				q.push({{{x, y, nd}, {r, c, ndd}}, cnt + 1});
			}
		}
		// forward
		int nx = x + dr[d].fi, ny = y + dr[d].se;
		int nr = r + dr[dd].fi, nc = c + dr[dd].se;
		if (good(nx, ny)) x = nx, y = ny;
		if (good(nr, nc)) r = nr, c = nc;
		if (!vis[x][y][d][r][c][dd]) {
			vis[x][y][d][r][c][dd] = 1;
			q.push({{{x, y, d}, {r, c, dd}}, cnt + 1});
		}
	}
	cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    setIO("cownav");
    while (testcase--)
    {
        solve();
    }
}