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

int MOD;

void solve() {
    int n, q;
    cin >> n >> q >> MOD;
    vi a(n), b(n), fib(n + 1);
    for (auto &e : a) cin >> e;
    for (auto &e : b) cin >> e;
    fib[1] = fib[2] = 1;
    for (int i = 3; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
        fib[i] %= MOD;
    } 
    vi c(n + 1);
    for (int i = n; i >= 1; i--) {
        c[i] = a[i - 1] - b[i - 1]; 
        c[i] %= MOD;
        if (c[i] < 0) c[i] += MOD;
        for (int j = i + 1; j <= min(n, i + 2); j++) {
            c[j] -= c[i];
            c[j] %= MOD;
            if (c[j] < 0) c[j] += MOD;
        }
    }
    int cnt = count(1 + all(c), 0);
    for (int i = 0; i < q; i++) {
        char ch;
        int l, r;
        cin >> ch >> l >> r;
        int fl = (ch == 'A' ? 1 : -1);
        if (c[l] == 0) cnt--; 
        c[l] += fl;
        c[l] %= MOD;
        if (c[l] < 0) c[l] += MOD;
        if (c[l] == 0) cnt++;
        if (r + 2 <= n) {
            if (c[r + 2] == 0) cnt--;
            c[r + 2] += -fl * fib[r - l + 1];
            c[r + 2] %= MOD;
            if (c[r + 2] < 0) c[r + 2] += MOD;
            if (c[r + 2] == 0) cnt++;
        } 
        if (r + 1 <= n) {
            if (c[r + 1] == 0) cnt--;
            c[r + 1] += -fl * fib[r - l + 2];
            c[r + 1] %= MOD;
            if (c[r + 1] < 0) c[r + 1] += MOD;
            if (c[r + 1] == 0) cnt++;
        }
        cout << (cnt == n ? "YES" : "NO") << '\n';
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

