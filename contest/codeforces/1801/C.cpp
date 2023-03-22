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
 * Description: Generic Iterative Segment Tree 
 * Source: 
        * https://codeforces.com/blog/entry/18051
        * Benq
 * Verification:
 * Time Complexity: O(n) build, O(log n) updates/queries
 */

template <typename T>
struct SegTree{
    const T ID = {}; 
    T comb(const T& a, const T& b) { return max(a, b); }
    vector<T> seg; int n;
    SegTree(int _n) {
        n = _n;
        seg.assign(2 * n, ID);
    }
    SegTree(const vector<T>& vec) : seg(sz(vec) * 2, ID), n(sz(vec)) {
        for (int i = 0; i < n; i++) seg[i + n] = vec[i];
        for (int i = n - 1; i; i--) pull(i);
    }
    void pull(int p) { seg[p] = comb(seg[2 * p], seg[2 * p + 1]); }
    void upd(int p, const T& val) {
        ckmax(seg[p += n], val);
        for (p /= 2; p; p /= 2) pull(p);
    }
    void build() { for (int i = n - 1; i; i--) pull(i); }
    T query(int l, int r) { // query interval: [l, r), must be associative
        T ra = ID, rb = ID;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2) ra = comb(ra, seg[l++]);
            if (r % 2) rb = comb(seg[--r], rb);
        }
        return comb(ra, rb);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<vi> b(n);
    vector<vi> hull(n);
    vi M(n);
    vi ind;
    auto get_ind = [&](int x) -> int {
        return lb(all(ind), x) - ind.begin();
    };
    for (int i = 0; i < n; i++) {
        map<int, int> freq;
        int k;
        cin >> k; b[i].resize(k);
        for (auto &e : b[i]) cin >> e, freq[e]++, ind.pb(e);
        for (int j = k - 1; j >= 0; j--) {
            if (freq[b[i][j]] == 1 && (*--freq.end()).fi == b[i][j]) {
                hull[i].pb(b[i][j]);
            }
            freq[b[i][j]]--;
            if (freq[b[i][j]] == 0) freq.erase(b[i][j]);
        }
        reverse(all(hull[i]));
    }
    sort(all(ind)), ind.resize(unique(all(ind)) - ind.begin());
    for (int i = 0; i < n; i++) {
        for (auto &e : b[i]) {
            e = get_ind(e);
            ckmax(M[i], e);
        }
        for (auto &e : hull[i]) e = get_ind(e);
    }
    dbg(hull);
    vi order(n);
    SegTree<int> dp(sz(ind));
    iota(all(order), 0);
    sort(all(order), [&](int i, int j) {
             return M[i] < M[j];
         });
    dbg(order);
    for (auto &id : order) {
        for (int i = 0; i < sz(hull[id]); i++) {
            dp.upd(M[id], dp.query(0, hull[id][i]) + sz(hull[id]) - i);
        }         
    }
    cout << dp.query(0, sz(ind)) << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

