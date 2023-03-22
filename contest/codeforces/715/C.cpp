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

constexpr int MAXN = 1e5 + 11;
bool vis[MAXN];
int sub[MAXN], power[MAXN], inv[MAXN], d, fwd[MAXN], bwd[MAXN];
vpi g[MAXN];
map<int, int> bfreq;
ll ans;
int n, m;

int add(int a, int b) { return (a + b) % m; }
int mul(int a, int b) { return 1LL * a * b % m;}
int inverse(int a, int mod) {
    a %= mod;
    int u = 0, v = 1, b = mod;
    while (a) {
        int q = b / a;
        b -= q * a;
        u -= q * v;
        swap(a, b), swap(u, v);
    }
    u %= mod;
    if (u < 0) u += mod;
    return u;
}


void precalc() {
    power[0] = 1;
    for (int i = 1; i < MAXN; i++) power[i] = mul(power[i - 1], 10);
    inv[0] = 1;
    inv[1] = inverse(10, m);
    for (int i = 2; i < MAXN; i++) inv[i] = mul(inv[i - 1], inv[1]);
}
int init(int u, int pu = -1) {
    sub[u] = 1;
    for (auto &[v, w] : g[u]) {
        if (v == pu || vis[v]) continue;
        sub[u] += init(v, u);
    }
    return sub[u];
}
int get_centroid(int u, int tot, int pu = -1) {
    for (auto &[v, w] : g[u]) {
        if (v != pu && !vis[v] && sub[v] * 2 > tot) {
            return get_centroid(v, tot, u);
        }
    }
    return u;
}
void dfs(int u, int pu) {
    for (auto &[v, w] : g[u]) {
        if (v == pu || vis[v]) continue;
        d++;
        fwd[v] = add(mul(10, fwd[u]), w);
        bwd[v] = add(bwd[u], mul(w, power[d - 1]));
        dfs(v, u);
        d--;
    }     
    ans += (fwd[u] == 0) + (bwd[u] == 0);
    bfreq[bwd[u]]++;
}
void dfs_add(int u, int pu, int val) {
    for (auto &[v, w] : g[u]) {
        if (v == pu || vis[v]) continue;
        dfs_add(v, u, val);
    }
    bfreq[bwd[u]] += val;
}
void dfs_two(int u, int pu) {
    for (auto &[v, w] : g[u]) {
        if (v == pu || vis[v]) continue;
        d++;
        dfs_two(v, u);
        d--;
    }
    int btarg = m - mul(inv[d], fwd[u]);
    if (btarg >= m) btarg -= m;
    if (bfreq.count(btarg)) ans += bfreq[btarg];
}
void cd(int u) {
    u = get_centroid(u, init(u));
    // dbg(u);
    map<int, int>().swap(bfreq);
    for (auto &[v, w] : g[u]) {
        if (vis[v]) continue;
        d = 1;
        fwd[v] = w % m;
        bwd[v] = w % m;
        dfs(v, u);
    }
    dbg(u, bfreq);
    for (auto &[v, w] : g[u]) {
        if (vis[v]) continue;
        d = 1;
        dfs_add(v, u, -1);
        dfs_two(v, u);
        dfs_add(v, u, 1);
    }
    dbg(ans); 
    vis[u] = 1;
    for (auto &[v, w] : g[u]) {
        if (!vis[v]) cd(v);
    }
}

void solve() {
    cin >> n >> m;
    precalc(); 
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].pb({v, w}), g[v].pb({u, w});
    }
    cd(0);
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

