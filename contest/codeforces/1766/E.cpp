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
    int n;
    cin >> n;
    vi a(n);
    for (auto &e : a) cin >> e;
    ll ans = 0;
    set<int> ab, ba, c;
    vi ivsa(n, -1), ivsb(n, -1);
    for (int i = 0; i < n; i++) {
        if (!a[i]) {
            ans += 1LL * (i + 1) * (n - i);
        }
        if (i + 1 < n) {
            if (a[i] == 1 && a[i + 1] == 2) ab.insert(i + 1), ivsa[i] = i + 1;
            if (a[i] == 2 && a[i + 1] == 1) ba.insert(i + 1), ivsb[i] = i + 1;
        }
    }
    ans += 1LL * (n + 1) * n / 2LL;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            int cnt = 1;
            int ii = i - 1;
            int p = (i ? a[i - 1] : -1);
            while (i + 1 < n && a[i + 1] == 0) cnt++, i++;
            int nxt = (i + 1 < n ? a[i + 1] : -1);
            if (p == 1 && nxt == 2) ab.insert(i + 1), ivsa[ii] = i + 1;
            if (p == 2 && nxt == 1) ba.insert(i + 1), ivsb[ii] = i + 1;
            ans -= 1LL * (cnt + 1) * cnt / 2LL;
        }
    }
    vector<vi> b;
    vi id(n);
    b.pb({});
    for (int i = 0; i < n; i++) {
        if (a[i] == 3) {
            b.pb({}); 
        }
        id[i] = sz(b) - 1;
        if (ivsa[i] >= 0) {
            if (sz(b[id[i]])) ab.erase(ivsa[i]);
            b.back().pb(i);
        }
        if (ivsb[i] >= 0) {
            if (sz(b[id[i]])) ba.erase(ivsb[i]);
            b.back().pb(i);
        }
    }
    for (auto &v : b) reverse(all(v));
    for (int i = 0; i < n; i++) {
        dbg(ab, ba);
        auto it1 = ab.lb(i);
        if (it1 != ab.end()) ans += n - *it1;
        auto it2 = ba.lb(i);
        if (it2 != ba.end()) ans += n - *it2;
        if (ivsa[i] >= 0) {
            ab.erase(ivsa[i]);
            b[id[i]].pop_back();
            if (sz(b[id[i]])) {
                int j = b[id[i]].back();
                if (ivsa[j] >= 0) ab.insert(ivsa[j]);
                if (ivsb[j] >= 0) ba.insert(ivsb[j]);
            }
        }
        if (ivsb[i] >= 0) {
            ba.erase(ivsb[i]);
            b[id[i]].pop_back();
            if (sz(b[id[i]])) {
                int j = b[id[i]].back();
                if (ivsa[j] >= 0) ab.insert(ivsa[j]);
                if (ivsb[j] >= 0) ba.insert(ivsb[j]);
            }
        }
    }
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

