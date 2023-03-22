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


int n, m, q, ans;
int a[1 << 20], q_pow[1 << 20];

int add(int a, int b) { a += b; if (a >= m) a -= m; return a; }
int sub(int a, int b) { a -= b; if (a < 0) a += m; return a; }
int mul(int a, int b) { return (1LL * a * b) % m; }
vi ntt(int idx, int k) {
    if (k == n) {
        return {a[idx]};
    }
    vi even = ntt(idx, k * 2);
    vi odd = ntt(idx + k, k * 2);
    vi res(2 * sz(even));
    const int half = n / (2 * k);
    for (int i = 0; i < half; i++) {
        res[i] = add(even[i], mul(q_pow[i * k], odd[i])); 
        res[i + half] = add(even[i], mul(q_pow[(i + half) * k], odd[i])); 
    }
    dbg(even, odd, res);
    return res;
}


void solve() {
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) cin >> a[i], a[i] %= m;
    q_pow[0] = 1;
    for (int i = 1; i < n; i++) q_pow[i] = mul(q_pow[i - 1], q);
    vi res = ntt(0, 1);
    for (auto &e : res) ans = add(ans, e);
    cout << ans << '\n';
    for (int i = 1; i <= n; i++) {
        cout << res[i % n] << " \n"[i == n];
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

