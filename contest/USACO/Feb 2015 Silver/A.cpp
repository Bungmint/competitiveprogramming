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
// #define int long long
constexpr int MOD = 1e9 + 7;
ar<int, 2> B{9973, 10011};
ar<int, 2> inv{};

int binpow(int x, int k) {
	ll res = 1;
	while (k) {
		if (k & 1) res = (res * x) % MOD;
		x = (1LL * x * x) % MOD;
		k >>= 1LL;
	}
	return res;
}

ar<int, 2> add(ar<int, 2> A, char c) {
	for (int i : rep(2)) A[i] = ((1LL * A[i] * B[i]) % MOD + c - 'a' + 1) % MOD;
	return A;
}
ar<int, 2> sub(ar<int, 2> A, ar<int, 2> BB) {
	for (int i : rep(2)) {
		A[i] -= BB[i];
		if (A[i] < 0) A[i] += MOD;
	}
	return A;
}
ar<int, 2> mul(ar<int, 2> A, ar<int, 2> x) {
	for (int i : rep(2)) {
		A[i] = 1LL * A[i] * x[i] % MOD;
	}
	return A;
}

void solve()
{
	string s, t;
	cin >> s >> t;
	for (int i : rep(2)) {
		inv[i] = binpow(B[i], MOD - 2);
	}
	vector<ar<int, 2>> stk, powerB(sz(s) + 1);
	powerB[0] = {1, 1};
	for (int i : rep(1, sz(s) + 1)) {
		for (int j : rep(2)) {
			powerB[i][j] = 1LL * powerB[i - 1][j] * B[j] % MOD;
		}
	}
	vi ind;
	stk.pb({0, 0});
	ar<int, 2> hsh{};
	for (int i : rep(sz(t))) {
		hsh = add(hsh, t[i]);
	}
	dbg(hsh);
	for (int i : rep(sz(s))) {
		stk.pb(add(stk.back(), s[i]));
		ind.pb(i);
		// dbg(stk, ind);
		if (sz(stk) > sz(t)) {
			ar<int, 2> bk = stk[sz(stk) - 1], fr = stk[sz(stk) - sz(t) - 1];
			bk = sub(bk, mul(fr, powerB[sz(t)]));
			if (bk == hsh) {
				dbg();
				for (int j : rep(sz(t))) {
					ind.pop_back();
					stk.pop_back();
				}
			}
		}
	}
	for (auto &v : ind) {
		{
			cout << s[v];
		}
	}
	cout << '\n';
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	freopen("censor.in", "r", stdin);
	freopen("censor.out", "w", stdout);
	// cin >> testcase;
	while (testcase--)
	{
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
