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

int N, Q, SZ = 1;
int ans[1 << 20];

using ps = struct SegTree*;
struct SegTree {
	ps c[2];
	SegTree() {
		c[0] = c[1] = nullptr;
	}
	~SegTree() {
		for (int i = 0; i < 2; i++) delete c[i];
	}
};

SegTree *rts[100];

// inserts a node at index of the tree with the root rt
void insert(int ind, ps &seg, int l, int r) {
	if (!seg) seg = new SegTree();
	if (r - l == 1) {
		return;
	}
	int m = (l + r) / 2;
	if (ind < m) insert(ind, seg->c[0], l, m);
	else insert(ind, seg->c[1], m, r);
}
void insert(int ind, int rt) {
	insert(ind, rts[rt], 0, 1 << SZ);
}
void proper_merge(ps &from, ps &to, int l, int r) {
	if (!from) return;
	if (!to) {
		swap(from, to);
		return;
	}
	int m = (l + r) / 2;
	proper_merge(from->c[0], to->c[0], l, m);
	proper_merge(from->c[1], to->c[1], m, r);
	delete from;
	from = nullptr;
}
void merge(int lo, int hi, ps &from, ps &to, int l, int r) {
	if (!from) return;
	if (lo >= r || hi <= l) return;
	if (lo <= l && r <= hi) {
		proper_merge(from, to, l, r);
		return;
	}
	if (!to) to = new SegTree();
	int m = (l + r) / 2;
	merge(lo, hi, from->c[0], to->c[0], l, m);
	merge(lo, hi, from->c[1], to->c[1], m, r);
	if (from) {
		if (from->c[0] == nullptr && from->c[1] == nullptr) {
			delete from;
			from = nullptr;
		}
	}
	if (to->c[0] == nullptr && to->c[1] == nullptr) {
		delete to;
		to = nullptr;
	}
}
void merge(int from, int to, int l, int r) {
	if (from == to) return;
	merge(l, r, rts[from], rts[to], 0, 1 << SZ);
}
void dfs(int rt, ps seg, int l, int r) {
	if (!seg) return;
	if (r - l == 1) {
		ans[l] = rt;
		return;
	}
	int m = (l + r) / 2;
	dfs(rt, seg->c[0], l, m);
	dfs(rt, seg->c[1], m, r);
}
void recover() {
	for (int i = 0; i < 100; i++) {
		dfs(i, rts[i], 0, 1 << SZ);
	}
}



void solve() {
	cin >> N;
	while ((1 << SZ) < N) SZ++;
	for (int i = 0; i < N; i++) {
		int x;
		cin >> x; x--;
		dbg(i, x);
		insert(i, x);
	}
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		int from, to, l, r;
		cin >> l >> r >> from >> to;
		from--, to--, l--;
		merge(from, to, l, r);
	}
	recover();
	for (int i = 0; i < N; i++) cout << ans[i] + 1 << " \n"[i == N - 1];
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
