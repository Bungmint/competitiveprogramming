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
template <typename T> // change SZ accordingly
struct SparseSeg {
    T val = T();
    SparseSeg<T>* c[2];
    SparseSeg() { c[0] = c[1] = nullptr; }
    using V = ll;
    static constexpr V SZ = 1LL << 40;
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
	bool queryq(V L = 0, V R = SZ) {
		bool lef = c[0] && c[0]->val.cnt;
		bool rig = c[1] && c[1]->val.cnt;
		if (!lef && !rig) return true;
		V sum = 0, last = 0;
		while (1) {
			V nxt = sum + 1;
			V cur = sum;
			T ret = query(last + 1, nxt + 1);
			sum += ret.sum;
			last = nxt;
			if (cur == sum) break;
		}
		return sum == val.sum;
	}
};

struct Node {
	ll sum;
	int cnt;
	Node(ll s = 0, int c = 0) : sum(s), cnt(c) {}
	Node operator+(const Node& o) const {
		return {sum + o.sum, cnt + o.cnt};
	}
};

SparseSeg<Node> seg;

bool init(int N, ll M, ll coins[]) {
	for (int i : rep(N)) {
		seg.upd(coins[i], {coins[i], 1});
	}
	return seg.queryq();
}
bool is_happy(int event, int K, ll coins[]) {
	for (int i : rep(K)) {
		seg.upd(coins[i], {coins[i] * event, event});
	}
	return seg.queryq();
}

// const int N = 1000;
// ll a[N];
// ll b[N];

// void solve()
// {
// 	int n, m;
// 	cin >> n >> m;
// 	for (int i : rep(n)) cin >> a[i];
// 	cout << init(n, m, a) << '\n';
// 	int q;
// 	cin >> q;
// 	for (int i : rep(q)) {
// 		int e;
// 		cin >> e;
// 		int k;
// 		cin >> k;
// 		for (int J : rep(k)) cin >> b[J];
// 		cout << is_happy(e, k, b) << '\n';
// 	}
// }

// int main()
// {
// 	cin.tie(0)->sync_with_stdio(0);
// 	cin.exceptions(cin.failbit);
// 	int testcase = 1;
// 	// cin >> testcase;
// 	while (testcase--)
// 	{
// 		solve();
// 	}
// #ifdef LOCAL
// 	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
// #endif
// }
