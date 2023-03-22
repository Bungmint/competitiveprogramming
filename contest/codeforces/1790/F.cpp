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

struct Info {
    int t, b, d;
};

constexpr int MAXN = 2e5 + 11;
int sub[MAXN];
int mn[MAXN][2];
bool vis[MAXN];
vi g[MAXN], v[MAXN];
vector<Info> anc[MAXN];
int root, branch, dist;


int get_size(int u, int pu) {
    sub[u] = 1;
    for (auto &v : g[u]) {
        if (v == pu || vis[v]) continue;
        sub[u] += get_size(v, u);
    }
    return sub[u];
}
int get_centroid(int u, int pu, int sz) {
    for (auto &v : g[u]) {
        if (v != pu && !vis[v] && 2 * sub[v] > sz) {
            return get_centroid(v, u, sz);
        }
    }
    return u;
}
void dfs(int u, int pu) {
    for (auto &v : g[u]) {
        if (v != pu && !vis[v]) ++dist, dfs(v, u), --dist;
    } 
    anc[u].pb({root, branch, dist});
}
void cd(int r) {
    r = get_centroid(r, -1, get_size(r, -1)); 
    root = r;
    v[r].reserve(sz(g[r]));
    for (auto &ch : g[r]) {
        if (!vis[ch]) {
            branch = sz(v[r]);
            dist = 1;
            dfs(ch, r);
            v[r].pb(INF);
        }
    }
    
    vis[r] = 1;
    for (auto &v : g[r]) {
        if (!vis[v]) cd(v);
    }
}

void solve() {
    int n, c_0;
    cin >> n >> c_0;
    c_0--;
    vi op(n - 1);
    for (auto &e : op) cin >> e, e--;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v, u--, v--;
        g[u].pb(v), g[v].pb(u);
    }
    for (int i = 0; i < n; i++) {
        mn[i][0] = mn[i][1] = INF;
    }
    cd(c_0);
    {
        for (auto &[t, b, d] : anc[c_0]) {
            // dbg(t, b, d);
            int &q = v[t][b];
            // dbg(q);
            if (d < q) {
                if (mn[t][0] == q) mn[t][0] = d;
                else {
                        for (int i = 0, val = d; i < 2; i++) {
                            if (mn[t][i] > val) swap(mn[t][i], val);
                        }
                    }
                q = d;
            }
        }
    }
    mn[c_0][0] = 0; 
    int ans = INF;
    for (int i = 0; i < n - 1; i++) {
        int u = op[i]; 
        for (auto &[t, b, d] : anc[u]) {
            // dbg(i, t, b, d);
            int &q = v[t][b];
            if (d < q) {
                if (mn[t][0] == q) mn[t][0] = d;
                else {
                        for (int i = 0, val = d; i < 2; i++) {
                            if (mn[t][i] > val) swap(val, mn[t][i]);
                        }
                    }
                q = d;
            }
            // dbg(mn[t][0], mn[t][1], t, c_0);
            ckmin(ans, mn[t][mn[t][0] == q] + d);
        }
        ckmin(ans, mn[u][0]); 
        mn[u][0] = 0;
        cout << ans << " \n"[i == n - 2];
    }


    for (int i = 0; i < n; i++) vis[i] = 0;
    for (int i = 0; i < n; i++) g[i].clear(), anc[i].clear(), v[i].clear();
    for (int i = 0; i < n; i++) sub[i] = 0, mn[i][0] = mn[i][1] = INF;
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

