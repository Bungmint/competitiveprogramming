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

int root = 0;
int ptr = 1;
int trie[32 * 200000][2], sum[32 * 200000];

void add(int x, int v) {
	int now = root;
	for (int i = 30; ~i; i--) {
		int fl = x >> i & 1;
		if (!trie[now][fl]) trie[now][fl] = ptr++;
		now = trie[now][fl];
		sum[now] ^= v;
	}
}
void remove(int x, int v) {
	int now = root;
	for (int i = 30; ~i; i--) {
		int fl = x >> i & 1;
		if (!trie[now][fl]) trie[now][fl] = ptr++;
		now = trie[now][fl];
		sum[now] ^= v;
	}
}
int query(int r, int x) {
	if (r == -1) return 0;
	int now = root;
	int ans{};
	for (int i = 30; ~i; i--) {
		if (ans) dbg(i, r, x, ans);
		int flr = r >> i & 1;
		int flx = x >> i & 1;
		int on = trie[now][1], off = trie[now][0];
		if (flr && flx) {
			if (on) ans ^= sum[on];
			if (!off) return ans;
			else now = off;
		}else if (flr) {
			if (off) ans ^= sum[off], dbg(sum[off]);
			if (!on) return ans;
			else now = on;
		}else if (flx) {
			if (!on) return ans;
			else now = on;
		}else {
			if (!off) return ans;
			else now = off;
		}
	}
	return ans ^ sum[now];
}


void solve() {
	int n;
	cin >> n;
	vi a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		add(i, a[i]);
	}
	int q; cin >> q;
	for (int i = 0; i < q; i++) {
		int t; cin >> t;
		if (t == 1) {
			int l, r, x;
			cin >> l >> r >> x;
			cout << (query(r, x) ^ query(l - 1, x)) << '\n';
		}else{
			int id, x;
			cin >> id >> x;
			add(id, x);
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
