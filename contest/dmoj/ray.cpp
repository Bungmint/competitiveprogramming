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

using T = ll;
using Matrix = ar<ar<T, 100>, 100>;
using Vector = ar<T, 100>;

Matrix createMatrix() {
    Matrix mat{};
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            mat[i][j] = LINF;
        }
    }
    return mat;
}
Vector createVector(int u = -1) {
    Vector vec{};
    for (int i = 0; i < 100; i++) vec[i] = LINF;
    if (u != -1) vec[u] = 0;
    return vec;
}
Matrix operator*(const Matrix& A, const Matrix& B) {
    Matrix C = createMatrix();
    for (int k = 0; k < 100; k++) {
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                ckmin(C[i][j], A[i][k] + B[k][j]);
            }
        }
    }
    return C;
}
Vector operator*(const Matrix& A, const Vector& V) {
    Vector res = createVector();
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ckmin(res[i], A[j][i] + V[j]);
        }
    }
    return res;
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    Matrix adj = createMatrix();
    vector<Matrix> bit(30);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;
        ckmin(adj[u][v], w);
    }
    bit[0] = adj;
    dbg(bit[0]);
    for (int i = 1; i < 30; i++) {
        bit[i] = bit[i - 1] * bit[i - 1];
    }
    for (int i = 0; i < q; i++) {
        int u, v, k;
        cin >> u >> v >> k, u--, v--;
        Vector vec = createVector(u);
        for (int j = 0; j < 30; j++) {
            if (k >> j & 1) vec = bit[j] * vec;
        }
        cout << (vec[v] == LINF ? -1 : vec[v]) << '\n';
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

