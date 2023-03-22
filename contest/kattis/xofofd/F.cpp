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

void solve() {
    int N, T;
    cin >> N >> T;
    vi x(N), y(N), t(N);
    for (int i = 0; i < N; i++) cin >> x[i] >> y[i] >> t[i];
    ld real = 0;
    ld gps = 0;
    for (int i = 0; i < N - 1; i++) {
        real += sqrtl(1ll * (x[i] - x[i + 1]) * (x[i] - x[i + 1]) + 1ll * (y[i] - y[i + 1]) * (y[i] - y[i + 1]));
    }
    vector<ld> xx, yy;
    for (int cur = 0; cur <= t.back(); cur += T) {
        if (cur == t.back()) {
            xx.pb(x.back()), yy.pb(y.back()); 
        }else{
            auto it = ub(all(t), cur) - t.begin();
            it--;
            if (t[it] == cur) {
                xx.pb(x[it]), yy.pb(y[it]);
            }else{
                xx.pb(x[it] + (ld)(cur - t[it]) / (t[it + 1] - t[it]) * (x[it + 1] - x[it]));
                yy.pb(y[it] + (ld)(cur - t[it]) / (t[it + 1] - t[it]) * (y[it + 1] - y[it]));
            }
        }
    }
    if (t.back() % T) {
        xx.pb(x.back()), yy.pb(y.back());
    }
    for (int i = 0; i < sz(xx) - 1; i++) {
        gps += sqrtl(1ll * (xx[i] - xx[i + 1]) * (xx[i] - xx[i + 1]) + 1ll * (yy[i] - yy[i + 1]) * (yy[i] - yy[i + 1]));
    }
    dbg(real, gps);
    cout << fixed << setprecision(20);
    cout << (real - gps) / real * 100 << '\n'; 
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

