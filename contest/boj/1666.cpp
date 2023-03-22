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

struct SegTree {
    int N;
    vi t;
    SegTree(int n) {
        N = 1;
        while (N < n) N *= 2;
        t.resize(2 * N);
    }
    void upd(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            ckmax(t[x], v);
            return;
        }
        int mid = (lx + rx) / 2;
        if (i < mid) upd(i, v, 2 * x + 1, lx, mid);
        else upd(i, v, 2 * x + 2, mid, rx);
        t[x] = max(t[2 * x + 1], t[2 * x + 2]); 
    } 
    void upd(int i, int v) {
        upd(i, v, 0, 0, N);
    }
    int query(int l, int r, int x, int lx, int rx) {
        if (r <= lx || rx <= l) return 0;
        if (l <= lx && rx <= r) return t[x];
        int mid = (lx + rx) / 2;
        int a = query(l, r, 2 * x + 1, lx, mid);
        int b = query(l, r, 2 * x + 2, mid, rx);
        return max(a, b);
    }
    int query(int l, int r) {
        return query(l, r, 0, 0, N);
    }
};
SegTree seg(100'001);

void solve() {
    int N;
    cin >> N;
    vector<ar<int, 3>> a;
    vector<ar<int, 4>> xy(N);
    vi dp(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 4; j++) cin >> xy[i][j]; 
        a.pb({xy[i][0], -1, i});
        a.pb({xy[i][2], 1, i});
    }
    sort(all(a));
    int ans = 0;
    for (auto &[x, fl, id] : a) {
        if (fl == -1) {
            dp[id] = seg.query(0, xy[id][1]) + 1;
            ckmax(ans, dp[id]);
        } else {
            seg.upd(xy[id][3], dp[id]);
        }
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

