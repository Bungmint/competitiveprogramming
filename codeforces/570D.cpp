// Problem: D. Tree Requests
// Contest: Codeforces - Codeforces Round #316 (Div. 2)
// URL: https://codeforces.com/contest/570/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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
const int N = 5e5;
int cnt[N][26], sub[N], depth[N];
bitset<N> ans{};
vi adj[N];
vpi query[N];
vi v[N];
string s;
void init(int u, int pu) {
	sub[u] = 1;
	for (auto &e : adj[u]) {
		if (e != pu) {
			depth[e] = depth[u] + 1;
			init(e, u);
			sub[u] += sub[e];
		}
	}
}
void dfs(int u, int pu, bool keep) {
	int mx = 0, big = -1;
	for (auto &e : adj[u]) {
		if (e == pu) continue;
		if (ckmax(mx, sub[e])) big = e;
	}
	for (auto &e : adj[u]) {
		if (e != pu && e != big) dfs(e, u, 0);
	}
	if (big != -1) {
		dfs(big, u, 1);
		v[u].swap(v[big]);
	}
	v[u].pb(u);
	cnt[depth[u]][s[u] - 'a']++;
	for (auto &e : adj[u]) {
		if (e == pu || e == big) continue;
		for (auto &vv : v[e]) {
			v[u].pb(vv);
			cnt[depth[vv]][s[vv] - 'a']++;
		}
		v[e].clear();
	}
	for (auto &[h, id] : query[u]) {
		ans[id] = (count_if(cnt[h], cnt[h] + 26, [&](int x) {
			return (x & 1);
		}) <= 1);
	}
	if (!keep) {
		for (auto &e : v[u]) {
			cnt[depth[e]][s[e] - 'a']--;
		}
	}
}

void solve()
{
	int n, m;
	cin >> n >> m;
	FOR(i, 1, n) {
		int p; cin >> p, --p;
		adj[i].pb(p), adj[p].pb(i);
	}
	cin >> s;
	F0R(i, m) {
		int vv, h;
		cin >> vv >> h;
		vv--, h--;
		query[vv].pb({h, i});
	}
	init(0, -1);
	dfs(0, -1, 0);
	F0R(i, m) cout << (ans[i] ? "Yes" : "No") << '\n';
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