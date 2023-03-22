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

int read() {
    string s;
    cin >> s;
    int decimal = -1;
    int res = 0;
    for (int i = 0; i < sz(s); i++) {
        if (s[i] == '.') {
            decimal = i;
            break;
        }
        res = 10 * res + s[i] - '0';
    }
    dbg(decimal, s);
    if (decimal >= 0) {
        for (int i = 0; i < 3; i++) {
            int it = i + 1 + decimal;
            if (it >= sz(s)) res *= 10;
            else res = res * 10 + s[it] - '0';
        }
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    int p = read(); 
    int sum = 0, wsum = 0;
    multiset<pii> st;
    for (int i = 0; i < n; i++) {
        int c, pi;
        cin >> c, pi = read();
        int b = p - pi;
        sum += c, wsum += c * b;
        st.insert({b, c}); 
    }
    dbg(st);
    cout << fixed << setprecision(20);
    while (wsum != 0) {
        dbg(wsum, st);
        if (wsum > 0) {
            auto [b, c] = *--st.end();
            st.erase(--st.end());
            if (b * c >= wsum) {
                cout << sum - (ld)(wsum) / (b) << '\n';
                return;
            } else {
                sum -= c;
                wsum -= b * c;
            }
        } else {
            auto [b, c] = *st.begin();
            st.erase(st.begin());
            if (abs(b * c) >= abs(wsum)) {
                cout << sum - (ld)(wsum) / (b) << '\n';
                return;
            } else {
                sum -= c;
                wsum -= b * c;
            }
        }
    }
    cout << sum << '\n';
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

