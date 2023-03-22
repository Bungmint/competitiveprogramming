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

set<set<pii>> tetr[4];
constexpr int dx[3] = {1, 0, 0}, dy[3] = {0, 1, -1};

void precalc() {
    tetr[0] = {{{0, 0}}}; 
    for (int s = 1; s < 4; s++) {
        for (auto &st : tetr[s - 1]) {
            for (auto &[r, c] : st) {
                for (int i = 0; i < 3; i++) {
                    int nr = r + dx[i], nc = c + dy[i]; 
                    set<pii> nxt = st;
                    if (!nxt.count({nr, nc})) {
                        nxt.insert({nr, nc});
                        tetr[s].insert(nxt);
                    }
                }
            }
        }
    }
}

void solve() {
    int n, m, ans = 0;
    cin >> n >> m;
    vector<vi> a(n, vi(m));
    for (auto &v : a) for (auto &e : v) cin >> e;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            for (auto &st : tetr[3]) {
                bool ok = 1;
                int sum = 0;
                for (auto &[dr, dc] : st) {
                    int nr = r + dr, nc = c + dc;
                    if (nr < 0 || nc < 0 || nr >= n || nc >= m) {
                        ok = 0;
                        break;
                    }
                    sum += a[nr][nc];
                }
                if (ok) ckmax(ans, sum);
            }
        }
    }
    cout << ans << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    precalc();
	int testcase = 1;
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

