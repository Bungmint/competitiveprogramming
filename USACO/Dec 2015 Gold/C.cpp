// Problem: Problem 3. Bessie's Dream
// Contest: USACO - USACO 2015 December Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=575
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

const int N = 1000;
int grid[N][N];
bool vis[N][N][2];
bool slide[N][N][4];


void solve()
{
	int n, m;
	cin >> n >> m;
	F0R(i, n) F0R(j, m) cin >> grid[i][j];
	queue<ar<int, 5>> q;
	q.push({0, 0, 0, 0, 0});
	while (sz(q)) {
		auto [r, c, dir, orang, d] = q.front();
		q.pop();
		if (r == n - 1 && c == m - 1) {
			cout << d << "\n";
			return;
		}
		if (grid[r][c] == 2) orang = 1;
		if (grid[r][c] == 4) {
			orang = 0;
			int nr = r + dx[dir], nc = c + dy[dir];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m || grid[nr][nc] == 3 || grid[nr][nc] == 0) {
				if (vis[r][c][orang]) continue;
				vis[r][c][orang] = 1;
				F0R(i, 4) {
					nr = r + dx[i], nc = c + dy[i];
					if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
					if (grid[nr][nc] == 0) continue;
					if (grid[nr][nc] == 3) continue;
					q.push({nr, nc, i, orang, d + 1});
				}
			}else{
				if (slide[r][c][dir]) continue;
				slide[r][c][dir] = 1;
				q.push({nr, nc, dir, orang, d + 1});
			}
		}else{
			if (vis[r][c][orang]) continue;
			vis[r][c][orang] = 1;
			F0R(i, 4) {
				int nr = r + dx[i], nc = c + dy[i];
				if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
				if (grid[nr][nc] == 0) continue;
				if (!orang && grid[nr][nc] == 3) continue;
				q.push({nr, nc, i, orang, d + 1});
			}
		}
	}
	cout << -1 << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    setIO("dream");
    while (testcase--)
    {
        solve();
    }
}