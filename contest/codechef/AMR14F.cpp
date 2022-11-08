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

// inline namespace RecursiveLambda
// {
// 	template <typename Fun>
// 	struct y_combinator_result
// 	{
// 		Fun fun_;
// 		template <typename T>
// 		explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}
// 		template <typename... Args>
// 		decltype(auto) operator()(Args &&...args)
// 		{
// 			return fun_(ref(*this), forward<Args>(args)...);
// 		}
// 	};
// 	template <typename Fun>
// 	decltype(auto) y_combinator(Fun &&fun)
// 	{
// 		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
// 	}
// };

inline namespace Range {
	class ForwardRange {
		int src, dst;

	  public:
	  	constexpr ForwardRange() : src(-1), dst(-1) {}
	  	explicit constexpr ForwardRange(const int l, const int r) : src(l), dst(r) {}
		explicit constexpr ForwardRange(const int n) : src(0), dst(n) {}
		constexpr ForwardRange begin() const { return *this; }
		constexpr ForwardRange end() const { return {}; }
		constexpr bool operator!=(ForwardRange) const { return src < dst; }
		constexpr void operator++() const {}
		constexpr int operator*() { return src++; }
	};
	class BackwardRange {
		int src, dst;

	  public:
	  	constexpr BackwardRange() : src(-1), dst(-1) {}
	  	explicit constexpr BackwardRange(const int l, const int r) : src(r), dst(l) {}
		explicit constexpr BackwardRange(const int n) : src(n), dst(0) {}
		constexpr BackwardRange begin() const { return *this; }
		constexpr BackwardRange end() const { return {}; }
		constexpr bool operator!=(BackwardRange) const { return src > dst; }
		constexpr void operator++() const {}
		constexpr int operator*() { return --src; }
	};
	using rep = ForwardRange;
	using per = BackwardRange;
};

int cnt[1 << 16], tmp[1 << 16];
constexpr int MOD = 1'000'000'007;

inline void add(int &a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
}
inline void sub(int &a, int b) {
	a -= b;
	if (a < 0) a += MOD;
}

void solve()
{
	memset(cnt, 0, sizeof(cnt));
	memset(tmp, 0, sizeof(tmp));
	string s;
	cin >> s;
	int n = sz(s);
	vector<vi> pref(1 + n, vi(16));
	vi bit(n + 1);
	auto charToBit = [&](char ch) -> int {
		if (ch >= '0' && ch <= '9') return (ch - '0');
		else return (ch - 'A' + 10);
	};
	for (int i : rep(n)) {
		for (int j : rep(16)) pref[i + 1][j] = pref[i][j];
		int z = charToBit(s[i]);
		bit[i + 1] = 1 << z;
		if ('0' <= s[i] && s[i] <= '9') pref[i + 1][z]++;
		else pref[i + 1][z]++;
	}
	for (int l : rep(1, n + 1)) {
		int L = l, R = n, nxt = n + 1;
		int mask = bit[l];
		while (1) {
			R = n, nxt = n + 1;
			int cur = L;
			while (L <= R) {
				int M = (L + R) >> 1;
				bool ok = 0;
				for (int j : rep(16)) {
					if (mask >> j & 1) continue;
					if (pref[M][j] - pref[L - 1][j]) {
						ok = 1;
						break;
					}
				}
				if (ok) nxt = M, R = M - 1;
				else L = M + 1;
			}
			cnt[mask] += nxt - cur;
			cnt[mask] %= MOD;
			if (nxt == n + 1) {
				break;
			}else{
				L = nxt;
				mask |= bit[nxt];
			}
		}
	}
	for (int i : rep(1 << 16)) tmp[i] = cnt[i];
	for (int i : rep(16)) {
		for (int j : rep(1 << 16)) {
			if (!(j >> i & 1)) continue;
			tmp[j] += tmp[j ^ (1 << i)];
			tmp[j] %= MOD;
		}
	}
	ll t = 1LL * n * (n + 1) / 2LL;
	t %= MOD;
	for (int i : rep(1 << 16)) tmp[i] = (MOD + t - tmp[i]) % MOD;
	ll ans = 0;
	for (int i : rep(1 << 16)) {
		ans = (ans + 1LL * cnt[i] * tmp[i ^ ((1 << 16) - 1)]) % MOD;
	}
	cout << ans << '\n';

}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	while (testcase--)
	{
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
