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
	int u, v, p;
	cin >> u >> v >> p;
	vector<vi> t;
	vi pp{1, 2, 3};
	do{
		t.pb(pp);
	}while(next_permutation(all(pp)));
	uniform_int_distribution<> d(0, 5);
	auto mod_inv = [&](int a) -> int {
		int b = p - 2;
		int r = 1;
		while (b) {
			if (b & 1) r = (1LL * a * r) % p;
			a = (1LL * a * a) % p;
			b >>= 1LL;
		}
		return r;
	};
	map<int, vi> st, en;
	const int LIM = sqrt(p) * 8;
	auto generate100 = y_combinator([&](auto self, int cur, vi& a, map<int, vi>& mp) -> void {
		if (sz(mp) == LIM || sz(a) > 100) return;
		if (mp.count(cur)) return;
		mp[cur] = a;
		for (int i : t[d(rng)]) {
			if (i == 1) {
				cur++;
				if (cur == p) cur = 0;
				a.pb(i);
				self(cur, a, mp);
				a.pop_back();
				cur--;
				if (cur < 0) cur += p;
			}else if (i == 2) {
				cur--;
				if (cur < 0) cur += p;
				a.pb(i);
				self(cur, a, mp);
				a.pop_back();
				cur++;
				if (cur == p) cur = 0;
			}else{
				int inv = mod_inv(cur);
				swap(inv, cur);
				a.pb(i);
				self(cur, a, mp);
				a.pop_back();
				swap(inv, cur);
			}
		}
	});
	vi tt;
	generate100(u, tt, st);
	generate100(v, tt, en);
	for (auto &[k, vv] : st) {
		if (en.count(k)) {
			dbg(k, vv, en[k]);
			cout << sz(vv) + sz(en[k]) << '\n';
			for (auto &e : vv) cout << e << ' ';
			reverse(all(en[k]));
			for (auto &e : en[k]) {
				if (e == 1) cout << 2 << ' ';
				else if (e == 2) cout << 1 << ' ';
				else cout << e << ' ';
			}
			cout << '\n';
			return;
		}
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
