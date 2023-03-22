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


template <typename T>
T inverse(T a, T mod) {
    a %= mod;
    T u = 0, v = 1, b = mod;
    while (a) {
        T q = b / a;
        b -= q * a, u -= q * v;
        swap(a, b), swap(u, v);
    }
    u %= mod;
    if (u < T(0)) u += mod;
    return u;
}
ll crt(ll a, ll am, ll b, ll bm, ll& c, ll& cm) {
    a %= am, b %= bm;
    if (am == 1) {
        c = b, cm = bm;
        return 0;
    } 
    if (bm == 1) {
        c = a, cm = am;
        return 0;
    }
    ll g = gcd(am, bm), l = lcm(am, bm);
    if ((b - a) % g) return -1;
    cm = l;
    am /= g, bm /= g;
    ll x = (inverse(am, bm) * ((b - a) / g)) % bm;
    c = (a + am * g * x) % l;
    c = (c + l) % l;
    assert(c >= 0 && c < l);
    return 0;
}

void solve() {
    ll n, m, s, t;
    cin >> n >> m;
    vl x(m), y(m);
    for (int i = 0; i < m; i++) cin >> x[i] >> y[i];
    cin >> s >> t;
    if (s > n || t > n) {
        cout << -1 << '\n';
        return;
    }
    vector<vi> graph(m);
    vi dist(m, INF), targ(m), par(m, -1);
    queue<int> q;
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            ll c, cm;
            if (crt(x[i], y[i], x[j], y[j], c, cm) == -1) continue;
            if (c > n || (c == 0 && cm > n)) continue;
            ll tt = (n - c) / cm;
            if (x[i] > cm * tt + c || x[j] > cm * tt + c) continue;
            graph[i].pb(j), graph[j].pb(i);
        }
    }
    for (int i = 0; i < m; i++) {
        if (s - x[i] < 0 || (s - x[i]) % y[i]) continue;
        dist[i] = 0;
        q.push(i);
    }
    for (int i = 0; i < m; i++) {
        if (t - x[i] < 0 || (t - x[i]) % y[i]) continue;
        targ[i] = 1;
    }
    while (sz(q)) {
        int u = q.front();
        q.pop();
        for (auto &v : graph[u]) {
            if (ckmin(dist[v], dist[u] + 1)) q.push(v), par[v] = u;
        }
    }
    int en = -1, res = INF;
    for (int i = 0; i < m; i++) {
        if (targ[i] && ckmin(res, dist[i])) {
            en = i;
        }
    }
    vi ans;
    while (en != -1) ans.pb(en + 1), en = par[en];
    reverse(all(ans));
    if (sz(ans) == 0) cout << -1 << '\n';
    else{
            cout << sz(ans) << '\n';
            for (int i = 0; i < sz(ans); i++) cout << ans[i] << '\n';
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

