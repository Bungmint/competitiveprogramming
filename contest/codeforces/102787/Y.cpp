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
 * Verification: https://codeforces.com/gym/102787
 * Time complexity: O(log n) per split/merge
 */

using pt = struct Treap*;
struct Treap {
    int pri; pt c[2]; // basics
    int sz; 
	int max, cnt[2]; // range
	pair<int, bool> max_pref, max_suf;
	bool val;
    bool reverse = 0, flip = 0; // lazy
	int is_set = -1;
    Treap(bool _val) {
        pri = rng(); 
		val = _val;
		max_pref = max_suf = {1, _val};
		cnt[_val] = max = sz = 1;
		cnt[_val ^ 1] = 0;
        c[0] = c[1] = nullptr;
    }
    ~Treap() {
        for (int i = 0; i < 2; i++) delete c[i];
    }
};

// Just for myself: If you are going to change what the pointer is pointing, use pt&

int get_size(pt x) { return x ? x->sz : 0; }
void prop(pt x) {
    if (!x || (!x->reverse && !x->flip && x->is_set == -1)) return;
	if (x->is_set != -1) {
		x->val = x->is_set;
		x->max_pref = x->max_suf = {x->sz, x->is_set};
		x->cnt[x->is_set] = x->max = x->sz;
		x->cnt[x->is_set ^ 1] = 0;
		for (int i = 0; i < 2; i++) if (x->c[i]) {
			x->c[i]->is_set = x->is_set;
			x->c[i]->flip = 0;
		}
		x->is_set = -1;
	}	
	if (x->reverse) {
		swap(x->c[0], x->c[1]);
		x->reverse = 0;
		swap(x->max_pref, x->max_suf);
		for (int i = 0; i < 2; i++) if (x->c[i]) x->c[i]->reverse ^= 1;
	}
	if (x->flip) {
		x->flip = 0;
		x->val ^= 1;
		x->max_pref.se ^= 1;
		x->max_suf.se ^= 1;
		swap(x->cnt[0], x->cnt[1]);
		for (int i = 0; i < 2; i++) if (x->c[i]) x->c[i]->flip ^= 1;
	}
}
void calc(pt x) {
    pt a = x->c[0], b = x->c[1];
    prop(a), prop(b);
    x->sz = 1 + get_size(a) + get_size(b);
	x->cnt[x->val] = 1;
	x->cnt[x->val ^ 1] = 0;
	for (int i = 0; i < 2; i++) {
		if (x->c[i]) {
			for (int j = 0; j < 2; j++) {
				x->cnt[j] += x->c[i]->cnt[j];
			}
		}
	}
    pair<int, bool> pref{}, suf{};
	int mx{1}, mid{1};
	if (x->c[0]) {
		pref = x->c[0]->max_pref;
		ckmax(mx, x->c[0]->max);
		if (x->c[0]->max_suf.se == x->val) mid += x->c[0]->max_suf.fi;
		if (pref.fi == x->c[0]->sz) {
			if (pref.se == x->val) {
				pref.fi++;
				if (x->c[1] && x->c[1]->max_pref.se == pref.se) {
					pref.fi += x->c[1]->max_pref.fi;
				}
			}
		}
	}
	else {
		pref = {1, x->val};
		if (pref.se == x->val) {
			if (x->c[1] && x->c[1]->max_pref.se == pref.se) {
				pref.fi += x->c[1]->max_pref.fi;
			}
		}
	}
	if (x->c[1]) {
		suf = x->c[1]->max_suf;
		ckmax(mx, x->c[1]->max);
		if (x->c[1]->max_pref.se == x->val) mid += x->c[1]->max_pref.fi;
		if (suf.fi == x->c[1]->sz) {
			if (suf.se == x->val) {
				suf.fi++;
				if (x->c[0] && x->c[0]->max_suf.se == suf.se) {
					suf.fi += x->c[0]->max_suf.fi;
				}
			}
		}
	}else {
		suf = {1, x->val};
		if (suf.se == x->val) {
			if (x->c[0] && x->c[0]->max_suf.se == suf.se) {
				suf.fi += x->c[0]->max_suf.fi;
			}
		}
	}
	x->max_pref = pref;
	x->max_suf = suf;
	x->max = max({mx, mid, pref.fi, suf.fi});
}
pair<pt, pt> split_size(pt t, int v) { // size v goes to the left
    if (!t) return {t, t};
    prop(t);
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
    prop(l), prop(r); 
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
void heapify(pt t) {
    if (!t) return;
    pt mx = t;
    for (int i = 0; i < 2; i++) {
        if (t->c[i] && t->c[i]->pri > mx->pri) mx = t->c[i];
    }
    if (mx != t) {
        swap(mx->pri, t->pri);
        heapify(mx);
    }
}
pt build(string& a, int l, int r) {
    if (r == l) return nullptr;
    int m = (l + r) / 2;
    pt t = new Treap(a[m] - '0');
    t->c[0] = build(a, l, m);
    t->c[1] = build(a, m + 1, r);
    heapify(t);
    calc(t);
    return t;
}
pt flip(pt t, int l, int r) {
	auto a = split_size(t, l - 1), b = split_size(a.se, r - l + 1);
	b.fi->flip ^= 1;
	return merge(a.fi, merge(b.fi, b.se));
}
pt reverse(pt t, int l, int r) {
	auto a = split_size(t, l - 1), b = split_size(a.se, r - l + 1);
	b.fi->reverse ^= 1;
	return merge(a.fi, merge(b.fi, b.se));
}
pt sort(pt t, int l, int r) {
	auto a = split_size(t, l - 1), b = split_size(a.se, r - l + 1);
	auto c = split_size(b.fi, b.fi->cnt[0]);
	if (c.fi) {
		c.fi->is_set = 0;
		c.fi->flip = 0;
	}
	if (c.se) {
		c.se->is_set = 1;
		c.se->flip = 0;
	}
	return merge(a.fi, merge(merge(c.fi, c.se), b.se));
}

void solve() {
	int n, q;
	cin >> n >> q;
	string s;
	cin >> s;
	pt root = build(s, 0, n);
	dbg(root->max);
	for (int i = 0; i < q; i++) {
		int t, l, r;
		cin >> t >> l >> r;
		if (t == 1) {
			root = flip(root, l, r);
		}else if (t == 2) {
			root = reverse(root, l, r);
		}else{
			root = sort(root, l, r);
		}
		cout << root->max << '\n';
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
