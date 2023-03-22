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

struct BIT {
    vi bit;
    int N;
    BIT(int n) {
        N = n;
        bit.resize(N + 1);
    }
    void upd(int i, int v) {
        for (i++; i <= N; i += i & -i) bit[i] += v;
    }
    int query(int r) {
        int ans = 0;
        for (r++; r; r -= r & -r) ans += bit[r];
        return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
    void clear() {
        bit.clear();
        bit = vi(N + 1);
    }
};

void solve() {
    string s;
    cin >> s;
    int n = sz(s);
    vector<vi> ind(26);
    for (int i = 0; i < n; i++) {
        ind[s[i] - 'a'].pb(i); 
    }
    int ok = 0;
    for (auto &v : ind) ok += sz(v) & 1;
    if (ok > 1) {
        cout << -1 << '\n';
        return;
    }
    ll ans = 0;
    int odd = -1;
    vi l(n, -1);
    for (auto &v : ind) {
        int k = sz(v) / 2;
        if (sz(v) & 1) odd = v[k];
        for (int i = 0; i < k; i++) {
            l[v[sz(v) - 1 - i]] = v[i];      
        }
    }
    if (n & 1) {
        for (auto &v : ind) {
            int k = sz(v) / 2;
            for (int i = 0; i < k; i++) {
                if (v[i] > odd) ans++;
                if (v[sz(v) - 1 - i] < odd) ans++;
            }
        }
    }
    ll a = 0, b = 0, c = 0;
    BIT bit(n);
    for (int i = 0; i < n; i++) {
        if (l[i] == -1) continue;
        // dbg(bit.query(l[i], i));
        a += bit.query(l[i], i);
        bit.upd(l[i], 1);
    }
    bit.clear();
    for (int i = 0; i < n; i++) {
        if (l[i] == -1 && i != odd) {
            bit.upd(i, 1);
            continue;
        }
        if (l[i] == -1) continue;
        b += bit.query(l[i] + 1, i);
        bit.upd(l[i], -2);
        bit.upd(i, 1);
    }
    dbg(1LL * (n / 2) * (n / 2 - 1) / 2);
    // dbg(a, b);
    b /= 2;
    c = 1LL * (n / 2) * (n / 2 - 1) / 2 - a - b;
    dbg(a, b, c);
    ans += b + 2 * c;
    cout << ans << '\n';
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

