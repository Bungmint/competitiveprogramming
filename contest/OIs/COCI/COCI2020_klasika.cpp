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

// TODO: Test xor_max
/**
 * Description: Bit Trie supporting xor min and xor max queries
 * Source: Folklore, Benq
 * Verification: https://judge.yosupo.jp/problem/set_xor_min
 * Time complexity: O(MAXBIT) per insertion
 */

template <int SZ, int MAXBIT>
struct TrieBit {
    int nxt[SZ][2], num = 0;
	vi stck[SZ];
    TrieBit() { memset(nxt, 0, sizeof(nxt)); }
    void insert(ll x, int u) {
        int now = 0;
		stck[now].pb(sz(stck[now]) ? min(u, stck[now].back()) : u);
        for (int j = MAXBIT-1; j >= 0; j--) {
            bool fl = x>>j & 1;
            if (!nxt[now][fl]) nxt[now][fl] = ++num;
            now = nxt[now][fl];
			stck[now].pb(sz(stck[now]) ? min(u, stck[now].back()) : u);
        }
    }
	void erase(ll x) {
		int now = 0;
		stck[now].pop_back();;
        for (int j = MAXBIT-1; j >= 0; j--) {
            bool fl = x>>j & 1;
            if (!nxt[now][fl]) nxt[now][fl] = ++num;
            now = nxt[now][fl];
			stck[now].pop_back();
        }
	}
    ll query_xor_max(ll x, int time) {
        if (!sz(stck[0]) || stck[0].back() > time) return -1;
        int now = 0;
        for (int j = MAXBIT-1; j >= 0; j--) {
            bool fl = (x>>j & 1) ^ 1;
            if (!nxt[now][fl] || !sz(stck[nxt[now][fl]]) ||
			stck[nxt[now][fl]].back() > time) fl ^= 1;
            if (fl) x ^= 1<<j;
            now = nxt[now][fl];
        }
        return x;
    }
};
TrieBit<200010*30, 30> trie;

void solve() {
	int q; cin >> q;
	vector<vi> adj(1);
	vector<vector<ar<int, 3>>> queries(1);
	vpi ans;
	vi a(1);
	int num = 0;
	for (int i = 0; i < q; i++) {
		string s; cin >> s;
		if (s[0] == 'A') {
			int p, x; cin >> p >> x; p--;
			a.pb(x ^ a[p]);
			adj.pb({});
			num++;
			adj[p].pb(num);
			adj[num].pb(p);
			queries.pb({});
		}else{
			int u, v; cin >> u >> v;
			u--, v--;
			queries[v].pb({a[u], num, i});
		}
	}
	dbg(queries);
	vi s(num+1), tin(num+1), rev_tin(num+1);
	int ti{};
	auto init = y_combinator([&](auto self, int u = 0, int pu = -1) -> int {
		s[u] = 1;
		tin[u] = ti++;
		rev_tin[tin[u]] = u;
		for (auto &v : adj[u]) { 
			if (v == pu) continue;
			s[u] += self(v, u);
		}
		return s[u];
	});
	auto dfs = y_combinator([&](auto self, int u = 0, int pu = -1, bool big = 1) -> void {
		int big_ch = -1, mx = -1;
		for (auto &v : adj[u]) {
			if (v == pu) continue;
			if (ckmax(mx, s[v])) big_ch = v;
		}
		for (auto &v : adj[u]) {
			if (v != big_ch && v != pu)
				self(v, u, 0);
		}
		if (big_ch != -1) {
			self(big_ch, u, 1);
		}
		trie.insert(a[u], u);
		for (auto &v : adj[u]) {
			if (v == pu || v == big_ch) continue;
			for (int t = tin[v]; t < tin[v]+s[v]; t++) {
				trie.insert(a[rev_tin[t]], rev_tin[t]);
			}
		}
		dbg(u, queries[u]);
		for (auto &[aa, nn, id] : queries[u]) {
			ans.pb({id, trie.query_xor_max(aa, nn)});
		}
		if (!big) {
			for (int t = tin[u]; t < tin[u]+s[u]; t++) {
				trie.erase(a[rev_tin[t]]);
			}
		}
	});
	init();
	dfs();
	sort(all(ans));
	for (auto &[_, ret] : ans) cout << ret << '\n';
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
