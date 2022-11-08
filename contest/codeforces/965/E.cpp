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
 * Description: Trie supporting string insertion
 * Source: Folklore, Benq
 * Verification: https://oj.uz/problem/view/IOI08_printer
 * Time complexity: O(|S_i|) per insertion
 */

template <int SZ, int ALPHA>
struct TrieAlpha {
    int nxt[SZ][ALPHA], num = 0;
	multiset<int> depths[SZ];
    TrieAlpha() { memset(nxt, 0, sizeof(nxt)); }
    void insert(const string& s) {
        int now = 0;
        for (int i = 0; i < sz(s); i++) {
            int c = s[i] - 'a';
            if (!nxt[now][c]) nxt[now][c] = ++num;
            now = nxt[now][c];
        }
		depths[now].insert(sz(s));
    }
	ll calc_total() {
		int root = 0;
		ll total = 0;
		for (int c = 0; c < ALPHA; c++) {
			if (nxt[root][c]) {
				dfs(nxt[root][c]);
				for (auto &d : depths[nxt[root][c]]) total += d;
			}
		}
		return total;
	}
	void dfs(int u, int cur_depth = 1) {
		bool is_empty = sz(depths[u]) == 0;
		depths[u] = {cur_depth};
		for (int c = 0; c < ALPHA; c++) {
			int v = nxt[u][c];
			if (v) {
				dfs(v, cur_depth+1);
				if (sz(depths[u]) < sz(depths[v])) swap(depths[u], depths[v]);
				for (auto &d : depths[v]) depths[u].insert(d);
				multiset<int>().swap(depths[v]);
			}
		}
		dbg(cur_depth, depths[u], is_empty);
		if (is_empty) depths[u].erase(--depths[u].end());
	}
};
TrieAlpha<100'100, 26> trie;

void solve() {
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		trie.insert(s);
	}
	cout << trie.calc_total() << '\n';
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
