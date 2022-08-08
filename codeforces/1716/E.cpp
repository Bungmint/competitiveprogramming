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

const int MAXN = 1 << 19;
int a[MAXN + 5], n, tot;
ll res[MAXN + 5];
vector<ar<ll, 4>> stor[MAXN + 5];

void pull() {
	for (int i = 0; i < n; i++) {
		for (int mask = 0; mask < tot; mask++) {
			if (mask>>i & 1) ckmax(res[mask], res[mask ^ (1 << i)]);
		}
	}
}
ar<ll, 4> merge(const ar<ll, 4>& aa, const ar<ll, 4>& bb)	{
	ar<ll, 4> sum{};
	sum[0] = max(aa[0], aa[3] + bb[0]);
	sum[1] = max(bb[1], bb[3] + aa[1]);
	sum[2] = max({aa[2], bb[2], aa[1] + bb[0]});
	sum[3] = aa[3] + bb[3];
	return sum;
}
void dfs(int x = 1, int L = n) {
	stor[x].resize(1 << L);
	if (L == 0) {
		dbg(x, a[x-tot]);
		if (a[x-tot] > 0) stor[x][0] = {a[x-tot], a[x-tot], a[x-tot], a[x-tot]}, ckmax(res[0], (ll)a[x-tot]);
		stor[x][0][3] = a[x-tot];
		return;
	}
	int lch = 2*x, rch = 2*x + 1;
	dfs(lch, L-1), dfs(rch, L-1);
	for (int mask = 0; mask < (1 << L); mask++) {
		if (mask>>(L-1) & 1) {
			int m = mask ^ (1<<(L-1));
			stor[x][mask] = merge(stor[rch][m], stor[lch][m]);
			ckmax(res[mask], stor[x][mask][2]);
		}else{
			stor[x][mask] = merge(stor[lch][mask], stor[rch][mask]);
			ckmax(res[mask], stor[x][mask][2]);
		}
	}
}

void solve() {
	cin >> n;
	tot = 1 << n;
	for (int i = 0; i < tot; i++) cin >> a[i];
	dfs();
	dbg(res[0]);
	// pull();
	int q; cin >> q;
	int mask = 0;
	for (int i = 0; i < q; i++) {
		int k; cin >> k;
		mask ^= 1 << k;
		cout << res[mask] << '\n';
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
