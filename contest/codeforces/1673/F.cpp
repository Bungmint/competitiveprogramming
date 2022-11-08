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


vector<vi> z = {{0, 1, 5, 4, 20, 21, 17, 16}, {2, 3, 7, 6, 22, 23, 19, 18}, {10, 11, 15, 14, 30, 31, 27, 26}, {8, 9, 13, 12, 28, 29, 25, 24}};


vector<vi> comb(vector<vi> &a, vector<vi> &b) {
	vector<vi> ret(4);
	for (int i : rep(4)) {
		for (int j : a[i]) {
			ret[i].pb(j);
		}
		for (int j : b[i]) {
			ret[i].pb(j);
		}
	}
	return ret;
}
void rev(vector<vi> &a) {
	for (int i : rep(4)) {
		reverse(all(a[i]));
	}
}
void flip(vector<vi> &a) {
	reverse(all(a));
}

vector<vi> grid() {
	vector<vi> ret;
	for (int i : rep(8)) {
		vector<vi> cur(4);
		for (int j : rep(4)) {
			vector<vi> t = z;
			for (auto &v : t) {
				for (auto &e : v) e ^= (32 * z[j][i]);
			}
			if (i & 1) flip(t);
			if (j & 1) rev(t);
			cur = comb(cur, t);
		}
		for (auto &v : cur) ret.pb(v);
	}
	return ret;
}


int n, k;
vector<vi> t = grid();
vpi inv(1024);

int read()	{
	int x;
	cin >> x;
	return x;
}
void answer(int i, int j) {
	cout << i << ' ' << j << endl;
}

void solve()
{
	cin >> n >> k;
	for (int i : rep(n)) {
		for (int j : rep(n)) {
			inv[t[i][j]] = {i, j};
		}
	}
	for (int i : rep(n)) {
		for (int j : rep(n - 1)) {
			cout << (t[i][j] ^ t[i][j + 1]) << ' ';
		}
		cout << endl;
	}
	for (int i : rep(n - 1)) {
		for (int j : rep(n )) {
			cout << (t[i][j] ^ t[i + 1][j]) << ' ';
		}
		cout << endl;
	}
	int cur = 0;
	for (int i : rep(k)) {
		int x = read();
		auto &p = inv[cur ^ x];
		answer(p.fi + 1, p.se + 1);
		cur ^= x;
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
