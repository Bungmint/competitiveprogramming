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

int K, N, MM, O;
vpi adj[51'100], radj[51'000];
int A[11'000], B[11'000], ans[11'000];
int lef[51'000][5], rig[51'000][5];

void DnC(int L, int R, vi& query) {
	if (sz(query) == 0) return;
	if (L + 1 == R) {
		for (int &id : query) {
			ans[id] = (A[id] == B[id] ? 0 : -1);
		}
		return;
	}
	vi lefq, rigq;
	int M = (L + R) / 2;
	for (int i : rep(K)) {
		int cur = M * K + i;
		for (int j : rep(K)) {
			if (i == j) lef[cur][j] = rig[cur][j] = 0;
			else lef[cur][j] = rig[cur][j] = INF;
		}
	}
	for (int i : per(L, M)) {
		for (int j : rep(K)) {
			int cur = i * K + j;
			for (int jj : rep(K)) {
				lef[cur][jj] = INF;
				for (auto &[v, t] : adj[cur]) {
					ckmin(lef[cur][jj], t + lef[v][jj]);
				}	
			}
		}
	}
	for (int i : rep(M + 1, R)) {
		for (int j : rep(K)) {
			int cur = i * K + j;
			for (int jj : rep(K)) {
				rig[cur][jj] = (INF);
				for (auto &[v, t] : radj[cur]) {
					ckmin(rig[cur][jj], t + rig[v][jj]);
				}	
			}
		}
	}
	for (auto &id : query) {
		if (B[id] < K * M) lefq.pb(id);
		else if (A[id] >= M * K) rigq.pb(id);
		else{
			ans[id] = INF;
			dbg(L, R, id);
			for (int i : rep(K)) {
				ckmin(ans[id], lef[A[id]][i] + rig[B[id]][i]);
			}
			if (ans[id] == INF) ans[id] = -1;
		}
	}
	DnC(L, M, lefq), DnC(M, R, rigq);
}

void solve()
{
	cin >> K >> N >> MM >> O;
	vi query(O);
	for (int i : rep(MM)) {
		int a, b, t;
		cin >> a >> b >> t;
		adj[a].pb({b, t});
		radj[b].pb({a, t});
	}
	for (int i : rep(O)) cin >> A[i] >> B[i], query[i] = i;
	DnC(0, (N + K - 1) / K + 10, query);
	for (int i : rep(O)) cout << ans[i] << '\n';
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
