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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
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


const int MN = 1e6;
const int MX = 2e5;
vpi adj[MX];
vi v[MX];
pair<int, ll> up[20][MX];
int sub[MX], depth[MX];
int targ;
int ans = INF;
ll shift = 0;
map<ll, int> cnt;
int extra = 0;
void init(int u, int pu) {
	sub[u] = 1;
	for (auto &[e, w] : adj[u]) {
		if (e == pu) continue;
		depth[e] = depth[u] + 1;
		up[0][e] = {u, w};
		FOR(i, 1, 20) {
			auto [nxt, d] = up[i - 1][e];
			up[i][e].fi = up[i - 1][nxt].fi;
			up[i][e].se = up[i - 1][nxt].se + d;
		}
		init(e, u);
		sub[u] += sub[e];
	}
}
ll dist(int u, int v) { // u is a descendant
	int d = depth[u] - depth[v];
	ll res = 0;
	R0F(i, 20) {
		if (d & (1 << i)) {
			res += up[i][u].se;
			u = up[i][u].fi;
		}
	}
	return res;
}
void dfs(int u, int pu, bool keep) {
	int mx = 0, big = -1;
	int dd = 0;
	for (auto &[e, w] : adj[u]) {
		if (e == pu) continue;
		if (ckmax(mx, sub[e])) big = e, dd = w;
	}
	for (auto &[e, w] : adj[u]) {
		if (e == pu || e == big) continue;
		dfs(e, u, 0);
	}
	if (big != -1) {
		dfs(big, u, 1);
		shift += dd;
		swap(v[u], v[big]);
		extra++;
	}
	v[u].pb(u);
	if (cnt.count(targ - shift)) ckmin(ans, cnt[targ - shift] + extra);
	ckmin(cnt[-shift], -extra);
	for (auto &[e, w] : adj[u]) {
		if (e == pu || e == big) continue;
		for (auto &x : v[e]) {
			v[u].pb(x);
			ll y = dist(x, u);
			if (cnt.count(targ - y - shift)) ckmin(ans, cnt[targ - y - shift] + depth[x] - depth[u] + extra);
		}
		for (auto &x : v[e]) {
			ll y = dist(x, u);
			if (cnt.count(y - shift)) ckmin(cnt[y - shift], -extra + depth[x] - depth[u]);
			else cnt[y - shift] = -extra + depth[x] - depth[u];
		}
		v[e].clear();
	}
	
	if (!keep) cnt.clear(), extra = shift = 0;
	
}
int best_path(int N, int K, int H[][2], int L[]) {
	targ = K;
	FOR(i, 0, N - 1) {
		auto u = H[i][0];
		auto vv = H[i][1];
		adj[u].pb({vv, L[i]});
		adj[vv].pb({u, L[i]});
	}
	init(0, -1);
	dfs(0, -1, 0);
	return (ans == INF ? -1 : ans);
}

// void solve()
// {
	// int n, k;
	// cin >> n >> k;
	// int h[n - 1][2];
	// int l[n - 1];
	// F0R(i, n - 1) cin >> h[i][0] >> h[i][1];
	// F0R(i, n - 1) cin >> l[i];
	// cout << best_path(n, k, h, l) << '\n';
// }
// 
// int main()
// {
    // cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    // int testcase=1;
    // // cin >> testcase;
    // while (testcase--)
    // {
        // solve();
    // }
// }