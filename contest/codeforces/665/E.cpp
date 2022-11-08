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
 * Description: Bit Trie supporting xor min and xor max queries
 * Source: Folklore, Benq
 * Verification: https://judge.yosupo.jp/problem/set_xor_min
 * Time complexity: O(MAXBIT) per insertion
 */

template <int SZ, int MAXBIT>
struct TrieBit {
    int nxt[SZ][2], sz[SZ], num = 0;
    TrieBit() { memset(nxt, 0, sizeof(nxt)), memset(sz, 0, sizeof(sz)); }
    void insert(ll x) {
        int now = 0; sz[now]++;
        for (int j = MAXBIT-1; j >= 0; j--) {
            bool fl = x>>j & 1;
            if (!nxt[now][fl]) nxt[now][fl] = ++num;
            now = nxt[now][fl];
            sz[now]++;
        }
    }
    int count_xor_at_least(ll x, ll k) {
		int now = 0; int res = 0;
		for (int j = MAXBIT-1; j >= 0; j--) {
			bool fl_x = x>>j & 1;
			bool fl_k = k>>j & 1;
			if (fl_k) {
				if (!nxt[now][fl_x^1]) return res;
				else now = nxt[now][fl_x^1];
			}else{
				if (nxt[now][fl_x^1]) res += sz[nxt[now][fl_x^1]];
				if (!nxt[now][fl_x]) return res;
				else now = nxt[now][fl_x];
			}
		}
		res += sz[now];
		return res;
	}
};
TrieBit<30*1'000'010, 30> trie;

void solve() {
	int n, k, x; cin >> n >> k;
	int xum{};
	ll ans{};
	trie.insert(0);
	for (int i = 0; i < n; i++) {
		cin >> x; xum ^= x;
		dbg(xum);
		dbg(trie.count_xor_at_least(xum, k));
		ans += trie.count_xor_at_least(xum, k);
		trie.insert(xum);
	}
	cout << ans << '\n';
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
