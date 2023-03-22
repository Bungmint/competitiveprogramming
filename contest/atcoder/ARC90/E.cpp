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

constexpr int MOD = 1e9 + 7;

int add(int a, int b) {
    a += b;
    if (a >= MOD) {
        a -= MOD;
    }
    return a;
}
int sub(int a, int b) {
    a -= b;
    if (a < 0) {
        a += MOD;
    }
    return a;
}
int mul(int a, int b) {
    return 1LL * a * b % MOD;
}

void dijkstra(int st, vector<vpi> &g, vl& dist, vi& dp) {
    pqg<pair<ll, int>> pq;
    dist[st] = 0;
    dp[st] = 1;
    pq.push({dist[st], st});
    while (sz(pq)) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto &[v, w] : g[u]) {
            if (ckmin(dist[v], d + w)) {
                pq.push({dist[v], v});
                dp[v] = dp[u];
            } else if (dist[v] == d + w) {
                dp[v] = add(dp[v], dp[u]);
            }
        }
    }
}

void solve() {
    int N, M, S, T;
    cin >> N >> M >> S >> T;
    S--, T--;
    vector<vpi> original(N);
    vl dist_s(N, LINF), dist_t(N, LINF);
    vi dp_s(N), dp_t(N);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--; 
        original[u].pb({v, w}), original[v].pb({u, w});
    } 
    dijkstra(S, original, dist_s, dp_s);
    dijkstra(T, original, dist_t, dp_t);
    int ans = mul(dp_s[T], dp_s[T]);
    ll D = dist_s[T];
    for (int u = 0; u < N; u++) {
        if (dist_s[u] * 2 == D) {
            ans = sub(ans, mul(mul(dp_s[u], dp_s[u]), mul(dp_t[u], dp_t[u])));
        } else if (dist_s[u] * 2 < D) {
            for (auto &[v, w] : original[u]) {
                if (dist_t[v] * 2 < D && dist_s[u] + dist_t[v] + w == D) {
                    ans = sub(ans, mul(mul(dp_s[u], dp_s[u]), mul(dp_t[v], dp_t[v])));  
                }
            }
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

