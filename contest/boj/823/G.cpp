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


struct TrieNode {
	int c[2], cnt;
	TrieNode() { c[0] = c[1] = cnt = 0; }
}node[10000000];

int ptr = 0;
int create_node() {
	return ++ptr;
}
void insert(int t, int x) {
	node[t].cnt++;
	for (int i = 23; i >= 0; i--) {
		int fl = x >> i & 1;
		if (!node[t].c[fl]) node[t].c[fl] = create_node();
		t = node[t].c[fl];
		node[t].cnt++;
	}
}
void erase(int t, int x) {
	node[t].cnt--;
	for (int i = 23; i >= 0; i--) {
		int fl = x >> i & 1;
		t = node[t].c[fl];
		node[t].cnt--;
	}
}
int query_max_xor(int t, int x) {
	for (int i = 23; i >= 0; i--) {
		int fl = !(x >> i & 1);
		if (!node[t].c[fl] || node[node[t].c[fl]].cnt == 0) {
			if (!fl) x ^= 1 << i;
			t = node[t].c[fl ^ 1];
		}else{
			if (fl) x ^= 1 << i;
			t = node[t].c[fl];
		}
	}
	return x;
}
int query_min_xor(int t, int x) {
	for (int i = 23; i >= 0; i--) {
		int fl = x >> i & 1;
		if (!node[t].c[fl] || node[node[t].c[fl]].cnt == 0) {
			if (!fl) x ^= 1 << i;
			t = node[t].c[fl ^ 1];
		}else{
			if (fl) x ^= 1 << i;
			t = node[t].c[fl];
		}
	}
	return x;
}

const int MAXN = 1e5 + 100, C = 1100;
int N, Q, a[MAXN];
ar<int, 4> q[51000];
set<int> in[MAXN*2];
vi ind;
int rts[C];

int get_ind(int x) { return lb(all(ind), x) - ind.begin(); }

void solve() {
	cin >> N;
	for (int i = 0; i <= (N - 1) / C; i++) {
		rts[i] = create_node();
	}
	for (int i = 0; i < N; i++) {
		cin >> a[i];
		insert(rts[i / C], a[i]);
		ind.pb(a[i]);
	}
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		auto& [t, l, r, x] = q[i];
		cin >> t;
		if (t == 1 || t == 2) cin >> l >> r >> x, l--, r--;
		else{
			cin >> l >> x; l--;
			r = l;
			ind.pb(x);
		}
	}
	sort(all(ind)), ind.erase(unique(all(ind)), ind.end());
	dbg(ind);
	for (int i = 0; i < N; i++) {
		a[i] = get_ind(a[i]);
		in[a[i]].insert(i);
	}
	for (int i = 0; i < Q; i++) {
		auto &[t, l, r, x] = q[i];
		if (t == 1) {
			int lt = l / C + 1;
			int rt = r / C - 1;
			int res = INF;
			for (int j = lt; j <= rt; j++) {
				int k = query_min_xor(rts[j], x);
				ckmin(res, k);
			}
			for (int j = l; j < min(r + 1, lt*C); j++) {
				ckmin(res, ind[a[j]] ^ x);
			}
			for (int j = max(l, (rt + 1)*C); j <= r; j++) {
				ckmin(res, ind[a[j]] ^ x);
			}
			dbg(res ^ x);
			auto it = in[get_ind(res ^ x)].lb(l);
			cout << *it + 1 << '\n';
		}else if (t == 2) {
			int lt = l / C + 1;
			int rt = r / C - 1;
			int res = -INF;
			for (int j = lt; j <= rt; j++) {
				int k = query_max_xor(rts[j], x);
				ckmax(res, k);
			}
			for (int j = l; j < min(r + 1, lt*C); j++) {
				ckmax(res, ind[a[j]] ^ x);
			}
			for (int j = max(l, (rt + 1)*C); j <= r; j++) {
				ckmax(res, ind[a[j]] ^ x);
			}
			auto it = in[get_ind(res ^ x)].lb(l);
			dbg(res ^ x);
			cout << *it + 1 << '\n';
		}else{
			erase(rts[l / C], ind[a[l]]);
			in[a[l]].erase(l);
			a[l] = get_ind(x);
			insert(rts[l / C], ind[a[l]]);
			in[a[l]].insert(l);
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
