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

constexpr int MOD = 1e9 + 7;

int add(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}
int mul(int a, int b) {
    return 1LL * a * b % MOD;
}

template <typename T, int SZ>
using Matrix = ar<ar<T, SZ>, SZ>; 

template <typename T, int SZ> 
Matrix<T, SZ> identity() {
    Matrix<T, SZ> res{};
    for (int i = 0; i < SZ; i++) {
        res[i][i] = 1;
    }
    return res;
}

template <typename T, int SZ>
Matrix<T, SZ> mul(const Matrix<T, SZ>& A, const Matrix<T, SZ>& B) {
    Matrix<T, SZ> res{};
    for (int k = 0; k < SZ; k++) {
        for (int i = 0; i < SZ; i++) {
            for (int j = 0; j < SZ; j++) {
                res[i][j] = add(res[i][j], mul(A[i][k], B[k][j]));
            }
        }
    }
    return res;
}

template <typename T, int SZ>
Matrix<T, SZ> bin_pow(const Matrix<T, SZ>& A, int n) {
    if (n == 1) {
        return A;
    }    
    Matrix<T, SZ> mid = bin_pow<T, SZ>(A, n / 2);
    return (n & 1 ? mul<T, SZ>(mul<T, SZ>(mid, mid), A): mul<T, SZ>(mid, mid));
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    Matrix<int, 100> adj{};
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v, u--, v--;
        adj[u][v] += 1;        
    }
    cout << bin_pow<int, 100>(adj, k)[0][n - 1] << '\n';
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

