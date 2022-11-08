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

map<char, int> poke, suit;
using Card = pair<char, char>;
int ans = 0;

void init() {
	for (int j : rep(2, 10)) {
		poke[('0' + j)] = j;
	}
	poke['T'] = 10;
	poke['J'] = 11;
	poke['Q'] = 12;
	poke['K'] = 13;
	poke['A'] = 14;
	suit['H'] = 0, suit['D'] = 1, suit['C'] = 2, suit['S'] = 3;
}
pair<vi, vi> calc(vector<Card>& C, int& ret) {
	int res = 0;
	// check flushes
	bool same = 1;
	for (int i : rep(4)) {
		same &= C[i].se == C[i + 1].se;
	}
	vi t, s;
	for (int i : rep(5)) {
		t.pb(poke[C[i].fi]);
	}
	sort(all(t));
	bool consecutive = 1;
	for (int i : rep(4)) {
		consecutive &= (t[i] == t[i + 1] - 1);
	}
	if (consecutive) {
		if (ckmax(res, 4)) s = t;
	}
	if (same) {
		res = 5;
		s = t;
		if (consecutive) {
			res = 8;
			if (t.back() == 14) res = 9;
		}
	}
	map<int, int> freq;
	for (int i : rep(5)) {
		freq[poke[C[i].first]]++;
	}
	// 4 of a kind
	for (auto &[k, v] : freq) {
		if (v == 4) {
			if (ckmax(res, 7)) s = {k, k, k, k};
		}
		if (v == 3) {
			if (ckmax(res, 3)) s = {k, k, k};
		}
		if (v == 2) {
			if (ckmax(res, 1)) s = {k, k};
		}
	}
	map<int, int> freqfreq;
	for (auto &[k, v] : freq) {
		freqfreq[v]++;
	}
	if (freqfreq[2] == 2) {
		if (ckmax(res, 2)) {
			s.clear();
			for (auto &[k, v] : freq) {
				if (v == 2) {
					s.pb(k), s.pb(k);
				}
			}
		}
	}
	if (freqfreq[2] && freqfreq[3]) {
		if (ckmax(res, 6)) s = t;
	}
	ret = res;
	reverse(all(t));
	sort(all(s), greater<int>());
	return {t, s};
}

void solve()
{
	vector<Card> p1(5), p2(5);
	for (auto &e : p1) cin >> e.fi >> e.se;
	for (auto &e : p2) cin >> e.fi >> e.se;
	int t1, t2;
	auto [a, b] = calc(p1, t1); 
	auto [c, d] = calc(p2, t2);
	dbg(t1, t2);
	dbg(a, b, c, d);
	if (t1 > t2) {
		ans++;
	}else if (t1 == t2) {
		bool won{};
		if (b != d) {
			for (int i : rep(sz(b))) {
				if (b[i] > d[i]) {
					won = 1;
					break;
				}else if (b[i] < d[i]) break;
			}
		}else{
			for (int i : rep(5)) {
				if (a[i] > c[i]) {
					won = 1;
					break;
				}else if (a[i] < c[i]) break;
			}
		}
		if (won) ans++;
	}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1000;
	freopen("projectEuler/p054_poker.txt", "r", stdin);
	// cin >> testcase;
	init();
	while (testcase--)
	{
		solve();
	}
	cout << ans << "\n";
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
