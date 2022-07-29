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

constexpr int NAX = 1e5 + 100;
vpi adj[NAX];
ll dp[NAX];
ll V[NAX], S[NAX], n, dist, stck_max;

struct Line {
	ll m, b;
	ll operator()(ll x) const { return m*x + b; }
	friend ld intersect(const Line& l, const Line& r) {
		return -ld(l.b-r.b)/ld(l.m-r.m);
	}
}ch[NAX];

// returns the index in which l should be inserted
int insert_line(const Line& l) {
	if (stck_max < 2 || intersect(ch[stck_max-2], ch[stck_max-1]) < 
						intersect(ch[stck_max-2], l)) {
							return stck_max;
						}
	int lo = 1, hi = stck_max-1, ret = 1;
	while (lo <= hi) {
		int mid = (lo + hi)/2;
		
		if (intersect(ch[mid], ch[mid-1]) < intersect(ch[mid-1], l)) {
			ret = mid+1;
			lo = mid+1;
		}else{
			hi = mid-1;
		}
	}
	return ret;
}
ll get_min(int x) {
	int lo = 0, hi = stck_max-1, ret = 0;
	while (lo <= hi) {
		int mid = (lo + hi)/2;
		if (mid == stck_max-1) {
			ret = mid; break;
		}
		if (intersect(ch[mid], ch[mid+1]) < x) {
			lo = mid + 1;
		}else{
			ret = mid;
			hi = mid-1;
		}
	}
	return ch[ret](x);
}

void dfs(int u, int pu = -1) {
	int prev_max = stck_max;
	Line prev_l, l;
	int id;
	if (u == 0) {
		ch[0] = {0, 0};
		stck_max++;
	}else{
		dbg(u, stck_max, ch[0].m, ch[0].b, ch[1].m, ch[1].b);
		dbg(V[u], get_min(V[u]));
		dp[u] = get_min(V[u]) + S[u] + V[u]*dist;
		dbg(u);
		l = {-dist, dp[u]};
		id = insert_line(l);
		dbg(u);
		swap(prev_l, ch[id]);
		ch[id] = l;
		stck_max = id + 1;
	}
	for (auto &[v, d] : adj[u]) {
		if (v == pu) continue;
		dist += d;
		dfs(v, u);
		dist -= d;
	}
	if (u) {
		swap(ch[id], prev_l);
		stck_max = prev_max;
	}
}

void solve() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v, d; cin >> u >> v >> d;
		u--, v--;
		adj[u].pb({v, d}), adj[v].pb({u, d});
	}
	for (int i = 1; i < n; i++) cin >> S[i] >> V[i];
	dfs(0);
	for (int i = 1; i < n; i++) cout << dp[i] << " \n"[i == n - 1];
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
