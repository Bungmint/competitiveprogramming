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

void solve() {
    ll K, H, Q;
    cin >> K >> H >> Q;
    K++;
    ll mx = 1;
    for (int j = 1; j <= H; j++) mx *= K;
    mx--;
    for (int i = 0; i < Q; i++) {
        ll u, v;
        cin >> u >> v;
        vl pus, pvs;
        if (u > mx || v > mx) {
            cout << -1 << '\n';
            continue;
        }
        if (u == v) {
            cout << 0 << '\n';
            continue;
        }
        while (u % K == 0) {
            u /= K;
            pus.pb(-1);
        }
        while (sz(pus) < H) {
            pus.pb(u / K);
            u /= K;
        }
        while (v % K == 0) {
            v /= K;
            pvs.pb(-1);
        }
        while (sz(pvs) < H) {
            pvs.pb(v / K);
            v /= K;
        }
        reverse(all(pus)), reverse(all(pvs));
        dbg(pus, pvs);
        int id = 0;
        for (int j = 0; j < H; j++) {
            if (pus[j] < 0 || pvs[j] < 0) break;
            if (pus[j] != pvs[j]) break;
            id = j;
        }
        int j = id;
        int ans = 0;
        for (int k = H - 1; k >= j; k--) {
            if (pus[k] != -1) {ans += k - j + 1; break;}
        }
        for (int k = H - 1; k >= j; k--) {
            if (pvs[k] != -1) {ans += k - j + 1; break;}
        }
        cout << ans << '\n';
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

