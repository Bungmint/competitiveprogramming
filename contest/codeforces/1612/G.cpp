// Copyright © 2022 Youngmin Park. All rights reserved.
// #pragma GCC optimize("O3")
// #pragma GCC target("avx2")
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

const int MAXN = 3'000'000, MOD = 1e9 + 7;
const int OFFSET = 1e6 + 10;
const ll INV2 = 5e8 + 4;
int fact[MAXN];
int a[MAXN];
ll mul(ll a, ll b) { a %= MOD, b %= MOD, a += MOD, b += MOD; return 1LL * a * b % MOD; }

void solve() {
    fact[0] = fact[1] = 1;
    for (int i = 2; i < MAXN; i++) fact[i] = (1LL * fact[i - 1] * i) % MOD;
    int M;
    cin >> M;
    ll sum = 0;
    for (int i = 0; i < M; i++) {
        int c;
        cin >> c;
        a[OFFSET - (c - 1)]++;
        a[OFFSET + (c + 1)]--;
        sum += c;
    } 
    for (int i = 2; i < MAXN; i++) a[i] += a[i - 2];
    ll ans = 0;
    ll cnt = 1;
    for (int i = MAXN - 1; i >= 0; i--) {
        if (a[i] == 0) continue; 
        assert(a[i] >= 0);
        assert(sum >= a[i]);
        cnt *= fact[a[i]], cnt %= MOD;
        ll cur = mul(i - OFFSET, mul(2 * sum - a[i] + 1, a[i]));
        cur = mul(cur, INV2);
        sum -= a[i];
        ans += cur;
        ans %= MOD;
        (ans += MOD) %= MOD;
    }
    ans %= MOD;
    ans += MOD;
    ans %= MOD;
    dbg(ans);
    cout << ans << ' ' << cnt << '\n';
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

