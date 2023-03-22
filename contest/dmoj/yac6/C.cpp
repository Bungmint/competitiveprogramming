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

#define int long long
int n, m;
int query(int x, int y) {
    if (x < 0 || y < 0 || x > n || y > m) return 1;
    cout << "? " << x << ' ' << y << endl;
    int d;
    cin >> d;
    return d;
}
void answer(int a, int b, int c, int d) {
    cout << "! " << a << ' ' << b << ' ' << c << ' ' << d << endl;
}

void solve() {
    cin >> n >> m;
    int a, b, c, d;
    int a_plus_b = query(1, 1) + 2;
    int c_plus_d = n + m - query(n, m);
    int a_minus_b = query(1, m) - m + 1;
    int c_minus_d = n - 1 - query(n, 1);
    {
        a = a_plus_b + a_minus_b; 
        b = a_plus_b - a_minus_b;
        c = c_plus_d + c_minus_d;
        d = c_plus_d - c_minus_d;
        if ((a & 1) || (b & 1) || (c & 1) || (d & 1)) {
            swap(a_minus_b, c_minus_d); 
        }else{
            int q = query(a / 2, b / 2);                
            if (q) swap(a_minus_b, c_minus_d);
        }
    }
    a = a_plus_b + a_minus_b; 
    b = a_plus_b - a_minus_b;
    c = c_plus_d + c_minus_d;
    d = c_plus_d - c_minus_d;
    answer(a / 2, b / 2, c / 2, d / 2);
}

int32_t main() {
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

