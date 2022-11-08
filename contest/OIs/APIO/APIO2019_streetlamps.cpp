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

const int MX = 3e5;

struct BIT {
	vi ind;
	vl t;
	bool mode = 0;
	BIT() {}
	int atMost(int i) {
		return ub(all(ind), i) - ind.begin();
	}
	void upd(int i, int v) {
		if (!mode) {
			ind.pb(i);
			return;
		}
		int it = atMost(i);
		if (it == 0 || ind[it - 1] != i) it++;
		for (; it <= sz(ind); it += it & -it) {
			t[it - 1] += v;
		}
	}
	ll query(int i) {
		ll ret{};
		for (int it = atMost(i); it; it -= it & -it) {
			ret += t[it - 1];
		}
		return ret;
	}
	ll query(int l, int r) {
		return query(r) - query(l - 1);
	}
	void init() {
		mode = 1;
		sort(all(ind)), ind.resize(unique(all(ind)) - ind.begin());
		t.resize(sz(ind));
	}
}bit[MX];

int n, q;

void fakeUpd(int a, int b) {
	for (; a; a -= a & -a) {
		bit[a - 1].upd(b, 0);
		dbg(a, b);
	}
}
void init() {
	for (int i : rep(n)) bit[i].init();
}
void upd(int x, int y, int v) {
	for (; x <= n; x += x & -x) {
		dbg(x, y, v);
		dbg(bit[x - 1].ind);
		bit[x - 1].upd(y, v);
		dbg(x, bit[x - 1].t);
	}
}
void upd(int l, int i, int r, int v) {
	upd(l, i, v);
	upd(i + 1, i, -v);
	upd(l, r + 1, -v);
	upd(i + 1, r + 1, v);

}
int qq(int x, int y) {
	int ret = 0;
	for (; x; x -= x & -x) {
		ret += bit[x - 1].query(y);
		if (y == 3) dbg(x, y, bit[x - 1].ind);
	}
	return ret;
}



void solve()
{
	cin >> n >> q;
	string s;
	cin >> s;
	set<int> st; st.insert(0), st.insert(n + 1);
	for (int i : rep(n)) if (s[i] == '0') st.insert(i + 1);
	vector<pair<char, pii>> query(q);
	for (int i : rep(q)) {
		string t;
		cin >> t;
		if (t[0] == 'q') {
			int a, b;
			cin >> a >> b;
			b--;
			fakeUpd(a, b);
			query[i] = {t[0], {a, b}};
		}else{
			int j;
			cin >> j;
			query[i] = {t[0], {j, j}};
		}
	}
	init();
	for (int i : rep(q)) {
		auto &[t, p] = query[i];
		if (t == 'q') {
			int z = qq(p.fi, p.se) + (*st.lb(p.fi) > p.se ? i + 1 : 0);
			cout << z << '\n';
		}else{
			int L, R, v;
			auto j = p.fi;
			if (st.count(j)) {
				v = -(i + 1);
				auto it = st.lb(j);
				L = *prev(it) + 1;
				R = *next(it) - 1;
				st.erase(it);
			}else{
				v = (i + 1);
				auto it = st.insert(j).fi;
				L = *prev(it) + 1;
				R = *next(it) - 1;
			}
			upd(L, j, R, v);
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
