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


bool is_better(pll d1, pll d2, pll d3) {
    return (d1.first - d3.first)*(d2.second - d1.second)
            >= (d3.second - d1.second)*(d1.first - d2.first);
}
ll y_val(pll l, ll x) {
    return l.first*x + l.second;
}


void solve() {
    int n, m, K;
    cin >> n >> m >> K;
    vector<vl> dp(K + 1, vl(n, LINF));    
    vector<vpl> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].pb({v, w});
        g[v].pb({u, w});
    }
    dp[0][0] = 0;  
    for (int k = 0; k <= K; k++) {
        deque<pll> deq;
        pqg<pll> pq;
        if (k == 0) {
            pq.push({0, 0});
        }else{
            for (int i = 0; i < n; i++) {
                if (dp[k - 1][i] == LINF) continue;
                pll line = {-2*i, 1LL*i*i + dp[k - 1][i]};
                while (sz(deq) > 1) {
                    int len = sz(deq);
                    if (is_better(deq[len - 2], deq[len - 1], line)) {
                        deq.pop_back();
                    }else{
                        break;
                    }
                }
                deq.pb(line);
            }
            for (int i = 0; i < n; i++) {
                while (sz(deq) > 1 && y_val(deq[0], i) >= y_val(deq[1], i)) {
                    deq.pop_front();
                }
                // cerr << deq[0].first << ' ' << deq[0].second << " \n"[i == n - 1];
                dp[k][i] = min(dp[k - 1][i], 1LL*i*i + y_val(deq[0], i)); 
                pq.push({dp[k][i], i});
            } 
        }
        while (sz(pq)) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dp[k][u]) continue;
            for (auto &[v, w] : g[u]) {
                if (ckmin(dp[k][v], d + w)) {
                    pq.push({dp[k][v], v});
                } 
            } 
        }
    }
    for (int i = 0; i < n; i++) cout << dp[K][i] << " \n"[i == n - 1];
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

