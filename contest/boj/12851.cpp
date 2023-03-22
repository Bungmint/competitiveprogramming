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

int dist[1 << 18];
ll ways[1 << 18];

void solve() {
    int n, k;
    cin >> n >> k;
    queue<int> q;
    dist[n] = 0;
    ways[n] = 1;
    q.push(n);
    while (sz(q)) {
        int u = q.front();
        q.pop();
        if (u == k) {
            cout << dist[u] << '\n';
            cout << ways[u] << '\n';
            return;
        }
        if (u) {
            if (ckmin(dist[u - 1], dist[u] + 1)) {
                q.push(u - 1);
                ways[u - 1] = ways[u];
            } else if (dist[u - 1] == dist[u] + 1) {
                ways[u - 1] += ways[u];
            }
        }
        if (u + 1 < (1 << 18)) {
            if (ckmin(dist[u + 1], dist[u] + 1)) {
                q.push(u + 1);
                ways[u + 1] = ways[u];
            } else if (dist[u + 1] == dist[u] + 1) {
                ways[u + 1] += ways[u];
            }
        }
        if (2 * u < (1 << 18)) {
            if (ckmin(dist[2 * u], dist[u] + 1)) {
                q.push(2 * u);
                ways[2 * u] = ways[u];
            } else if (dist[2 * u] == dist[u] + 1) {
                ways[2 * u] += ways[u];
            }
        }
    }
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    memset(dist, 0x3f, sizeof(dist));
	int testcase = 1;
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

