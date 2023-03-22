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

int sqrt_mod_2(vi& P, vi& Q) {
    vi copy = P;
    for (auto &e : copy) e &= 1;
    while (sz(copy) && copy.back() == 0) copy.pop_back();
    if (sz(copy) % 2 == 0) {
        if (sz(copy) == 0) {
            return 0;
        }
        return -1;
    }
    dbg(copy);
    int m = (sz(copy) - 1) / 2;
    Q.resize(m + 1);
    for (int i = 0; i <= 2 * m; i++) {
        if ((i & 1) && copy[i]) {
            return -1;
        } 
        if (i % 2 == 0) Q[i / 2] = copy[i];
    }
    return 0;
}
vi square_mod_5(const vi& P) {
    vi res(sz(P) * 2 - 1);
    for (int i = 0; i < sz(res); i++) {
        for (int j = 0; j <= i; j++) {
            if (j >= sz(P) || i - j >= sz(P)) continue;
            res[i] += P[j] * P[i - j]; 
        }
    }
    for (auto &e : res) e %= 5;
    return res;
}
int sqrt_mod_5(vi& P, vi& Q) {
    vi copy = P;
    for (auto &e : copy) e %= 5;
    while (sz(copy) && copy.back() == 0) copy.pop_back();
    if (sz(copy) % 2 == 0) {
        if (sz(copy) == 0) {
            return 0;
        }
        return -1;
    }
    int m = (sz(copy) - 1) / 2;
    Q.resize(m + 1);
    int am = -1;
    for (int i = 0; i < 5; i++) {
        if ((i * i) % 5 == copy[2 * m]) { am = Q[m] = i; break; }
    }
    if (am == -1) {
        return -1;
    }
    for (int i = 2 * m - 1; i >= m; i--) {
        int st = i - m + 1;
        int en = m - 1;
        int sum = copy[i];
        for (int j = st; j <= en; j++) {
            sum -= Q[j] * Q[i - j];
        }
        sum %= 5;
        if (sum < 0) sum += 5;
        for (int j = 0; j < 5; j++) {
            if ((2 * am * j) % 5 == sum) {
                Q[i - m] = j;
                break;
            }
        }
    }
    return (copy == square_mod_5(Q)) - 1; 
}

void solve() {
    string s;
    cin >> s;
    if (sz(s) % 2 == 0) {
        cout << -1 << '\n';
        return;
    }
    reverse(all(s));
    int m = (sz(s) - 1) / 2;
    vi a, b, c;
    for (auto &ch : s) a.pb(ch - '0');
    if (sqrt_mod_2(a, b) == -1 || sqrt_mod_5(a, c) == -1) {
        cout << -1 << '\n';
        return;
    }
    while (sz(b) < m + 1) b.pb(0);
    while (sz(c) < m + 1) c.pb(0);
    vector<string> ans;
    for (int iter = 0; iter < 2; iter++) {
        for (int it = 0; it < 2; it++) {
            string res;
            for (int i = 0; i <= m; i++) {
                int cur = c[i]; 
                if (cur % 2 != b[i]) cur += 5;
                res += (char)(cur + '0');
            } 
            reverse(all(res));
            ans.pb(res);
            for (auto &e : c) if (e) e = 5 - e;
        }
        for (auto &e : b) if (e) e = 2 - e;
    }
    sort(all(ans));
    cout << ans[0] << '\n';
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

