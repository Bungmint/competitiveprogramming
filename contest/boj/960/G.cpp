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
    int n, k;
    cin >> n >> k;
    vi a(n);
    vi lef(n), rig(n);
    for (auto &e : a) cin >> e;
    for (int i = 0; i < n; i++) {
        lef[i] = rig[i] = 1;
        for (int j = i - 1; j >= 0; j--) {
            if (a[j] >= a[j + 1]) break;
            lef[i]++;
        }
        for (int j = i + 1; j < n; j++) {
            if (a[j] <= a[j - 1]) break;
            rig[i]++;
        }
    }
    int ans = max(*max_element(all(lef)), *max_element(all(rig)));
    for (int i = 0; i < n - k + 1; i++) {
        vi st;
        for (int j = 0; j < k; j++) {
            st.pb(a[i + j]);
        }
        sort(all(st)), st.resize(unique(all(st)) - st.begin());
        ckmax(ans, sz(st));
        if (sz(st) == k && (i == 0 || a[i - 1] < st[0]) && (i == n - k || a[i + k] > st[k - 1])) {
            int res = k;
            if (i) res += lef[i - 1];
            if (i < n - k) res += rig[i + k];
            ckmax(ans, res);
        }
        if (i) {
            int res = lef[i - 1];
            for (auto &e : st) {
                if (e > a[i - 1]) res++;
            }
            ckmax(ans, res);
        }
        if (i < n - k) {
            int res = rig[i + k];
            for (auto &e : st) {
                if (e < a[i + k]) res++;
            }
            ckmax(ans, res);
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

