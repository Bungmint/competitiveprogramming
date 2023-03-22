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

using Point = ar<int, 3>;

void solve() {
    while (true) {
        int a, b, c, m;
        cin >> a;
        if (a == -1) return;
        cin >> b >> c >> m;
        vector<Point> choc(m);
        vector<pair<Point, Point>> cube(m);
        bool good = 1;
        ll sum_v{};
        for (auto &[x, y, z] : choc) cin >> x >> y >> z;
        for (auto &[p, q] : cube) {
            cin >> p[0] >> p[1] >> p[2] >> q[0] >> q[1] >> q[2];
            good &= max(p[0], q[0]) <= a;
            good &= max(p[1], q[1]) <= b;
            good &= max(p[2], q[2]) <= c;
            ll sum = 1;
            for (int k = 0; k < 3; k++) {
                sum *= (q[k] - p[k] + 1);
            }
            if (sum_v >= 2 * LINF) continue;
            sum_v += sum;
        }
        good &= sum_v == 1LL * a * b * c;
        for (int i = 0; i < m; i++) {
            for (int k = 0; k < 3; k++) {
                if (cube[i].fi[k] <= choc[i][k] && cube[i].se[k] >= choc[i][k]) {
                    continue;
                }
                good = 0;
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                Point ok{};
                for (int k = 0; k < 3; k++) {
                    ok[k] = max(cube[i].fi[k], cube[j].fi[k]) <= min(cube[i].se[k], cube[j].se[k]);
                }
                if (ok[0] == ok[1] && ok[1] == ok[2] && ok[0]) {
                    good = 0; 
                }
            }
        }
        cout << (good ? "YES" : "NO") << '\n';
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

