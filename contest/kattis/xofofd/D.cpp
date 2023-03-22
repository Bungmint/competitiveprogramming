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


constexpr int dx[] = {1, 0, -1, 0, -1, 1, -1, 1}, dy[] = {0, 1, 0, -1, 1, 1, -1, -1};

void solve() {
    int N, M;
    cin >> N >> M;
    vector<string> grid(N);
    for (auto &s : grid) cin >> s;
    vi d(26, INF);
    for (int i = 0; i < 26; i++) {
        if (i == 'W' - 'A') continue;
        vector<vi> dist(N, vi(M, INF));
        deque<pii> q;
        for (int r = 0; r < N; r++) for (int c = 0; c < M; c++) {
            if (grid[r][c] - 'A' == i) q.pb({r, c}), dist[r][c] = 0;
        }
        while (sz(q)) {
            auto [r, c] = q.front();
            q.pop_front();
            if (grid[r][c] == 'W') {
                d[i] = dist[r][c];
                break;
            }
            for (int k = 0; k < 8; k++) {
                int nr = r + dx[k], nc = c + dy[k];
                if (nr < 0 || nc < 0 || nr >= N || nc >= M) continue;
                if (grid[nr][nc] == grid[r][c]) {
                    if (ckmin(dist[nr][nc], dist[r][c])) {
                        q.push_front({nr, nc});
                    } 
                }else{
                    if (ckmin(dist[nr][nc], dist[r][c] + 1)) {
                        q.pb({nr, nc});
                    }
                }
            }
        }
    }
    for (int i = 0; i < 26; i++) {
        if (i == 'W' - 'A') continue;
        if (d[i] == INF) continue;
        cout << (char)('A' + i) << ' ' << d[i] - 1 << '\n';
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

