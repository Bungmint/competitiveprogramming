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

#pragma endregion template

constexpr ld EPS = 1e-9;

ld safe_acos(ld x) {
    if (x > 1.0) x = 1.0;
    if (x < -1.0) x = -1.0;
    return acosl(x);
}
ld calc(ld lo_a, ld la_a, ld lo_b, ld la_b) {
    ld del_phi = (la_b - la_a) / 2;
    ld del_lambda = (lo_b - lo_a) / 2;
    ld a = sinl(del_phi) * sinl(del_phi) + cosl(la_a) * cosl(la_b) * sinl(del_lambda) * sinl(del_lambda);
    return 6381 * atan2l(sqrtl(a), sqrtl(1 - a)) * 2;
}

void solve() {
    int N, M, s, t;
    string ss, tt;
    cin >> N >> M;
    cin >> ss >> tt;
    vector<vi> g(N);
    vector<string> str(N);
    map<string, int> ind;
    vector<ld> lo(N), la(N);
    vector<ld> dist(N, LINF);
    for (int i = 0; i < N; i++) {
        cin >> str[i] >> la[i] >> lo[i]; 
        lo[i] *= PI / 180, la[i] *= PI / 180;
        ind[str[i]] = i;
    }
    s = ind[ss], t = ind[tt];
    for (int i = 0; i < M; i++) {
        string st, en;
        cin >> st >> en;
        int u = ind[st], v = ind[en];
        g[u].pb(v), g[v].pb(u);
    }
    dbg(g);
    pqg<pair<ld, int>> pq;
    dist[s] = 0;
    pq.push({dist[s], s});
    while (sz(pq)) {
        auto [d, u] = pq.top();
        dbg(d, u);
        pq.pop();
        if (d > dist[u] + EPS) continue;
        for (auto &v : g[u]) {
            ld dd = calc(lo[u], la[u], lo[v], la[v]) + 100;
            dbg(dd);
            if (dist[v] > dist[u] + dd + EPS) {
                dist[v] = dist[u] + dd;
                pq.push({dist[v], v});
            }
        } 
    }
    if (dist[t] > LINF / 2.0) {
        cout << -1 << '\n';
        return;
    }
    cout << fixed << setprecision(20) << dist[t] << '\n';
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

