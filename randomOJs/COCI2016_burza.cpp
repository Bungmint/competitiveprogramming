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

int dp[1 << 20];
vi g[400];
int nxt[401][401];
int dep[401];
pii cov[401];
int n, k;
int cnt;

void dfs(int u, int pu, int dd) {
	dep[u] = dd;
	if (dd == k) {
		cov[cnt] = {cnt, cnt};
		if (dd) ckmax(nxt[dd - 1][cnt], cnt + 1);
		cnt++;
		return;
	}
	pii p = {cnt, cnt};
	for (auto &e : g[u]) {
		if (e != pu) {
			dfs(e, u, dd + 1);
		}
		p.se = cnt - 1;
	}
	cov[u] = p;
	if (dd) ckmax(nxt[dd - 1][p.fi], p.se + 1);
}

void solve()
{
	cin >> n >> k;
	if (k * k >= n) {
		cout << "DA" << "\n";
		return;
	}
	REP(n - 1) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].pb(v), g[v].pb(u);
	}
	fill(cov, cov + n, make_pair(0, -1));
	FOR(i, 1, n) {
		if (dep[i]) ckmax(nxt[dep[i] - 1][cov[i].fi], cov[i].se + 1);
	}
	dfs(0, -1, 0);
	F0R(i, k) FOR(j, 1, cnt + 1) {
		ckmax(nxt[i][j], nxt[i][j - 1]);
	}
	F0R(mask, (1 << k)) {
		F0R(j, k) {
			if (mask & (1 << j)) {
				dbg(mask, 1 << j, nxt[j][mask - (1 << j)]);
				ckmax(dp[mask], nxt[j][dp[mask - (1 << j)]]);
			}
		}
	}
	cout << (dp[(1 << k) - 1] == cnt ? "DA" : "NE");
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