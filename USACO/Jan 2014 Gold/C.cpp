// Problem: Problem 3. Ski Course Rating
// Contest: USACO - USACO 2014 January Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=384
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

const int N = 500;
int grid[N][N];
int n, m, t;
ll ans{};


int conv(int r, int c) {
	return r * m + c;
}

inline namespace DSU {
	int par[N * N]{}, sz[N * N]{}, cnt[N * N]{};
	void init() {
		iota(par, par + n * m, 0);
		fill(sz, sz + n * m, 1);
	}
	int get(int a) {return a == par[a] ? a : par[a] = get(par[a]);}
	void unite(int a, int b, int w) {
		a = get(a), b = get(b);
		if (a == b) return;
		if (sz[a] < sz[b]) swap(a, b);
		par[b] = a;
		sz[a] += sz[b];
		cnt[a] += cnt[b];
		if (sz[a] >= t) {
			if (cnt[a]) {
				ans += 1LL * cnt[a] * w;
				cnt[a] = 0;
			}
		}
	}
};

struct Edge{
	int u, v, w;
	bool operator<(const Edge& other) const {
		return w < other.w;
	}
}edges[N * N * 4];


void solve()
{
	cin >> n >> m >> t;
	init();
	F0R(i, n) F0R(j, m) {
		cin >> grid[i][j];
	}
	int co = 0;
	F0R(i, n) F0R(j, m) {
		cin >> cnt[conv(i, j)];
		dbg(i * m + j);
		if (i) edges[co++] = {conv(i, j), conv(i - 1, j), abs(grid[i][j] - grid[i - 1][j])};
		if (j) edges[co++] = {conv(i, j), conv(i, j - 1), abs(grid[i][j] - grid[i][j - 1])};
	}
	sort(edges, edges + co);
	F0R(i, co) {
		auto [u, v, w] = edges[i];
		unite(u, v, w);
	}
	cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    setIO("skilevel");
    while (testcase--)
    {
        solve();
    }
}