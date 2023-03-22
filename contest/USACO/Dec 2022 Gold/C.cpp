#include <bits/stdc++.h>
using namespace std;

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


struct DSU {
	vi e;
	DSU(int N) { e = vi(N, -1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool same_set(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) {
		x = get(x), y = get(y);
		if (x == y) return false;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
		return true;
	}
};

// O(nlogn)?
void solve() {
    int N, M;
    cin >> N >> M;
    vector<vi> g(N);
    vi deg(N);
    set<pii> min_deg;
    vi remove_seq;
    vi vis(N);
    DSU dsu(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].pb(v), g[v].pb(u);
        deg[u]++, deg[v]++;
    }
    for (int i = 0; i < N; i++) min_deg.insert({deg[i], i});
    for (int i = 0; i < N; i++) {
        auto [_, u] = *min_deg.begin();
        min_deg.erase(min_deg.begin());
        remove_seq.pb(u);
        vis[u] = 1;
        for (auto &v : g[u]) {
            if (!vis[v]) {
                min_deg.erase({deg[v], v});
                deg[v]--;
                min_deg.insert({deg[v], v});
            }
        }
    }
    reverse(all(remove_seq));
    fill(all(vis), 0);
    fill(all(deg), 0);
    ll ans = 0;
    for (auto &u : remove_seq) {
        vis[u] = 1;
        for (auto &v : g[u]) {
            if (vis[v]) {
                deg[u]++;
                dsu.unite(u, v);
            }
        } 
        ckmax(ans, 1LL * deg[u] * dsu.size(u));
    }
    cout << ans << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    solve();
}

