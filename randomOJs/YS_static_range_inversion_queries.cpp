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



constexpr int LOGN = 20;
constexpr int MAXN = 1 << LOGN;

ll hilbertorder(int x, int y)
{
	ll d = 0;
	for (int s = 1 << (LOGN - 1); s; s >>= 1)
	{
		bool rx = x & s, ry = y & s;
		d = d << 2 | ((rx * 3) ^ static_cast<int>(ry));
		if (!ry)
		{
			if (rx)
			{
				x = MAXN - x;
				y = MAXN - y;
			}
			swap(x, y);
		}
	}
	return d;
}

struct Query {
    int l, r, idx;
	ll ord;
	inline void calcOrder() {
		ord = hilbertorder(l, r);
	}
};
inline bool operator<(const Query &a, const Query &b) {
	return a.ord < b.ord;
}

using vq = vector<Query>;

constexpr int B = 320;
ll lazy[330][2], brute[111000][2], label[111000];
int n, q;
int SZ;

void init() {
	for (int i : rep(1, 100001)) {
		label[i] = (i) / B;
	}
	SZ = n / B;
}
void add(int a) {
	for (int i : per(SZ + 1)) {
		int R = (i + 1) * B - 1;
		int L = R - B + 1;
		if (L <= a) {
			for (int j : rep(a + 1, R + 1)) {
				brute[j][0]++;
			}
			break;
		}else{
			lazy[i][0]++;
		}
	}
	for (int i : rep(SZ + 1)) {
		int L = i * B, R = L + B - 1;
		if (a <= R) {
			for (int j : rep(L, a)) brute[j][1]++;
			return;
		}else{
			lazy[i][1]++;
		}
	}
}
ll calc(int a, int fl) {
	dbg(a, fl, brute[a][fl], lazy[label[a]][fl]);
	return brute[a][fl] + lazy[label[a]][fl];
}


void solve()
{
	cin >> n >> q;
	vi a(n + 1);
	vl ans(q), fans(q), ansPrev(n + 1), ansNow(n + 1);
	vector<vector<ar<int, 5>>> iv(n + 1);
	vi tmp;
	for (int i : rep(1, 1 + n)) cin >> a[i], tmp.pb(a[i]);
	sort(all(tmp)), tmp.resize(unique(all(tmp)) - tmp.begin());
	for (int i : rep(1, 1 + n)) a[i] = lb(all(tmp), a[i]) - tmp.begin();
	vq queries(q);
	for (int i : rep(q)) {
		auto &qq = queries[i];
		cin >> qq.l >> qq.r;
		qq.l++;
		qq.idx = i;
		qq.calcOrder();
	}
	sort(all(queries));
	int curL = 1, curR = 0;
	for (auto &qq : queries) {
		if (curR < qq.r) {
			iv[curL - 1].pb({curR + 1, qq.r, qq.idx, -1, 1});
			curR = qq.r;
		}
		if (curL > qq.l) {
			iv[curR].pb({qq.l, curL - 1, qq.idx, 1, 0});
			curL = qq.l;
		}
		if (curR > qq.r) {
			iv[curL - 1].pb({qq.r + 1, curR, qq.idx, 1, 1});
			curR = qq.r;
		}
		if (curL < qq.l) {
			iv[curR].pb({curL, qq.l - 1, qq.idx, -1, 0});
			curL = qq.l;
		}
	}
	init();
	for (int i : rep(1, n + 1)) {
		dbg(i, a[i]);
		ansPrev[i] = ansPrev[i - 1] + calc(a[i], 1);
		add(a[i]);
		for (auto &[l, r, id, sign, fl] : iv[i]) {
			ll z = 0;
			for (int j : rep(l, r + 1)) {
				z += calc(a[j], fl);
			}
			ans[id] += z * sign;
		}
		ansNow[i] = ansNow[i - 1] + calc(a[i], 0);
	}
	dbg(ansPrev, ansNow, ans);
	ll curans = 0;
	for (auto &qq : queries) {
		curans += ans[qq.idx];
		dbg(curans);
		fans[qq.idx] = curans + ansPrev[qq.r] + ansNow[qq.l - 1];
	}
	for (int i : rep(q)) {
		cout << fans[i] << '\n';
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
