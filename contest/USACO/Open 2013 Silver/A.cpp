// Problem: Problem 1. What's Up With Gravity
// Contest: USACO - USACO 2013 US Open, Silver
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=282
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

char grid[500][500];


void solve()
{
	int n, m;
	cin >> n >> m;
	int rh, ch, rd, cd;
	int dist[n][m][2]; // Forgive me god for this abomination
	F0R(i, n) F0R(j, m) F0R(k, 2) dist[i][j][k] = INF;
	F0R(i, n) F0R(j, m) {
		cin >> grid[i][j];
		if (grid[i][j] == 'C') rh = i, ch = j;
		if (grid[i][j] == 'D') rd = i, cd = j;
	}
	dist[rh][ch][0] = 0;
	queue<pair<pii, int>> q;
	q.push({{rh, ch}, 0});
	while (sz(q)) {
		auto [r, c] = q.front().fi;
		auto dir = q.front().se;
		q.pop();
		int d = dist[r][c][dir];
		if (dir) {
			while (!r || grid[r - 1][c] != '#') {
				r--;
				if (r < 0) break;
				ckmin(dist[r][c][dir], d);
			}
		}else{
			while (r == n - 1 || grid[r + 1][c] != '#') {
				r++;
				if (r == n) break;
				ckmin(dist[r][c][dir], d);
			}
		}
		if (r < 0 || r == n) continue;
		dbg(r, c, dir);
		if (ckmin(dist[r][c][dir], d)) {
			q.push({{r, c}, dir});
		}
		if (ckmin(dist[r][c][dir ^ 1], d + 1)) {
			q.push({{r, c}, (dir ^ 1)});
		}
		if (c + 1 < m && grid[r][c + 1] != '#' && ckmin(dist[r][c + 1][dir], d)) {
			q.push({{r, c + 1}, dir});
		}
		if (c && grid[r][c - 1] != '#' && ckmin(dist[r][c - 1][dir], d)) {
			q.push({{r, c - 1}, dir});
		}
	}
	int ans = min(dist[rd][cd][0], dist[rd][cd][1]);
	cout << (ans < INF ? ans : -1);
	
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    setIO("gravity");
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}