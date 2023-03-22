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

constexpr int MAXN = 1 << 20;
int mu[1 << 20];
int lp[1 << 20];
vi pr;

void precalc() {
    lp[0] = lp[1] = -1;
    mu[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        if (lp[i] == 0) {
            lp[i] = i;
            mu[i] = -1;
            pr.pb(i);
        } 
        for (int j = 0; i * pr[j] < MAXN && j < sz(pr); j++) {
            lp[i * pr[j]] = pr[j];
            mu[i * pr[j]] = mu[i] * (-1);
            if (i % pr[j] == 0) {
                mu[i * pr[j]] = 0;
                break;
            }
        } 
    }
}
ll get_square_free(ll x) {
    ll res = 0;
    for (ll i = 1; i < MAXN; i++) {
        if (i * i > x) break;
        if (mu[i]) res += mu[i] * (x / (i * i));
    }
    return res;
}
bool is_square_free(ll x) {
    for (auto &p : pr) {
        if (1LL * p * p > x) break;
        if (x % (1LL * p * p) == 0) return false;
    }
    return true;
}

void solve() {
    int N;
    cin >> N;
    ll L = 1, R = 1e11, ans = 1;
    while (L <= R) {
        ll M = (L + R) / 2;
        ll cnt = get_square_free(M);
        if (cnt == N) {
            if (is_square_free(M)) {
                ans = M;
                break;
            } else {
                R = M - 1;
            }
        } else if (cnt > N) {
            R = M - 1;
        } else {
            L = M + 1;
        }
    }
    cout << ans << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    precalc();
	int testcase = 1;
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

