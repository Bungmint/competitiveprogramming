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


void fill_radj(int x, vi& nxt, vector<vi>& radj, vi& cyc_id, vi& cyc_sz, vi& reach, vi& d) {
    reach[x] = 1;
    for (auto &e : radj[x]) {
        if (!cyc_id[e]) {
            cyc_id[e] = cyc_id[x];
            cyc_sz[e] = cyc_sz[x];
            d[e] = d[x] + 1;
            fill_radj(e, nxt, radj, cyc_id, cyc_sz, reach, d);
            reach[x] += reach[e];  
        }
    }
}

void floyd(int x, vi& nxt, vector<vi>& radj, vi& cyc_id, vi& cyc_sz, vi& reach, vi& d) {
    int y = x;
    do {
        x = nxt[x];
        y = nxt[nxt[y]];
    } while (x != y);
    int cnt = 0;
    do {
        cnt++;
        cyc_id[x] = y;
        x = nxt[x];
    } while (x != y);
    do {
        cyc_sz[x] = cnt;
        x = nxt[x];
    } while (x != y);
    do {
        fill_radj(x, nxt, radj, cyc_id, cyc_sz, reach, d);
        x = nxt[x];
    } while (x != y);
}

void solve() {
    int n;
    cin >> n;
    vi nxt(3 * n + 1);
    vector<vi> radj(3 * n + 1);
    vi cyc_id(3 * n + 1), cyc_sz(3 * n + 1);
    vi pref(3 * n + 1), reachable(3 * n + 1), dist(3 * n + 1);
    for (int i = 1; i <= 3 * n; i++) nxt[i] = i;
    for (int i = 1; i <= n; i++) {
        cin >> nxt[i + n]; 
        nxt[i + n] += i + n;
    }
    for (int i = 1; i <= 3 * n; i++) {
        radj[nxt[i]].pb(i);
    }
    dbg();
    for (int i = 1; i <= 3 * n; i++) {
        if (!cyc_id[i]) {
            floyd(i, nxt, radj, cyc_id, cyc_sz, reachable, dist);
        }
    }
    vi vis(3 * n + 1);
    int st = n + 1;
    while (!vis[st]) {
        vis[st] = 1;
        st = nxt[st];
    }
    for (int i = 1; i <= 3 * n; i++) {
        pref[i] = pref[i - 1];
        if (cyc_sz[i] == 1 && cyc_id[i] != cyc_id[st] && (cyc_id[i] > 2 * n || cyc_id[i] < n + 1)) {
            pref[i]++;
        }
    }
    bool good = cyc_sz[st] == 1 && (st > 2 * n || st < n + 1); 
    
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[n + i]) {
            ans += pref[2 * n + i] - pref[i - 1];
            if (good) {
                int cc = reachable[st]; 
                if (cc > reachable[n + i]) ans += cc - reachable[n + i] - 1;
                if (abs(n + i - st) <= n) ans++;
            }
        } else {
            if (good) {
                ans += 2 * n + 1; 
            }
        }
    }
    cout << ans << '\n';
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

