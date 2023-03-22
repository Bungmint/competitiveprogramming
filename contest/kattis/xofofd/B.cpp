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

int read_double() {
    string s;
    cin >> s;
    auto it = s.find('.');
    if (it == string::npos) return stoi(s);
    while (sz(s) - 1 - it < 7) s.pb('0');
    int res = 0, sign = 1;
    for (auto &ch : s) {
        if (ch == '-') {
            sign = -1;
        }else if (ch != '.') {
            res *= 10;
            res += ch - '0';
        }
    }
    return res * sign;
}

void solve() {
    while (true) {
        int nx, ny;
        cin >> nx >> ny;
        int w = read_double();
        if (nx == 0 && ny == 0 && w == 0) {
            return;
        }
        vl x(nx), y(ny);
        for (auto &e : x) e = read_double() * 2;
        for (auto &e : y) e = read_double() * 2;
        sort(all(x)); sort(all(y));
        ll mix = x[0] - w, mxx = x[0] + w;
        for (auto &e : x) {
            if (mxx < e - w) break;
            mxx = e + w;
        }
        ll miy = y[0] - w, mxy = y[0] + w;
        for (auto &e : y) {
            if (mxy < e - w) break;
            mxy = e + w;
        }
        cout << ((mix <= 0 && mxx >= 1LL * INF * 3 / 2LL) && miy <= 0 && mxy >= 2LL * INF ? "YES" : "NO") << '\n';
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

