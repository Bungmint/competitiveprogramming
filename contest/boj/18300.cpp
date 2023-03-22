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

using ull = unsigned long long;
ull st = 0x600DCAFE;
ull line_sz = 350125310;
ull cyc_sz = 182129209;
ull cyc_st = 516914;
ull cyc_sum = 91029304;
vector<pair<ll, ull>> line_cnt = {{17523209, 120410903315}, {35055207, 1273471303}, {52584333, 117327198679}, 
{70103052, 943749230}, {87600494, 114307527999}, {105119641, 622001778}, {122648127, 111358905960}, {140161962, 307559631}, {157664636, 108465637480}, {175147925, 516914}};
vector<pair<ll, ull>> cyc_cnt = {{9084429, 699682908697}, {18197618, 443533675373}, {27305793, 279457613340}, {36398272, 174361037591}, {45500272, 107045731206}, {54603802, 63919545706}, {63737118, 36295683070}, {72843753, 18599082681}, {81939193, 7262563659}, {91029304, 516914}};


ull get_next(ull x) {
    x += (x >> 20LL) + 12345;
    if (x >= (1LL << 40)) x -= (1LL << 40);
    return x;
}

void solve() {
    ll n, ans = 0;
    cin >> n;
    if (n >= line_sz) {
        ans = line_cnt.back().fi;
        ll rest = n - line_sz;
        ll q = rest / cyc_sz, r = rest % cyc_sz;
        ans += q * cyc_sum;
        for (int i = 10; i >= 0; i--) {
            if (cyc_sz * i / 10 <= r) {
                if (i) ans += cyc_cnt[i - 1].fi;
                ll cur = (i ? cyc_cnt[i - 1].se : cyc_st); 
                ll rr = r - (cyc_sz * i / 10);
                for (int j = 0; j < rr; j++) {
                    ans += !(cur & 1);
                    cur = get_next(cur);
                }
                break;
            }
        }
        // for (int i = 0; i < r; i++) {
        //     ans += !(cur & 1);
        //     cur = get_next(cur);
        // }
    } else {
        for (int i = 10; i >= 1; i--) {
            if (line_sz * i / 10 <= n) {
                ans = line_cnt[i - 1].fi;
                ll cur = line_cnt[i - 1].se;
                ll rest = n - (line_sz * i / 10);
                for (int j = 0; j < rest; j++) {
                    ans += !(cur & 1);
                    cur = get_next(cur);
                }
                break;
            }
        }
        if (!ans) {
            ll cur = st;
            for (int j = 0; j < n; j++) {
                ans += !(cur & 1);
                cur = get_next(cur);
            }
        }
    }
    cout << ans << '\n';
}

void calc() {
    vector<pair<int, ull>> ret;
    int even = 0;
    ull cur = cyc_st;
    for (int i = 0; i <= cyc_sz; i++) {
        for (int j = 1; j <= 10; j++) {
            if (cyc_sz * j / 10 == i) {
                ret.pb({even, cur});
            }
        } 
        even += !(cur & 1);
        cur = get_next(cur);
    }
    dbg(ret);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--) {
        // calc();
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

