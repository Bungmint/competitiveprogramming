// Copyright © 2022 Youngmin Park. All rights reserved.
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
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

#define all(v) (v).begin(), (v).end()
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound

constexpr int INF = 1e9;
constexpr ll LINF = 1e18;
const ld PI = acos((ld)-1.0);
constexpr int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
constexpr bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
constexpr bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

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
template <typename T>
ostream &operator<<(ostream &os, const deque<T> &v) {
	os << vector<T>(all(v));
	return os;
}
template <typename T, typename S, typename C>
ostream &operator<<(ostream &os, priority_queue<T, S, C> pq) {
	vector<T> v;
	while (sz(pq)) {
		v.pb(pq.top());
		pq.pop();
	}
	os << v;
	return os;
}
void dbg_out()
{
	cerr << "\033[0m" << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
	cerr << ' ' << H;
	dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "\033[1;35m(" << #__VA_ARGS__ << "):\033[33m", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

inline namespace RecursiveLambda
{
	template <typename Fun>
	struct y_combinator_result
	{
		Fun fun_;
		template <typename T>
		explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}
		template <typename... Args>
		decltype(auto) operator()(Args &&...args)
		{
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun)
	{
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

inline namespace Range {
	class ForwardRange {
		int src, dst;

	  public:
	  	explicit constexpr ForwardRange(const int l, const int r) : src(l), dst(r) {}
		explicit constexpr ForwardRange(const int n) : src(0), dst(n) {}
		constexpr ForwardRange begin() const { return *this; }
		constexpr monostate end() const { return {}; }
		constexpr bool operator!=(monostate) const { return src < dst; }
		constexpr void operator++() const {}
		constexpr int operator*() { return src++; }
	};
	class BackwardRange {
		int src, dst;

	  public:
	  	explicit constexpr BackwardRange(const int l, const int r) : src(r), dst(l) {}
		explicit constexpr BackwardRange(const int n) : src(n), dst(0) {}
		constexpr BackwardRange begin() const { return *this; }
		constexpr monostate end() const { return {}; }
		constexpr bool operator!=(monostate) const { return src > dst; }
		constexpr void operator++() const {}
		constexpr int operator*() { return --src; }
	};
	using rep = ForwardRange;
	using per = BackwardRange;
};

int n, s, q, e;
constexpr int M = 1e5 + 100, K = 17;
string ESC = "escaped", IMP = "oo";
vpi adj[M];
pii edges[M];
int tin[M], tout[M], timer{};
ll dist[M];
ll dp[M], minDist[M];
int jmp[K][M];
ll jmpDP[K][M];
bitset<M> shop{};



void dfs(int u, int pu) {
	tin[u] = timer++;
	minDist[u] = (shop[u] ? dist[u] : LINF);
	for (auto &[v, w] : adj[u]) {
		if (v == pu) continue;
		dist[v] = dist[u] + w;
		jmp[0][v] = u;
		for (int j : rep(1, K)) {
			jmp[j][v] = jmp[j - 1][jmp[j - 1][v]];
		}
		dfs(v, u);
		if (minDist[v] < LINF) ckmin(minDist[u], minDist[v]);
	}
	dp[u] = (minDist[u] < LINF ? minDist[u] - 2 * dist[u] : LINF);
	tout[u] = timer - 1;
}
void calc(int u, int pu) {
	for (auto &[v, w] : adj[u]) {
		if (v == pu) continue; 
		jmpDP[0][v] = min(dp[v], dp[u]);
		for (int j : rep(1, K)) {
			jmpDP[j][v] = min(jmpDP[j - 1][v], jmpDP[j - 1][jmp[j - 1][v]]);
		}
		calc(v, u);
	}
}
ll query(int R, int root) {
	ll ret = dp[R];
	dbg(ret);
	int u = R;
	for (int i : per(K)) {
		int nxt = jmp[i][u];
		if (nxt && dist[nxt] >= dist[root]) {
			dbg(nxt, i, jmpDP[i][u]);
			ckmin(ret, jmpDP[i][u]);
			u = nxt;
		}
	}
	return (ret == LINF ? LINF : ret + dist[R]);
}

bool isAnc(int u, int v) {
	return tin[u] <= tin[v] && tout[v] <= tout[u];
}

void solve()
{
	cin >> n >> s >> q >> e;
	for (int i : rep(n - 1)) {
		int u, v, w;
		cin >> u >> v >> w; 
		adj[u].pb({v, w}), adj[v].pb({u, w});
		edges[i + 1] = {u, v};
	}
	for (int i : rep(s)) {
		int x;
		cin >> x;
		shop[x] = 1;
	}
	dfs(e, 0);
	calc(e, 0);
	for (int i : rep(q)) {
		int id, r;
		cin >> id >> r;
		auto [u, pu] = edges[id];
		if (dist[u] < dist[pu]) swap(u, pu);
		if (!isAnc(u, r)) {
			cout << ESC << '\n';
		}else{
			ll res = query(r, u);
			if (res == LINF) cout << IMP << '\n';
			else cout << res << '\n';
		}
	}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--)
	{
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}