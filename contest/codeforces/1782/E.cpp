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



struct Rect {
    int u, d;
    int l, r;
};

void solve() {
    int n;
    cin >> n;
    vector<Rect> a(n);   
    vi order(n);
    iota(all(order), 0);
    // vi ind;
    // auto get_ind = [&](int x) -> int {
    //     return lb(all(ind), x) - ind.begin();
    // };
    for (auto &[u, d, l, r] : a) {
        cin >> u >> l >> d >> r;
        // ind.pb(l), ind.pb(r + 1), ind.pb(r);
    }
    sort(all(order), [&](int i, int j){ return a[i].l < a[j].l; });
    stack<pii> uu, dd, uudd;
    for (auto &id : order) {
        auto &[u, d, l, r] = a[id];
        int u_mx = (sz(uu) ? uu.top().fi : 0);
        int d_mx = (sz(dd) ? dd.top().fi : 0);
        int ud_mx = (sz(uudd) ? uudd.top().fi : 0);
        if (u == d) {
            if (u == 1) {
                if (u_mx >= l || ud_mx >= l) {
                        if (u_mx >= l) {
                            if (u_mx >= r) u = d = l = r = 0;
                            else l = u_mx + 1;
                        }
                        if (ud_mx >= l){
                            if (ud_mx >= r) u = d = l = r = 0;
                            else l = ud_mx + 1;
                        }
                    }
                if (u) uu.push({r, id});
            } else {
                if (d_mx >= l || ud_mx >= l) {
                        if (d_mx >= l) {
                            if (d_mx >= r) u = d = l = r = 0;
                            else l = d_mx + 1;
                        }
                        if (ud_mx >= l) {
                            if (ud_mx >= r) u = d = l = r = 0;
                            else l = ud_mx + 1;
                        }
                    }
                if (d) dd.push({r, id});
            }
        } else {
            int uud = max(u_mx, ud_mx);
            int udd = max(d_mx, ud_mx);
            if (uud >= r && udd >= r) {
                u = d = l = r = 0;
            } else if (uud < l && udd < l) {
                 
            } else if (uud == udd) {
                l = uud + 1;
            } else if (u_mx >= r) {
                u = 2;
                l = max(max(d_mx, ud_mx) + 1, l);
            } else if (d_mx >= r) {
                d = 1;
                l = max(max(u_mx, ud_mx) + 1, l);
            } else {
                while (u_mx >= l && sz(uu)) {
                    int u_id = uu.top().se;
                    uu.pop();
                    if (a[u_id].l >= l) a[u_id] = {0, 0, 0, 0};
                    else {
                            a[u_id].r = l - 1;
                            uu.push({a[u_id].r, u_id});
                        } 
                    if (sz(uu)) u_mx = uu.top().fi;
                    else u_mx = 0;
                }
                while (d_mx >= l && sz(dd)) {
                    int d_id = dd.top().se;
                    dd.pop();
                    if (a[d_id].l >= l) a[d_id] = {0, 0, 0, 0};
                    else {
                            a[d_id].r = l - 1;
                            uu.push({a[d_id].r, d_id});
                        } 
                    if (sz(dd)) d_mx = dd.top().fi;
                    else d_mx = 0;
                }
                while (ud_mx >= l && sz(uudd)) {
                    int ud_id = uudd.top().se;
                    uudd.pop();
                    if (a[ud_id].l >= l) a[ud_id] = {0, 0, 0, 0};
                    else {
                            a[ud_id].r = l - 1;
                            uu.push({a[ud_id].r, ud_id});
                        } 
                    if (sz(uudd)) ud_mx = uudd.top().fi;
                    else ud_mx = 0;
                }
            }
            if (u == 1 && d == 1) uu.push({r, id}); 
            if (u == 2 && d == 2) dd.push({r, id});
            if (u == 1 && d == 2) uudd.push({r, id});
        }
    }
    int ans = 0;
    for (auto &[u, d, l, r] : a) if (u) ans += (d - u + 1) * (r - l + 1);
    cout << ans << '\n';
    for (auto &[u, d, l, r] : a) cout << u << ' ' << l << ' ' << d << ' ' << r << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

