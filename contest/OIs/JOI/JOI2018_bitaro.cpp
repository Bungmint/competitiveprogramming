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

constexpr int SQRT = 350, MAXN = 100'111;
vi g[MAXN], revg[MAXN];
vpi top[MAXN];
bool vis[MAXN];
int dp[MAXN];
int N, M, Q;

void calc_top() {
    for (int u = 0; u < N; u++) {
        top[u] = {{u, 0}};   
        for (auto &v : revg[u]) {
            {
                vpi fin;
                int su = sz(top[u]), sv = sz(top[v]); 
                for (int i = 0, j = 0; sz(fin) < SQRT && (i < su || j < sv); ) {
                    if (j == sv || (i != su && top[u][i].se > 1 + top[v][j].se)) {
                        fin.pb(top[u][i]);
                        vis[top[u][i].fi] = 1;
                        i++;
                    } else {
                        fin.eb(top[v][j].fi, top[v][j].se + 1);
                        vis[top[v][j].fi] = 1;
                        j++;
                    }
                    while (i < su && vis[top[u][i].fi]) i++;
                    while (j < sv && vis[top[v][j].fi]) j++;
                }
                for (auto &[w, _] : fin) vis[w] = 0;
                swap(top[u], fin);
            }
        }
    }
}

void solve() {
    cin >> N >> M >> Q;
    vi is_forb(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v, u--, v--;
        g[u].pb(v);
        revg[v].pb(u);
    }
    calc_top(); 
    for (int i = 0; i < Q; i++) {
        int T, Y;
        cin >> T >> Y;
        T--;
        vi forb(Y);
        for (auto &e : forb) {
            cin >> e;
            e--;
            is_forb[e] = 1;
        }
        if (Y < SQRT) {
            // dbg(forb, top[T]);
            int ans = -1;
            for (auto &[u, d] : top[T]) {
                if (!is_forb[u]) ckmax(ans, d); 
            } 
            cout << ans << '\n'; 
        } else {
            memset(dp, -1, sizeof(dp));
            for (int u = 0; u < N; u++) {
                if (!is_forb[u]) ckmax(dp[u], 0);
                if (dp[u] < 0) continue;
                for (auto &v : g[u]) {
                    ckmax(dp[v], dp[u] + 1); 
                }
            }
            cout << dp[T] << '\n'; 
        }
        for (auto &e : forb) {
            is_forb[e] = 0;
        }
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

