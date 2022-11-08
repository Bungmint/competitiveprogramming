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

struct MaxBIT {
	vector<int> bit;
	int N;
	MaxBIT(int n) {
		N = n;
		bit.resize(N);
	}
	void upd(int i, int v) {
		for (i++; i <= N; i += i & -i) ckmax(bit[i - 1], v);
	}
	int query(int i) {
		int ans{};
		for (i++; i > 0; i -= i & -i) ckmax(ans, bit[i - 1]);
		return ans;
	}
};


void solve()
{
	int n;
	cin >> n;
	vi a(n + 1), ind(n + 1), t(n + 1);
	for (int i : rep(1, n + 1)) cin >> a[i];
	for (int i : rep(1, n + 1)) ind[a[i]] = i;
	stack<int> lo;
	MaxBIT bit(n + 1);
	vector<vi> hi(n + 1);
	vector<bool> isLow(n + 1), isHigh(n + 1);
	set<int> st;
	for (int i : rep(1, n + 1)) {
		t[i] = bit.query(ind[i]);
		bit.upd(ind[i], i);
		hi[t[i]].pb(i);
	}
	int ans{};
	for (int i : rep(n + 1)) {
		dbg(i);
		if (i == 0) {
			for (auto &e : hi[i]) isHigh[e] = 1, st.insert(ind[e]);
		}else{
			vi todo;
			while (sz(lo) && ind[lo.top()] > ind[i]) {
				int z = lo.top();
				int id = ind[z];
				if (auto it = st.lb(id); it != st.begin() && isHigh[a[*prev(it)]]) ans--;
				isLow[z] = 0;
				todo.pb(ind[z]);
				lo.pop();
			}
			while (sz(todo)) st.erase(st.find(todo.back())), todo.pop_back();
			lo.push(i);
			st.insert(ind[i]);
			isLow[i] = 1;
			isHigh[i] = 0;
			if (auto it = st.lb(ind[i]); it != st.begin() && isHigh[a[*prev(it)]]) ans++;
			for (auto &e : hi[i]) {
				isHigh[e] = 1;
				st.insert(ind[e]);
			}
			for (auto &e : hi[i]) {
				if (auto it = st.ub(ind[e]); it != st.end() && isLow[a[*it]]) ans++;
			}
		}
		dbg(st);
		cout << ans << '\n';
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
