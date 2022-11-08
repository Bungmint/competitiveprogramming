// Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

#pragma region TEMPLATE

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

#pragma endregion TEMPLATE

/**
 * Description: Randomized BBST
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/Treap%20(15.3).h
 * Verification:
 * Time complexity: O(log n) per split/merge
 */

const int MAXN = 3e5 + 10, MOD = 1e9 + 7;
int P[MAXN];

int add(int a, int b) { a += b; return (a >= MOD) ? a - MOD : a; }
int mul(int a, int b) { return 1LL*a*b%MOD; }

using pt = struct Treap*;
struct Treap {
    int pri; pt c[2]; // basics
	pii val, sum;
    int sz; 
    Treap(char _val) {
        pri = rng();
		sum = val = {_val - 'a', _val - 'a'};
        sz = 1;
        c[0] = c[1] = nullptr;
    }
    ~Treap() {
        for (int i = 0; i < 2; i++) delete c[i];
    }
};

// Just for myself: If you are going to change what the pointer is pointing, use pt&

int get_size(pt x) { return x ? x->sz : 0; }
pii get_sum(pt x) {return x ? x->sum : make_pair(0, 0); }
void calc(pt x) {
    pt a = x->c[0], b = x->c[1];
	int sza = get_size(a), szb = get_size(b);
    x->sz = 1 + sza + szb;
    auto [fl, bl] = get_sum(a);
	auto [fr, br] = get_sum(b);
	auto [frw, bck] = x->val;
	x->sum.fi = add(fl, add(mul(P[sza], frw), mul(P[sza + 1], fr)));
	x->sum.se = add(br, add(mul(P[szb], bck), mul(P[szb + 1], bl)));
}
pair<pt, pt> split_size(pt t, int v) { // size v goes to the left
    if (!t) return {t, t};
    if (get_size(t->c[0]) >= v) {
        auto [l, r] = split_size(t->c[0], v);
        t->c[0] = r;
        calc(t);
        return {l, t};
    }else{
        auto [l, r] = split_size(t->c[1], v - get_size(t->c[0]) - 1);
        t->c[1] = l;
        calc(t);
        return {t, r};
    }
}
pt merge(pt l, pt r) { // all keys in l < all keys in r
    if (!l || !r) return l ? l : r;
    pt t;
    if (l->pri > r->pri) {
        l->c[1] = merge(l->c[1], r);
        t = l;
        calc(t);
        return t;
    }else{
        r->c[0] = merge(l, r->c[0]);
        t = r;
        calc(t);
        return t;
    }
}
pt erase(pt t, int l, int r) {
	auto a = split_size(t, l - 1), b = split_size(a.se, r - l + 1);
	return merge(a.fi, b.se);
}
pt insert(pt t, int pos, char c) {
	auto p = split_size(t, pos - 1);
	return merge(p.fi, merge(new Treap(c), p.se));
}
bool query(pt &t, int l, int r) {
	auto a = split_size(t, l - 1), b = split_size(a.se, r - l + 1);
	bool ans = b.fi->sum.fi == b.fi->sum.se;
	t = merge(a.fi, merge(b.fi, b.se));
	return ans;
}

void precalc() {
	const int B = rng() % MOD;
	P[0] = 1;
	for (int i = 1; i < MAXN; i++) P[i] = mul(P[i - 1], B);
}

void solve() {
	precalc();
	int n, q;
	cin >> n >> q;
	pt root = nullptr;
	for (int i = 0; i < n; i++) {
		char c; cin >> c;
		root = merge(root, new Treap(c));
	}
	for (int i = 0; i < q; i++) {
		int t;
		cin >> t;
		dbg(i, root->sz);
		if (t == 1) {
			int l, r;
			cin >> l >> r;
			root = erase(root, l, r);
		}else if (t == 2) {
			int pos; char c;
			cin >> c >> pos;
			root = insert(root, pos, c);
		}else{
			int l, r;
			cin >> l >> r;
			cout << (query(root, l, r) ? "yes" : "no") << '\n';
		}
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
