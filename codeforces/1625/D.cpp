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


int n, k, msb;
const int N = 3e5 + 10;
int x[N];
int tree[N * 30][2], cnt[N * 60];
int root = 0;
int cur = 1;
vi ans;

void add(int x, int id)	{
	int now = root;
	for (int i : per(30)) {
		int fl = !!(x & (1 << i));
		if (!tree[now][fl]) {
			tree[now][fl] = cur++;
		}
		now = tree[now][fl];
		cnt[now] = id;
	}
}
void remove(int x) {
	int now = root;
	for (int i : per(30)) {
		int fl = !!(x & (1 << i));
		now = tree[now][fl];
		cnt[now] = -1;
	}
}
int go(int x) {
	int now = root;
	for (int i : per(30)) {
		int fl = !!(x & (1 << i));
		int nxt;
		if (tree[now][fl ^ 1] == 0 || cnt[tree[now][fl ^ 1]] == -1) {
			nxt = tree[now][fl];
		}else{
			nxt = tree[now][fl ^ 1];
		}
		now = nxt;
	}
	return cnt[now];
}

void dfs(vi &a, int level) {
	if (sz(a) == 0) return;
	vi on, off;
	for (auto &e : a) {
		if (x[e] & (1 << level)) on.pb(e);
		else off.pb(e);
	}
	if (level == msb) {
		bool good = 0;
		for (auto &e : on) add(x[e], e);
		for (auto &e : off) {
			int z = go(x[e]);
			if (z != -1 && (x[z] ^ x[e]) >= k) {
				ans.pb(z);
				ans.pb(e);
				good = 1;
				break;
			}
		}
		for (auto &E : on) remove(x[E]);
		if (!good) {
			if (sz(on)) ans.pb(on.front());
			else ans.pb(off.front());
		}
		return;
	}
	dfs(on, level - 1);
	dfs(off, level - 1);
}

void solve()
{
	memset(cnt, -1, sizeof(cnt));
	cin >> n >> k;
	for (int i : rep(n)) cin >> x[i];
	if (k == 0) {
		cout << n << '\n';
		for (auto i : rep(1, n + 1)) cout << i << ' ';
		cout << '\n';
		return;
	}
	msb = 31 - __builtin_clz(k);
	vi a(n); 
	iota(all(a), 0);
	dfs(a, 29);
	if (sz(ans) <= 1) {
		cout << -1 << '\n';
		return;
	}
	cout << sz(ans) << '\n';
	for (auto &e : ans) cout << e + 1 << ' ';
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
