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

constexpr int MOD = 1e9 + 7;

inline int add(int a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
	return a;
}
inline int sub(int a, int b) {
	a -= b;
	if (a < 0) a += MOD;
	return a;
}
inline int mul(int a, int b) {
	return 1LL * a * b % MOD;
}


constexpr int MX = 5e4 + 100;
int lef[MX][20], rig[MX][20];
int cnt[20];
int ans[200000];
int A[200000], B[200000];
int a[MX];
int n, k;

void goLeft(int L, int M) {
	for (int i : rep(L, M)) for (int j : rep(k)) {
		lef[i][j] = 0; 
	}
	for (int i : per(k)) {
		for (int j : rep(i, k)) cnt[j] = 0;
		for (int j : per(L, M)) {
			if (a[j] == i) {
				cnt[i] = add(1, mul(2, cnt[i]));
				for (int x : rep(i + 1, k)) {
					cnt[x] = add(mul(2, cnt[x]), lef[j][x]);
				}
			}
			for (int x : rep(i, k)) {
				lef[j][x] = add(lef[j][x], cnt[x]);
			}
		}
	}
}
void goRight(int M, int R) {
	for (int i : rep(M, R)) for (int j : rep(k)) rig[i][j] = 0;
	for (int i : rep(k)) {
		for (int j : rep(i + 1)) cnt[j] = 0;
		for (int j : rep(M, R)) {
			if (a[j] == i) {
				cnt[i] = add(1, mul(2, cnt[i]));
				for (int x : rep(i)) {
					cnt[x] = add(mul(cnt[x], 2), rig[j][x]);
				}
			}
			for (int x : rep(i + 1)) {
				rig[j][x] = add(rig[j][x], cnt[x]);
			}
		}
	}
}

void DnC(int L, int R, vi& query) {
	if (sz(query) == 0) return;
	if (R - L == 1) {
		for (int i : query) {
			ans[i] = 2; 
		}
		return;
	}
	vi lefq, rigq;
	int M = (L + R) / 2;
	goLeft(L, M), goRight(M, R);
	for (int i : rep(M, R)) {
		for (int j : per(k - 1)) {
			rig[i][j] = add(rig[i][j], rig[i][j + 1]);
		}
	}
	for (auto &id : query) {
		if (A[id] >= M) rigq.pb(id);
		else if (B[id] < M) lefq.pb(id);
		else{
			int z = 1;
			// for (int i : per(k)) {
			// 	cnt[i] = rig[B[id]][i];
			// 	if (i + 1 < k) cnt[i] = add(cnt[i], rig[B[id]][i + 1]);
			// }
			for (int i : rep(k)) {
				// dbg(L, R, id, lef[A[id]][i], rig[B[id]][i]);
				z = add(z, mul(lef[A[id]][i], rig[B[id]][i]));
				z = add(z, lef[A[id]][i]);
			}
			z = add(z, rig[B[id]][0]);
			ans[id] = z;
		}
	}
	DnC(L, M, lefq), DnC(M, R, rigq);
}


void solve()
{
	cin >> n >> k;
	for (int i : rep(n)) cin >> a[i], a[i]--;
	int q;
	cin >> q;
	vi query(q);
	for (int i : rep(q)) {
		query[i] = i;
		cin >> A[i] >> B[i], A[i]--, B[i]--;
	}
	DnC(0, n, query);
	for (int i : rep(q)) cout << ans[i] << '\n';
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	#ifndef LOCAL
		freopen("nondec.in", "r", stdin);
		freopen("nondec.out", "w", stdout);
	#endif
	while (testcase--)
	{
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
