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
    int n, k, x;
    cin >> n >> k >> x;
    int tmp = n % 4;
    int xum = 0;
    for (int i = 0; i <= tmp; i++) {
        xum ^= n + i - tmp;
    }
    if ((k & 1) && xum != x) {
        cout << "NO\n";
        return;
    }
    if (k % 2 == 0 && xum != 0) {
        cout << "NO\n";
        return;
    }
    vi vis(n + 1);
    vector<vi> ans;
    for (int i = 1; i <= n; i++) {
        if (i == x) {
            vis[i] = 1;
            ans.pb({i});
        } else if (!vis[i] && (i ^ x) <= n) {
            vis[i] = vis[i ^ x] = 1;
            ans.pb({i, i ^ x});
        }
    }
    vi rest;
    int xx = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            rest.pb(i); 
            xx ^= i;
        }
    }
    if (sz(rest)) {
        if (xx == x) {
            ans.pb(rest);
        } else {
            if (sz(ans) == 0) {
                cout << "NO\n";
                return;
            }
            for (auto &e : rest) ans.back().pb(e);
        }
    }
    if (sz(ans) < k) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for (int i = 0; i < k - 1; i++) {
        cout << sz(ans[i]);
        for (auto &e : ans[i]) cout << ' ' << e;
        cout << '\n';
    }
    vi rem;
    for (int i = k - 1; i < sz(ans); i++) {
        for (auto &e : ans[i]) rem.pb(e); 
    }
    cout << sz(rem);
    for (auto &e : rem) cout << ' ' << e;
    cout << '\n';
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

