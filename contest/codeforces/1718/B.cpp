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

vl fib;
set<pll> good;

void precalc() {
    fib = {1, 1};
    good.insert({1, 0}), good.insert({2, 1});
    ll sum = 2;
    while (fib.back() <= 4LL * INF) {
        fib.pb(end(fib)[-2] + end(fib)[-1]);
        sum += fib.back();
        good.insert({sum, sz(fib) - 1});
    }
}

void solve() {
    int k;
    cin >> k;
    vi a(k);
    ll sum = 0;
    for (int i = 0; i < k; i++) {
        cin >> a[i];
        sum += a[i];
    }
    int la = -1;
    while (sum) {
        dbg(sum, la);
        dbg(a);
        auto it = good.lb({sum, -INF});
        if (it == good.end() || it->fi != sum) {
            cout << "NO\n";
            return;
        } 
        int targ = fib[it->se]; 
        int mx = -1, id = -1;
        for (int i = 0; i < k; i++) {
            if (a[i] >= targ && la != i) {
                if (ckmax(mx, a[i])) id = i;
            }
        } 
        if (mx == -1) {
            cout << "NO\n";
            return;
        }
        sum -= targ;
        a[id] -= targ;
        la = id;
    }
    cout << "YES\n";
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    precalc();
	int testcase = 1;
	cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

