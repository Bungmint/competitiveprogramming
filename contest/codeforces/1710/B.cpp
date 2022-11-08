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
ll cdiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // divide a by b rounded down

#ifdef LOCAL
#include "miscellaneous/debug.h"
#else
#define dbg(...) 42
#endif

inline namespace RecursiveLambda {
	template <typename Fun>
	struct y_combinator_result {
		Fun fun_;
		template <typename T>
		explicit constexpr y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}
		template <typename... Args>
		constexpr decltype(auto) operator()(Args &&...args) const {
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun) {
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};




/**
 * Description: Generic Iterative Segment Tree 
 * Source: 
        * https://codeforces.com/blog/entry/18051
        * Benq
 * Verification:
 * Time Complexity: O(n) build, O(log n) updates/queries
 */

template <typename T>
struct SegTree{
    const T ID = {}; 
    T comb(const T& a, const T& b) { return a + b; }
    vector<T> seg; int n;
    SegTree(int _n) {
        n = _n;
        seg.assign(2 * n, ID);
    }
    SegTree(const vector<T>& vec) : seg(sz(vec) * 2, ID), n(sz(vec)) {
        for (int i = 0; i < n; i++) seg[i + n] = vec[i];
        for (int i = n - 1; i; i--) pull(i);
    }
    void pull(int p) { seg[p] = comb(seg[2 * p], seg[2 * p + 1]); }
    void upd(int p, const T& val) {
        seg[p += n] = val;
        for (p /= 2; p; p /= 2) pull(p);
    }
    void build() { for (int i = n - 1; i; i--) pull(i); }
    T query(int l, int r) { // query interval: [l, r), must be associative
        T ra = ID, rb = ID;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2) ra = comb(ra, seg[l++]);
            if (r % 2) rb = comb(seg[--r], rb);
        }
        return comb(ra, rb);
    }
};

/**
 * Observation: The global maxima occurs at peaks
 * Solution: RUPQ Minimum
 */

struct Max {
	ll x, pos, neg;
	Max(ll x_ = -LINF, ll pos_ = -LINF, ll neg_ = -LINF) : x(x_), pos(pos_), neg(neg_) {}
	Max operator+(const Max& other) const {
		return {max(x, other.x),
			    max(pos, other.pos),
				max(neg, other.neg)};
	}
};

void solve() {
	int n, m; cin >> n >> m;
	vpl rain(n); // x, p
	vi ind(n);
	vl coef(n + 1), ret(n + 1); 
	vector<Max> mx(n);
	iota(all(ind), 0);
	for (int i = 0; i < n; i++) {
		auto &[x, p] = rain[i];
		cin >> x >> p;
	}
	sort(all(ind), [&](int i, int j) {
		return rain[i] < rain[j];
	});
	sort(all(rain));
	for (int i = 0; i < n; i++) {
		auto [x, p] = rain[i];
		int lt = lb(all(rain), make_pair(x-p, -LINF)) - rain.begin();
		int rt = lb(all(rain), make_pair(x+p+1, -LINF)) - rain.begin() - 1;
		coef[lt]++; coef[i + 1]--; coef[i + 1]--; coef[rt + 1]++;
		ret[lt] += p - x; ret[i + 1] -= p - x;
		ret[i + 1] += p + x; ret[rt + 1] -= p + x;
	}
	for (int i = 1; i < n; i++) {
		ret[i] += ret[i - 1];
		coef[i] += coef[i - 1];
	}
	for (int i = 0; i < n; i++) {
		ret[i] += coef[i]*rain[i].fi;
		mx[i] = {ret[i], ret[i] + rain[i].fi, ret[i] - rain[i].fi};
	}
	dbg(ret);
	SegTree<Max> seg(mx);
	string ans(n, '0');
	for (int i = 0; i < n; i++) {
		auto [x, p] = rain[i];
		int lt = lb(all(rain), make_pair(x-p, -LINF)) - rain.begin();
		int rt = lb(all(rain), make_pair(x+p+1, -LINF)) - rain.begin() - 1;
		ll a = seg.query(0, lt).x, b = seg.query(rt+1, n).x;
		ll c = seg.query(lt, i+1).neg - (p-x), d = seg.query(i+1, rt+1).pos - (p+x);
		ll r = max({a, b, c, d});
		ans[ind[i]] = (r <= m) + '0';
	}
	cout << ans << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
