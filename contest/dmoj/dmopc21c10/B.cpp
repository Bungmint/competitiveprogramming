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


void solve()
{
	int n;
	cin >> n;
	vi a(n);
	for (auto &e : a) cin >> e;
	if (n == 1) {
		cout << 1 << '\n';
		return;
	}
	
	vi inv(n + 1);
	for (int i : rep(n)) {
		inv[a[i]] = i;
		a.pb(a[i]);
	}
	if (a[inv[1] + 1] == 2) {
		for (int j : rep(inv[1], inv[1] + n)) {
			if (a[j] != j - inv[1] + 1) {
				int it = inv[j - inv[1] + 1];
				if (it >= inv[1] && it < inv[1] + n) {
					swap(a[it], a[j]);
				}else{
					swap(a[j], a[it + n]);
				}
				break;
			}
		}
		for (int j : rep(inv[1], inv[1] + n)) {
			cout << a[j] << " \n"[j == inv[1] + n - 1];
		}
		return;
	}
	// 1, 2
	int t = inv[1];
	swap(a[t], a[(inv[2] > 0 ? inv[2] - 1 : n - 1)]);
	swap(a[t + n], a[(inv[2] > 0 ? inv[2] - 1 : n - 1) + n]);
	vi ret{};
	if (inv[2] == 0) {
		for (int j : rep(n - 1, n + n - 1)) {
			ret.pb(a[j]);
		}
	}else{
		for (int j : rep(inv[2] - 1, inv[2] - 1 + n)) ret.pb(a[j]);
	}
	vi res{};
	swap(a[t], a[(inv[2] > 0 ? inv[2] - 1 : n - 1)]);
	swap(a[t + n], a[(inv[2] > 0 ? inv[2] - 1 : n - 1) + n]);
	int z = inv[2];
	swap(a[z], a[(inv[1] == n - 1 ? 0 : inv[1] + 1)]);
	swap(a[z + n], a[(inv[1] == n - 1 ? 0 : inv[1] + 1) + n]);
	for (int j : rep(inv[1], inv[1] + n)) {
		res.pb(a[j]);
	}
	swap(a[z], a[(inv[1] == n - 1 ? 0 : inv[1] + 1)]);
	swap(a[z + n], a[(inv[1] == n - 1 ? 0 : inv[1] + 1) + n]);
	res = min(res, ret);
	if (a[inv[2] + 1] == 1) {
		swap(a[inv[2] + 1], a[inv[2]]);
		// swap(a[inv[2] + 1], a[inv[2]]);
		ret.clear();
		for (int i : rep(inv[2], inv[2] + n)) {
			ret.pb(a[i]);
		}
		dbg(ret);
		res = min(res, ret);
	}
	for (int j : rep(n)) {
		cout << res[j] << " \n"[j == n - 1];
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