// Problem: E. Fair Share
// Contest: Codeforces - Codeforces Round #770 (Div. 2)
// URL: https://codeforces.com/contest/1634/problem/E
// Memory Limit: 256 MB
// Time Limit: 1500 ms
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

template<int SZ, bool directed> struct Euler {
	int N; vpi adj[SZ]; vpi::iterator its[SZ];
	bool vis[SZ];
	vector<bool> used;
	vi comp;
	void add_edge(int a, int b) {
		dbg(a,b);
		int M = sz(used); used.pb(0); 
		adj[a].emplace_back(b,M); if (!directed) adj[b].emplace_back(a,M); }
	void dfs(int u) {
		vis[u] = 1;
		comp.pb(u);
		for (auto &[v, id] : adj[u]) if (!vis[v]) dfs(v);
	}
	vpi solve(int _N, int src = 0) {
		N = _N; F0R(i,N) its[comp[i]] = begin(adj[comp[i]]);
		vector<pair<pii,int>> ret, s = {{{src,-1},-1}}; 
		// {{vert, prev vert}, edge label}
		while (sz(s)) {
			dbg(ret, s);
			int x = s.back().fi.fi; auto& it = its[x], en = end(adj[x]);
			while (it != en && used[it->se]) it ++;
			if (it == en) { // no more edges out of vertex
				if (sz(ret) && ret.back().fi.se != x) return {}; 
				ret.pb(s.back()), s.pop_back(); 
			} else { s.pb({{it->fi,x},it->se}); used[it->se] = 1; }
		}
		F0R(i, N) if (its[comp[i]] != adj[comp[i]].end()) return {};
		vpi ans; 
		for (auto &t : ret) ans.pb(t.fi);
		reverse(all(ans)); return ans;
	}
	vpi solve_each(int _N) {
		int n = _N;
		vpi res;
		F0R(i, n) {
			if (vis[i]) continue;
			comp.clear();
			dfs(i);
			vpi z = solve(sz(comp), i);
			dbg(z, comp, i);
			if (z.empty() && sz(comp) > 1) return {};
			for (auto &e : z) res.pb(e);
		}
		return res;
	}
};

const int N = 5e5;
Euler<N, false> euler;

void solve()
{
	int n;
	cin >> n;
	vector<vi> a(n);
	vector<map<int, vi>> b(n);
	vector<map<int, int>> L(n);
	vi ind;
	for (auto &e : a) {
		int k;
		cin >> k;
		e.resize(k);
		for (auto &f : e) cin >> f, ind.pb(f);
	}
	sort(all(ind)), ind.resize(unique(all(ind)) - ind.begin());
	dbg(ind);
	F0R(i, n) {
		F0R(j, sz(a[i])) {
			auto &e = a[i][j];
			e = lb(all(ind), e) - ind.begin() + n;
			euler.add_edge(i, e);
			b[i][e].pb(j);
		}
	}
	vpi res = euler.solve_each(n + sz(ind));
	dbg(res);
	if (res.empty()) {
		cout << "NO\n";
		return;
	}
	dbg(res);
	for (auto &[l, r] : res) {
		if (r == -1) continue;
		if (l > r) {
			L[r][l]++;
		}
	}
	vector<vi> ans(n);
	F0R(i, n) {
		ans[i].resize(sz(a[i]));
		for (auto &[k, v] : b[i]) {
			int l = L[i][k];
			F0R(j, l) ans[i][v[j]] = 1;
		}
	}
	cout << "YES\n";
	for (auto &v : ans) {
		for (auto &e : v) cout << (e ? 'L' : 'R');
		cout << '\n';
	}
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