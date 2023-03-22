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

constexpr int MAXN = 500'100;
vi tree[MAXN];
vi res[MAXN];
int f[MAXN], g[MAXN];
bool ok;

void dfs_down(int u, int pu) {
    int ch = 0;
    for (auto &v : tree[u]) {
        if (v == pu) continue;
        dfs_down(v, u);
        res[u].pb(f[v]);
        ch++;
    }
    if (ch == 0) {
        f[u] = 0; 
    } else if (ch == 1) {
        f[u] = res[u].front(); 
    } else {
        sort(all(res[u]));
        f[u] = max(end(res[u])[-2] + 1, end(res[u])[-1]);
    }
}
void dfs_up(int u, int pu) {
    if (u) {
        if (sz(res[pu]) == 1) {
            g[u] = 0; 
        } else if (sz(res[pu]) == 2) {
            g[u] = (res[pu][0] == f[u] ? res[pu][1] : res[pu][0]); 
        } else {
            if (end(res[pu])[-2] == f[u]) {
                g[u] = max(end(res[pu])[-3] + 1, end(res[pu])[-1]);
            } else if (end(res[pu])[-1] == f[u]) {
                g[u] = max(end(res[pu])[-3] + 1, end(res[pu])[-2]);
            } else {
                g[u] = max(end(res[pu])[-2] + 1, end(res[pu])[-1]);
            }
        }
        res[u].pb(g[u]);
        sort(all(res[u]));
        if (sz(res[u]) == 1) {
            ok |= res[u].front() <= 2;
        } else {
            ok |= end(res[u])[-2] <= 1 && end(res[u])[-1] <= 2;
        }
    }
    for (auto &v : tree[u]) {
        if (v == pu) continue;
        dfs_up(v, u);
    }
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        tree[u].pb(v), tree[v].pb(u);
    }
    dfs_down(0, -1);
    dfs_up(0, -1);
    cout << (ok ? "YES" : "NO") << '\n'; 
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

