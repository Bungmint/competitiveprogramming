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
    int n, Q;
    cin >> n >> Q;
    ll mx = 1LL * n * (n + 1) / 2LL + n;
    auto numbering = [&](ll x) -> string {
        int res10 = x % 10, res100 = x % 100;
        if (res10 == 0 || res10 > 3) return "th";
        if (res100 >= 11 && res100 <= 13) return "th";
        if (res10 == 1) return "st";
        if (res10 == 2) return "nd";
        if (res10 == 3) return "rd";
        return "WTF";
    };
    for (int i = 0; i < Q; i++) {
        ll x;
        cin >> x;
        if (x > mx) {
            cout << "Codemas is already over!";
        } else {
            int L = 1, R = n, res = 1;
            while (L <= R) {
                int mid = (L + R) / 2;
                ll tot = 1LL * mid * (mid + 1) / 2LL + mid;
                if (x <= tot) {
                    res = mid;
                    R = mid - 1;
                } else {
                    L = mid + 1;
                }
            }
            ll extra = x - (1LL * res * (res - 1) / 2LL + res - 1); 
            if (extra == 1) {
                cout << "On the " << res << numbering(res) << " day of Codemas, my computer gave to me,"; 
            } else {
                int day = res + 2 - extra;
                if (day == 5) {
                    cout << "FIVE! COMPILER! WARNINGS!!!";
                } else if (day == 1) {
                    if (res == 1) {
                        cout << "A syntax error on line three!"; 
                    } else {
                        cout << "And a syntax error on line three!"; 
                    }
                } else {
                    cout << day << " compiler warnings,";
                }
            }
        }
        if (i < Q - 1) cout << '\n';
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

