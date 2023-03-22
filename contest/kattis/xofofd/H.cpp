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

constexpr int MAXN = 1e5 + 11;
constexpr ld EPS = 1e-9;
int N;
using Line = pll;
ld intersect_x(Line& l1, Line& l2) {
    return -(ld)(l2.se - l1.se) / (l2.fi - l1.fi);
}
ld f(Line& l1, ld x) {
    return l1.fi * x + l1.se;
}

void solve() {
    cin >> N;	
    vpl lines(N);
    deque<Line> max_ch, min_ch;
    vector<ld> crit_x;
    ll max_t = 0;
    for (auto &[v, t] : lines) cin >> t >> v, ckmax(max_t, t);
    crit_x.pb(max_t);
    sort(all(lines));
    for (auto &[v, t] : lines) {
        Line l = {v, -v * t};
        if (sz(max_ch) && max_ch.back().fi == v) continue;
        while (sz(max_ch) > 1 && intersect_x(max_ch[sz(max_ch) - 2], l) < intersect_x(max_ch[sz(max_ch) - 2], max_ch[sz(max_ch) - 1]) + EPS) {
            max_ch.pop_back();
        }
        max_ch.pb(l);
    }
    for (int i = 0; i < sz(max_ch) - 1; i++) {
        crit_x.pb(intersect_x(max_ch[i], max_ch[i + 1]));
    }
    reverse(all(lines));
    for (auto &[v, t] : lines) {
        Line l = {v, -v * t};
        if (sz(min_ch) && min_ch.back().fi == v) continue;
        while (sz(min_ch) > 1 && intersect_x(min_ch[sz(min_ch) - 2], l) < intersect_x(min_ch[sz(min_ch) - 1], min_ch[sz(min_ch) - 2]) + EPS) {
            min_ch.pop_back();
        }
        min_ch.pb(l);
    }
    for (int i = 0; i < sz(min_ch) - 1; i++) {
        crit_x.pb(intersect_x(min_ch[i], min_ch[i + 1]));
    }
    sort(all(crit_x));
    if (sz(max_ch) == 1 && sz(min_ch) == 1) {
        cout << abs(max_ch[0].se - min_ch[0].se) << '\n'; 
        return;
    }
    ld ans = LINF;
    dbg(crit_x, max_ch, min_ch);
    for (auto &e : crit_x) {
        if (e + EPS < max_t) continue;
        while (sz(max_ch) > 1 && f(max_ch[0], e) < f(max_ch[1], e) + EPS) max_ch.pop_front();
        while (sz(min_ch) > 1 && f(min_ch[0], e) + EPS > f(min_ch[1], e)) min_ch.pop_front();
        ld res = f(max_ch[0], e) - f(min_ch[0], e);
        dbg(max_ch[0], min_ch[0]);
        dbg(res);
        if (ans > res + EPS) {
            ans = res;
        }
    }

    cout << fixed << setprecision(20) << ans << '\n';
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

