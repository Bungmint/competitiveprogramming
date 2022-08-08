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

/**
 * Description: Dynamic Segment Tree with no lazy propagation
 * Source: USACO Guide
 * Verification:
 * Time Complexity: O(log SZ) time & memory per query
 */
template <typename T, typename V = int, V SZ = 1 << 30> // change SZ accordingly
struct SparseSeg {
    T val = T(); 
    SparseSeg<T>* c[2];
    SparseSeg() { c[0] = c[1] = nullptr; }
	void push(int L, int R) {
		if (val.lazy == 0) return;
		val.sum = R - L;
		if (R - L > 1) {
			if (!c[0]) c[0] = new SparseSeg();
			if (!c[1]) c[1] = new SparseSeg();
			c[0]->val.lazy = 1;
			c[1]->val.lazy = 1;
		}
		val.lazy = 0;
	}
	void rangeUpd(V lo, V hi, V L = 0, V R = SZ) {
		push(L, R);
		if (lo >= R || hi <= L) return;
		if (lo <= L && R <= hi) {
			val.lazy = 1;
			push(L, R);
			return;
		}
		int M = (L + R) / 2;
		if (!c[0]) c[0] = new SparseSeg();
		if (!c[1]) c[1]	= new SparseSeg();
		c[0]->rangeUpd(lo, hi, L, M);
		c[1]->rangeUpd(lo, hi, M, R);
		val.sum = c[0]->val.sum + c[1]->val.sum;
	}
    void upd(V ind, T v, V L = 0, V R = SZ) {
        if (R - L == 1) {
            val = val + v;
            return;
        }
        V M = (L + R) / 2;
        if (ind < M) {
            if (!c[0]) c[0] = new SparseSeg();
            c[0]->upd(ind, v, L, M);
        }else{
            if (!c[1]) c[1] = new SparseSeg();
            c[1]->upd(ind, v, M, R);
        }
        val = T();
        for (int i : rep(2)) if (c[i]) val = val + c[i]->val;
    }
    T query(V lo, V hi, V L = 0, V R = SZ) {
		push(L, R);
        if (hi <= L || lo >= R) return T();
        if (lo <= L && R <= hi) return val;
        V M = (L + R) / 2;
        T res = T();
        if (c[0]) res = res + c[0]->query(lo, hi, L, M);
        if (c[1]) res = res + c[1]->query(lo, hi, M, R);
        return res;
    }
    void parallelUpd(V ind, SparseSeg* c0, SparseSeg* c1, V L = 0, V R = SZ) {
        if (R - L > 1) {
            V M = (L + R) / 2;
            if (ind < M) {
                if (!c[0]) c[0] = new SparseSeg();
                c[0]->parallelUpd(ind, c0 ? c0->c[0] : nullptr, c1 ? c1->c[0] : nullptr, L, M);
            }else{
                if (!c[1]) c[1] = new SparseSeg();
                c[1]->parallelUpd(ind, c0 ? c0->c[1] : nullptr, c1 ? c1->c[1] : nullptr, L, M);
            }
        }
        val = (c0 ? c0->val : T()) + (c1 ? c1->val : T());
    }
};

struct Node {
	int sum, lazy;
	Node(int sum_ = 0, int lazy_ = 0) : sum(sum_), lazy(lazy_) {}
	Node operator+(const Node& other) const {
		return {sum + other.sum, 0};
	}
};

void solve()
{
	int m;
	cin >> m;
	SparseSeg<Node> st;
	int c = 0;
	for (int i : rep(m)) {
		int d, x, y;
		cin >> d >> x >> y;
		x--, y--;
		if (d == 1) {
			c = st.query(x + c, y + c + 1).sum;
			cout << c << '\n';
		}else{
			st.rangeUpd(x + c, y + c + 1);
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
