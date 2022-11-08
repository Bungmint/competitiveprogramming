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

// TODO: Test imp
/**
 * Description: Bit Trie supporting xor min and xor max queries
 * Source: Folklore, Benq
 * Verification: https://judge.yosupo.jp/problem/set_xor_min
 * Time complexity: O(MAXBIT) per insertion
 */

template <int SZ, int MAXBIT>
struct TrieBit {
    int nxt[SZ][2], sz[SZ], num = 0;
    TrieBit() { memset(nxt, 0, sizeof(nxt)), memset(sz, 0, sizeof(sz)); }
	int count(int x) {
		if (!sz[0]) return 0;
		int now = 0;
		for (int j = MAXBIT-1; j >= 0; j--) {
			bool fl = x>>j & 1;
			if (!nxt[now][fl] || !sz[nxt[now][fl]]) return 0;
			now = nxt[now][fl];
		}
		return sz[now];
	}
    void insert(int x, int cnt = 1) {
        int now = 0; sz[now] += cnt;
        for (int j = MAXBIT-1; j >= 0; j--) {
            bool fl = x>>j & 1;
            if (!nxt[now][fl]) nxt[now][fl] = ++num;
            now = nxt[now][fl];
            sz[now] += cnt;
        }
    }
	ll find_xor_min(ll x) {
        if (!sz[0]) return -1;
        int now = 0;
        for (int j = MAXBIT-1; j >= 0; j--) {
            bool fl = x>>j & 1;
            if (!nxt[now][fl] || !sz[nxt[now][fl]]) {
                if (!fl) x ^= 1<<j;
                fl ^= 1;
            }else if (fl) x ^= 1<<j;
            now = nxt[now][fl];
        }
        return x;
    }
    ll find_xor_max(ll x) {
        if (!sz[0]) return -1;
        int now = 0;
        for (int j = MAXBIT-1; j >= 0; j--) {
            bool fl = (x>>j & 1) ^ 1;
            if (!nxt[now][fl] || !sz[nxt[now][fl]]) fl ^= 1;
            if (fl) x ^= 1<<j;
            now = nxt[now][fl];
        }
        return x;
    }
};
TrieBit<30*500'000, 30> trie;

void solve() {
	int q; cin >> q;
	for (int i = 0; i < q; i++) {
		int t, x; cin >> t >> x;
		switch (t) {
		case 0:
			dbg(x, trie.count(x));
			if (!trie.count(x)) trie.insert(x);
			break;
		case 1: 
			dbg(x, trie.count(x));
			if (trie.count(x)) trie.insert(x, -1), dbg(x);
			break;
		case 2:
			cout << trie.find_xor_min(x) << '\n';
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
