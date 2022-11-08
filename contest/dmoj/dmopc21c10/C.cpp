// Copyright © 2022 Youngmin Park. All rights reserved.
#pragma GCC optimize("O3")
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
#define dbg(...) cerr << "\033[1;35m" << __func__ << ':' << __LINE__ << " (" << #__VA_ARGS__ << "):\033[33m", dbg_out(__VA_ARGS__)
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

constexpr int dx[4] = {1, 1, -1, -1}, dy[4] = {-1, 1, 1, -1};
constexpr char X = '\\', Y = '/';

// Hypothesis - O(4 * n * m) 

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<string> grid(n);
	for (auto &s : grid) cin >> s;
	if (n == 1) {
		if (m != 2) {
			cout << -1 << '\n';
		}else{
			cout << (grid[0][0] == Y) + (grid[0][1] == Y) << '\n';
		}
		return;
	}
	if (m == 1) {
		cout << -1 << '\n';
		return;
	}
	if (((n & 1) && (m & 1)) || (n % 2 == 0 && m % 2 == 0)) {
		cout << -1 << '\n';
		return;
	}
	int ans = (grid[0][0] == Y) + (grid[n - 1][m - 1] == Y);
	int dist[2][n][m]; // 0 - from left, 1 - from right
	for (int i : rep(2)) for (int j : rep(n)) for (int k : rep(m)) dist[i][j][k] = INF;
	dist[0][0][1] = 0;
	pqg<pair<int, ar<int, 3>>> q;
	q.push({0, {0, 0, 1}});
	while (sz(q)) {
		auto [d, p] = q.top();
		q.pop();
		auto [dir, x, y] = p;
		if (d > dist[dir][x][y]) continue;
		for (auto i : rep(4)) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
			int ext{};
			if (dir == 0) {
				if (i < 2) {
					ext += grid[x][y] != X;
				}else {
					ext += grid[x][y] != Y;
				}
				if (i == 0) ext += grid[x + 1][y] != Y;
				if (i == 1) ext += grid[x + 1][y] != X;
				if (i == 2) ext += grid[x - 1][y] != Y;
				if (i == 3) ext += grid[x - 1][y] != X;
				if (i == 1 || i == 2) {
					if (ckmin(dist[dir][nx][ny], ext + d)) {
						q.push({ext + d, {dir, nx, ny}});
					}
				}else{
					if (ckmin(dist[1 - dir][nx][ny], ext + d)) {
						q.push({ext + d, {1 - dir, nx, ny}});
					}
				}
			}else{
				if (i < 2) {
					ext += grid[x][y] != Y;
				}else {
					ext += grid[x][y] != X;
				}
				if (i == 0) ext += grid[x + 1][y] != Y;
				if (i == 1) ext += grid[x + 1][y] != X;
				if (i == 2) ext += grid[x - 1][y] != Y;
				if (i == 3) ext += grid[x - 1][y] != X;
				if (i == 0 || i == 3) {
					if (ckmin(dist[dir][nx][ny], ext + d)) {
						q.push({ext + d, {dir, nx, ny}});
					}
				}else{
					if (ckmin(dist[1 - dir][nx][ny], ext + d)) {
						q.push({ext + d, {1 - dir, nx, ny}});
					}
				}
			}
		}
	}


	cout << dist[0][n - 1][m - 1] + ans << '\n';
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
