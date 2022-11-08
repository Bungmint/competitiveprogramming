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

class Range {
	struct Iter
	{
		int iter;
		constexpr Iter(int it) noexcept : iter(it) {}
		constexpr void operator++() noexcept { iter++; }
		constexpr bool operator!=(const Iter &other) const noexcept { return iter != other.iter; }
		constexpr int operator*() const noexcept { return iter; }
	};
	const Iter first, last;

public:
	explicit constexpr Range(const int f, const int l) noexcept : first(f), last(max(f, l)) {}
	constexpr Iter begin() const noexcept { return first; }
	constexpr Iter end() const noexcept { return last; }
};

constexpr Range rep(const int l, const int r) noexcept { return Range(l, r); }
constexpr Range rep(const int n) noexcept { return Range(0, n); }

class ReversedRange {
    struct Iter {
        int itr;
        constexpr Iter(const int pos) noexcept : itr(pos) {}
        constexpr void operator++() noexcept { --itr; }
        constexpr bool operator!=(const Iter& other) const noexcept { return itr != other.itr; }
        constexpr int operator*() const noexcept { return itr; }
    };
    const Iter first, last;
 
  public:
    explicit constexpr ReversedRange(const int f, const int l) noexcept
        : first(l - 1), last(min(f, l) - 1) {}
    constexpr Iter begin() const noexcept { return first; }
    constexpr Iter end() const noexcept { return last; }
};
 
constexpr ReversedRange per(const int l, const int r) noexcept { return ReversedRange(l, r); }
constexpr ReversedRange per(const int n) noexcept { return ReversedRange(0, n); }

/**
 * Description: point update and rectangle sum with offline 2D BIT. 
	* For each of the points to be updated, $x\in (0,SZ)$ and $y\neq 0$.
 * Time: O(N\log^2 N)
 * Memory: O(N\log N)
 * Source: Benq
 * Verification: 
 	* https://dmoj.ca/problem/occ19g4
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=722 (753 ms)
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=601 (679 ms)
 */

template<class T, int SZ> struct BITOff2D { 
	bool mode = 0; // mode = 1 -> initialized
	vpi todo; // locations of updates to process
	int cnt[SZ], st[SZ];
	vi val; vector<T> bit; // store all BITs in single vector
	void init() { assert(!mode); mode = 1;
		int lst[SZ]; for (int i : rep(SZ)) lst[i] = cnt[i] = 0;
		sort(all(todo),[](const pii& a, const pii& b) { 
			return a.se < b.se; });
		for (auto &t : todo) for (int x = t.fi; x < SZ; x += x & -x) 
			if (lst[x] != t.se) lst[x] = t.se, cnt[x]++;
		int sum = 0; for (int i : rep(SZ)) lst[i] = 0, st[i] = (sum += cnt[i]);
		val.resize(sum); bit.resize(sum); reverse(all(todo));
		for (auto &t : todo) for (int x = t.fi; x < SZ; x += x & -x) 
			if (lst[x] != t.se) lst[x] = t.se, val[--st[x]] = t.se;
	}
	int rank(int y, int l, int r) {
		return ub(begin(val) + l, begin(val) + r, y) - begin(val) - l; }
	void UPD(int x, int y, T t) {
		for (y = rank(y, st[x], st[x] + cnt[x]); y <= cnt[x]; y += y & -y) 
			bit[st[x] + y - 1] += t; }
	void upd(int x, int y, T t) { 
		if (!mode) todo.pb({x, y});
		else for (; x < SZ; x += x & -x) UPD(x, y, t); }
	int QUERY(int x, int y) { T res = 0;
		for (y = rank(y, st[x], st[x] + cnt[x]); y; y -= y & -y) res += bit[st[x] + y - 1];
		return res; }
	T query(int x, int y) { assert(mode);
		T res = 0; for (; x; x -= x & -x) res += QUERY(x, y);
		return res; }
	T query(int xl, int xr, int yl, int yr) { 
		return query(xr, yr) - query(xl - 1, yr)
			- query(xr, yl - 1) + query(xl - 1, yl - 1); }
};

template <typename T>
struct BIT3D {
    vector<vector<vector<T>>> bit;
    int N, M, K;
    BIT3D(int n, int m, int k) : N(n), M(m), K(k) {
        bit.resize(n + 1);
        for (auto &v : bit) {
			v.resize(m + 1);
			for (auto &vv : v) vv.resize(k + 1);
		}
    }
    void upd(int x, int y, int z, T v) {
        for (x++; x <= N; x += x & -x) {
            for (int i = y + 1; i <= M; i += i & -i) {
				for (int j = z + 1; j <= K; j += j & -j) {
					bit[x][i][j] += v;
				}
            }
        }
    } 
    T query(int x, int y, int z) {
        T res = T();
        for (x++; x; x -= x & -x) {
            for (int i = y + 1; i; i -= i & -i) {
				for (int j = z + 1; j; j -= j & -j) {
					res += bit[x][i][j];
				}
            }
        }
        return res;
    }
	T query(int x1, int x2, int y1, int y2, int z1, int z2) {
		return query(x2, y2, z2) - query(x1 - 1, y2, z2) - query(x2, y1 - 1, z2) - query(x2, y2, z1 - 1) +
			query(x1 - 1, y1 - 1, z2) + query(x1 - 1, y2, z1 - 1) + query(x2, y1 - 1, z1 - 1) - 
			query(x1 - 1, y1 - 1, z1 - 1);
	}
};
#define ws aiojoiaj
vector<ar<int, 3>> a;
vi xs, ys, zs, ws;
int b, n, d, m;


ll solve1() {
	sort(all(a));
	ll res = 0;
	for (int i : rep(n)) {
		ar<int, 3> targ = a[i];
		targ[0] += d;
		int it = ub(all(a), targ) - a.begin();
		res += it - i - 1;
	}
	return res;
}
ll solve2() {
	constexpr int N = 75000;
	BITOff2D<int, 3 * N> bit;
	for (int i : rep(n)) {
		auto [x, y, _] = a[i];
		xs.pb(x + y), xs.pb(x + y + d), xs.pb(x + y - d);
	}
	sort(all(xs)), xs.resize(unique(all(xs)) - xs.begin());
	auto getX = [&](int x) -> int {
		return ub(all(xs), x) - xs.begin();
	};
	for (int i : rep(n)) {
		auto [x, y, _] = a[i];
		bit.upd(getX(x + y), x - y + d + N, 1);
		bit.upd(getX(x + y + d), x - y + d + d + N, 1);
		bit.upd(getX(x + y - d), x - y - d + d + N, 1);
	}
	bit.init();
	ll res = 0;
	for (int i : rep(n)) {
		auto [x, y, _] = a[i];
		bit.upd(getX(x + y), x - y + d + N, 1);
	}
	for (int i : rep(n)) {
		auto [x, y, _] = a[i];
		int x1 = (x + y - d), x2 = (x + y + d);
		int y1 = (x - y - d) + d + N, y2 = (x - y + d) + d + N;
		res += bit.query(getX(x1), getX(x2), y1, y2);
		res--;
	}
	return res / 2LL;
}
ll solve3() {
	vector<ar<int, 4>> b(n);
	for (int i : rep(n)) {
		auto [x, y, z] = a[i];
		int xx = x + y + z;
		int yy = x + y - z;
		int zz = x - y + z;
		int ww = x - y - z;
		b[i] = {xx, yy, zz, ww};
		ys.pb(yy);
		zs.pb(zz);
		ws.pb(ww);
	}
	sort(all(ws)), sort(all(ys)), sort(all(zs));
	ws.resize(unique(all(ws)) - ws.begin());
	ys.resize(unique(all(ys)) - ys.begin());
	zs.resize(unique(all(zs)) - zs.begin());
	sort(all(b));
	BIT3D<int> bit(sz(ys), sz(zs), sz(ws));
	ll res = 0;
	auto getWL = [&](int y) -> int { return lb(all(ws), y) - ws.begin(); };
	auto getWR = [&](int y) -> int { return ub(all(ws), y) - ws.begin() - 1; };
	auto getYL = [&](int y) -> int { return lb(all(ys), y) - ys.begin(); };
	auto getYR = [&](int y) -> int { return ub(all(ys), y) - ys.begin() - 1; };
	auto getZL = [&](int y) -> int { return lb(all(zs), y) - zs.begin(); };
	auto getZR = [&](int y) -> int { return ub(all(zs), y) - zs.begin() - 1; };
	int ptr = 0;
	for (int i : rep(n)) {
		auto [xx, yy, zz, ww] = b[i];
		bit.upd(getYL(yy), getZL(zz), getWL(ww), 1);
		while (ptr < n && b[ptr][0] < xx - d) {
			auto [x, y, z, w] = b[ptr];
			bit.upd(getYL(y), getZL(z), getWL(w), -1);
			ptr++;
		}
		res += bit.query(getYL(yy - d), getYR(yy + d), getZL(zz - d), getZR(zz + d), getWL(ww - d), getWR(ww + d)) - 1;
	}
	return res;
}

void solve()
{
	cin >> b >> n >> d >> m;
	a.resize(n);
	for (int i : rep(n)) for (int j : rep(b)) {
		cin >> a[i][j];
	}
	if (b == 1) cout << solve1() << '\n';
	else if (b == 2) cout << solve2() << '\n';
	else cout << solve3() << '\n';
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
