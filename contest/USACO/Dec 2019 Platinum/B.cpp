// Problem: Problem 2. Bessie's Snow Cow
// Contest: USACO - USACO 2019 December Contest, Platinum
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=973
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

// Uses zero index for the input
template<typename T>
struct BIT{
	int N, lg;
	vector<T> bit;
	BIT(int n) { bit.resize(n+1); N = n; lg=log2(N);}
	void upd(int i, T v){ 
		for (++i; i <= N; i += i & -i) bit[i] += v;	
	}
	T query(int i){
		T res = 0;
		for (++i; i > 0; i -= i & -i) res += bit[i];
		return res;
	}
	T range_query(int l, int r) {
		return query(r) - query(l - 1);
	}
};

const int N = 1e5 + 100;
vi adj[N];
int tin[N], tout[N], timer;
set<pii> color[N];
BIT<ll> fen1(N), fen2(N);

void addRange(int l, int r, int x) {
	fen1.upd(l, x), fen1.upd(r + 1, -x);
	fen2.upd(l, 1LL * (l - 1) * x);
	fen2.upd(r + 1, 1LL * -r * x);
}

ll pref(int l) {
	return fen1.query(l) * l - fen2.query(l);
}

ll query(int l, int r) {
	return pref(r) - pref(l - 1);
}

void upd(int u, int col) {
	auto it = color[col].lb({tin[u], 0});
	if (it != color[col].begin()) {
		it--;
		if (it->fi <= tin[u] && it->se >= tout[u]) return;
	}
	while (true) {
		auto it = color[col].lb({tin[u], 0});
		if (it != color[col].end() && it->fi <= tout[u]) {
			auto [l, r] = *it;
			addRange(l, r, -1);
			it = color[col].erase(it);
		}else break;
	}
	addRange(tin[u], tout[u], 1);
	color[col].insert({tin[u], tout[u]});
}

ll ans(int u) {
	return query(tin[u], tout[u]);
}

void dfs(int u, int pu) {
	tin[u] = timer++;
	for (auto &e : adj[u]) if (e != pu)	dfs(e, u);
	tout[u] = timer - 1;
}


void solve()
{
	int n, q;
	cin >> n >> q;
	REP(n - 1) {
		int u, v;
		cin >> u >> v, u--, v--;
		adj[u].pb(v), adj[v].pb(u);
	}
	dfs(0, -1);
	REP(q) {
		int t;
		cin >> t;
		if (t == 1) {
			int x, c;
			cin >> x >> c;
			x--, c--;
			upd(x, c);
		}else{
			int x;
			cin >> x;
			x--;
			cout << ans(x) << "\n";
		}
	}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    setIO("snowcow");
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}