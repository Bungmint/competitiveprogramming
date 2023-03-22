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
constexpr int MOD = 1000;

using Matrix = vector<vi>;

Matrix create_matrix(int r, int c) {
    return Matrix(r, vi(c));
}
Matrix Identity(int n) {
    Matrix res = create_matrix(n, n);
    for (int i = 0; i < n; i++) res[i][i] = 1;
    return res;
}
Matrix operator*(const Matrix& A, const Matrix& B) {
    assert(sz(A[0]) == sz(B));
    Matrix res = create_matrix(sz(A), sz(B[0]));
    for (int k = 0; k < sz(A[0]); k++) {
        for (int i = 0; i < sz(A); i++) {
            for (int j = 0; j < sz(B[0]); j++) {
                res[i][j] += A[i][k] * B[k][j];
                res[i][j] %= MOD;
            }
        }
    }
    return res;
}
Matrix& operator*=(Matrix& A, const Matrix& B) {
    A = A * B;
    return A;
}
Matrix bin_pow(Matrix& A, int b) {
    Matrix res = Identity(sz(A));     
    while (b) {
        if (b & 1) res *= A;
        A *= A;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n, b;
    cin >> n >> b;
    Matrix A = create_matrix(n, n);
    for (auto &v : A) for (auto &e : v) cin >> e;
    A = bin_pow(A, b);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << " \n"[j == n - 1];
        }
    }
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

