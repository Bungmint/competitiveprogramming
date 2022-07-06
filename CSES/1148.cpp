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


#define monostate int
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

/**
 * Description: Performs range prefix sum queries and point updates. lower_bound returns the first prefix sum >= v
 * Source: Own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=693
 * Time Complexity: O(log n) for query and update
 * 0-indexing
 */
template <typename T>
struct BIT
{
	int N;
	vector<T> bit;
	BIT(int n = 0)
	{
		bit.resize(n + 1);
		N = n;
	}
	void upd(int id, T v)
	{
		for (id++; id <= N; id += id & -id)
			bit[id] += v;
	}
	T query(int id)
	{
		T res = 0;
		for (id++; id > 0; id -= id & -id)
			res += bit[id];
		return res;
	}
	T query(int l, int r)
	{
		return l > r ? 0 : query(r) - query(l - 1);
	}
	T lower_bound(T v)
	{
		int id = 0;
		T sum = 0;
		int lg = 31 - __builtin_clz(N);
		for (int j = lg; ~j; j--)
		{
			if (id + (1 << j) <= N && sum + bit[id + (1 << j)] < v)
			{
				id += (1 << j);
				sum += bit[id];
			}
		}
		return id;
	}
};

struct AriBit {
	BIT<long long> C, Ci;
	int N;
	AriBit(int n) {
		N = n;
		C = BIT<long long>(N + 4);
		Ci = BIT<long long>(N + 4);
	}
	void add_ari(long long i, long long j, long long a, long long d) { // i - first, j - last
		if (i > j) return;
		C.upd(i, a); Ci.upd(i, a * i);
		C.upd(i + 1, d - a); Ci.upd(i + 1, (d - a) * (i + 1));
		C.upd(j + 1, -a - (j - i + 1) * d);
		Ci.upd(j + 1, (j + 1) * (a + (j - i + 1) * d) * -1);
		C.upd(j + 2, a + (j - i) * d);
		Ci.upd(j + 2, (a + (j - i) * d) * (j + 2));
	}
	vector<long long> to_vector() {
		vector<long long> ret(N + 1);
		for (int i : rep(0, N + 1)) {
			ret[i] = (i + 1) * C.query(i) - Ci.query(i);
		}
		return ret;
	}
};



void solve()
{
	int n, m;
	cin >> n >> m;
	vector<string> grid(n);
	for (int i : rep(n)) {
		cin >> grid[i];
	}
	vector<int> up(m), L(m), R(m);
	vector<vector<long long>> pref(n + 1, vector<long long>(m + 1));
	vector<vector<array<int, 4>>> upd(n + 1);
	
	for (int i : rep(n)) {
		stack<int> stL, stR;
		for (int j : rep(m)) {
			if (grid[i][j] == '*') up[j] = 0;
			else up[j]++;
			while (sz(stL) && up[stL.top()] >= up[j]) stL.pop();
			int lef = (sz(stL) ? stL.top() : -1);
			L[j] = j - lef - 1;
			stL.push(j);
		}
		for (int j : per(m)) {
			while (sz(stR) && up[stR.top()] > up[j]) stR.pop();
			int rig = (sz(stR) ? stR.top() : m);
			R[j] = rig - j - 1;
			stR.push(j);
		}
		for (int j : rep(m)) {
			int a = L[j], b = R[j];
			if (up[j] == 0) continue;
			if (a > b) swap(a, b);
			upd[up[j]].pb({1, a, 1, 1});
			upd[up[j]].pb({a + 1, b + 1, a + 1, 0});
			upd[up[j]].pb({b + 2, a + b + 1, a, -1});
		}
	}
	for (int i : rep(1, n + 1)) {
		AriBit bit(m);
		for (auto &[l, r, a, d] : upd[i]) {
			bit.add_ari(l, r, a, d);
		}
		vector<long long> v = bit.to_vector();
		swap(v, pref[i]);
	}


	for (int i : per(n + 1)) for (int j : per(m + 1)) {
		if (i < n) pref[i][j] += pref[i + 1][j];
	}
	for (int i : rep(1, n + 1)) for (int j : rep(1, m + 1)) cout << pref[i][j] << " \n" [j == m];
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
