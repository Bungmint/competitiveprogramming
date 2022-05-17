// Problem: E. Purple Crayon
// Contest: Codeforces - Codeforces Global Round 18
// URL: https://codeforces.com/contest/1615/problem/E
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

// w * (r - b)
void solve()
{
	ll n, k;
	cin >> n >> k;
	vector<vi> adj(n);
	vector<bool> vis(n);
	vi subtree(n), big(n, -1);
	REP(n - 1) {
		int u, v;
		cin >> u >> v; u--, v--;
		adj[u].pb(v), adj[v].pb(u);
	}
	set<pii, greater<pii>> st;
	auto dfsInit = y_combinator([&](auto dfs, int u, int pu) -> void {
		subtree[u] = 1;
		int mx = 0;
		for (auto &e : adj[u]) {
			if (e == pu) continue;
			dfs(e, u);
			if (ckmax(mx, subtree[e])) big[u] = e;
			subtree[u] += subtree[e];
		}
		st.insert({subtree[u], u});
	});
	auto dfs = y_combinator([&](auto self, int u) -> void {
		vis[u] = 1;
		for (auto &e : adj[u]) if (!vis[e]) self(e);
	});
	dfsInit(0, -1);
	int cnt = 0;
	dbg(big);
	while (sz(st) && cnt < k) {
		while (sz(st) && vis[st.begin()->se]) st.erase(st.begin());
		if (!sz(st)) break;
		int root = st.begin()->se;
		vis[root] = 1;
		while (big[root] != -1) {
			root = big[root];
			vis[root] = 1;
		}
		cnt++;
	}
	if (st.empty()) {
		ll mi = (n + 1) / 2;
		if (n & 1) {
			if (cnt > mi || k < n / 2) {
				cout << max(k * (n - k), (n - cnt) * cnt) << '\n';
			}else {
				cout << mi * (n - mi) << '\n';
			}
		}else {
			if (cnt > mi || k < mi) {
				cout << max(k * (n - k), (n - cnt) * cnt) << '\n';
			}else {
				cout << mi * (n - mi) << '\n';
			}
		}
		return;
	}
	dbg(st);
	ll b = 0;
	while (sz(st)) {
		while (sz(st) && vis[st.begin()->se]) st.erase(st.begin());
		if (!sz(st)) break;
		auto [sb, root] = *st.begin();
		dfs(root);
		b += sb;
	}
	dbg(k, b);
	ll mi = n / 2;
	if (n & 1) {
		if (b >= (n - 1) / 2) {
			cout << k * (n - k) - mi * (n - mi) << '\n';
		}else cout << k * (n - k) - b * (n - b) << '\n';
	}else {
		if (b >= n / 2) {
			cout << k * (n - k) - mi * (n - mi) << '\n';
		}else cout << k * (n - k) - b * (n - b) << '\n';
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