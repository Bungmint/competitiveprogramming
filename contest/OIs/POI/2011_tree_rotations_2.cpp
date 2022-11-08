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
    int pri, val; pt c[2]; // basics
	int sz;
    Treap(int _val) {
        pri = rng(), val = _val;
		sz = 1;
        c[0] = c[1] = nullptr;
    }
    ~Treap() {
        for (int i = 0; i < 2; i++) delete c[i];
    }
};

// Just for myself: If you are going to change what the pointer is pointing, use pt&

int get_size(pt x) { return x ? x->sz : 0; }
void calc(pt x) {
    pt a = x->c[0], b = x->c[1];
	x->sz = 1 + get_size(a) + get_size(b);
}
pair<pt, pt> split(pt t, int v) { // <= v goes to the left
    if (!t) return {t, t};
    if (t->val > v) {
        auto [l, r] = split(t->c[0], v);
        t->c[0] = r;
        calc(t);
        return {l, t};
    }else{
        auto [l, r] = split(t->c[1], v);
        t->c[1] = l;
        calc(t);
        return {t, r};
    }
}
ll inv{};
pt unite(pt l, pt r) {
	if (!l || !r) return l ? l : r;
	dbg(l->sz, r->sz);
	if (l->pri < r->pri) {
		auto [lef, rig] = split(l, r->val);
		inv += 1LL*get_size(rig)*(get_size(r->c[0]) + 1);
		r->c[0] = unite(lef, r->c[0]);
		r->c[1] = unite(rig, r->c[1]);
		calc(r);
		dbg(r->sz);
		return r;
	}else{
		auto [lef, rig] = split(r, l->val);
		inv += 1LL*get_size(lef)*(get_size(l->c[1]) + 1);
		l->c[0] = unite(l->c[0], lef);
		l->c[1] = unite(l->c[1], rig);
		calc(l);
		dbg(l->sz);
		return l;
	}
}

void solve() {
	int N;
	cin >> N;
	int ti = N + 1;
	vector<pt> sts(2*N);
	vector<vi> chs(2*N);
	vl dp(2*N);
	stack<int> stck;
	for (int i = 0; i < 2*N - 1; i++) {
		int x;
		cin >> x;
		if (!x) {
			if (sz(stck)) chs[stck.top()].pb(ti);
			stck.push(ti);
			ti++;
		}else{
			if (sz(stck)) chs[stck.top()].pb(x);
			sts[x] = new Treap(x);
			dp[x] = 0;
		}
		while (sz(stck) && sz(chs[stck.top()]) == 2) {
			auto u = stck.top();
			inv = 0;
			int lef = get_size(sts[chs[u][0]]);
			int rig = get_size(sts[chs[u][1]]);
			sts[u] = unite(sts[chs[u][0]], sts[chs[u][1]]);
			dbg(lef, rig, sts[u]->sz);
			dp[u] = min(inv, 1LL*lef*rig - inv) + dp[chs[u][0]] + dp[chs[u][1]];
			stck.pop();
		}
	}
	cout << dp[N + 1] << '\n';
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
