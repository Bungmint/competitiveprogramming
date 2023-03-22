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
#define eb emplace_back
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
    void insert(ll x, int cnt = 1) {
        int now = 0; sz[now] += cnt;
        for (int j = MAXBIT-1; j >= 0; j--) {
            bool fl = x>>j & 1;
            if (!nxt[now][fl]) nxt[now][fl] = ++num;
            now = nxt[now][fl];
            sz[now] += cnt;
        }
    }
    ll query_xor_min(ll x) {
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
    ll query_xor_max(ll x) {
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

TrieBit<6'000'000, 30> t;

void solve() {
    int n;
    cin >> n;
    vi a(n);
    for (auto &e : a) cin >> e;
    auto rec = [&](int L, vi& x, auto&& rec) -> ll {
        if (sz(x) == 0) return 0;
        if (L == -1) return 0;
        dbg(L, x);
        ar<vi, 2> y;
        for (auto &e : x) y[e >> L & 1].pb(e);
        ll ans = rec(L - 1, y[0], rec) + rec(L - 1, y[1], rec);
        if (sz(y[0]) && sz(y[1])) {
            for (auto &e : y[0]) {
                t.insert(e, 1);
            }
            ll mi = 2 * INF;
            for (auto &e : y[1]) {
                ckmin(mi, t.query_xor_min(e));
            }
            ans += mi;
            for (auto &e : y[0]) {
                t.insert(e, -1);
            }
        }
        return ans;
    };
    cout << rec(29, a, rec) << '\n';
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

