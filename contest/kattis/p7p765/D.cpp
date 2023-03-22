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

int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int inv_5[] = {0, 1, 3, 2, 4};
int inv_73[73];
int N, M;

void precalc() {
    for (int i = 1; i < 73; i++) {
        for (int j = 1; j < 73; j++) {
            if ((i * j) % 73 == 1) {
                inv_73[i] = j;
            }
        }
    } 
}
int convert_to_365(int day, int month) {
    for (int i = 0; i < month - 1; i++) {
        day += months[i];
    }
    return day;
}
int gaussian_elimination_5(vector<vi>& A, vi& b, vi& x) {
    int nr = 0, nc = 0, na = 0;
    int rank = 0;
    vi col(sz(A[0])); 
    iota(all(col), 0);
    for (int i = 0; i < N; i++) {
        na = 0;
        for (int j = i; j < N; j++) {
            for (int k = i; k < M; k++) {
                if (!na && A[j][k]) {
                    na = A[j][k];
                    nr = j;
                    nc = k; }
            } 
            if (na) break;
        }
        if (!na) {
            for (int j = i; j < N; j++) {
                if (b[j]) return -1;
            }
            break;
        }
        swap(A[nr], A[i]);
        swap(b[nr], b[i]);
        swap(col[nc], col[i]);
        for (int j = 0; j < N; j++) swap(A[j][nc], A[j][i]);
        dbg(na);
        const int INV = inv_5[na];
        for (int j = i + 1; j < N; j++) {
            const int MUL = INV * A[j][i] % 5;
            b[j] = (b[j] - MUL * b[i]) % 5;
            if (b[j] < 0) b[j] += 5;
            for (int k = i + 1; k < M; k++) {
                A[j][k] = (A[j][k] - MUL * A[i][k]) % 5;
                if (A[j][k] < 0) A[j][k] += 5;
            } 
        }
        rank++;
    }
    x.assign(M, 0);   
    for (int i = rank; i--; ) {
        (b[i] *= inv_5[A[i][i]]) %= 5;
        x[col[i]] = b[i];
        for (int j = 0; j < i; j++) {
            (b[j] -= A[j][i] * b[i]) %= 5;
            if (b[j] < 0) b[j] += 5;
        }
    }
    return rank;
}
int gaussian_elimination_73(vector<vi>& A, vi& b, vi& x) {
    int nr = 0, nc = 0, na = 0;
    int rank = 0;
    vi col(sz(A[0])); 
    iota(all(col), 0);
    for (int i = 0; i < N; i++) {
        na = 0;
        for (int j = i; j < N; j++) {
            for (int k = i; k < M; k++) {
                if (!na && A[j][k]) {
                    na = A[j][k];
                    nr = j;
                    nc = k;
                }
            } 
            if (na) break;
        }
        if (!na) {
            for (int j = i; j < N; j++) {
                if (b[j]) return -1;
            }
            break;
        }
        swap(A[nr], A[i]);
        swap(b[nr], b[i]);
        swap(col[nc], col[i]);
        for (int j = 0; j < N; j++) swap(A[j][nc], A[j][i]);
        const int INV = inv_73[na];
        for (int j = i + 1; j < N; j++) {
            const int MUL = INV * A[j][i] % 73;
            b[j] = (b[j] - MUL * b[i]) % 73;
            if (b[j] < 0) b[j] += 73;
            for (int k = i + 1; k < M; k++) {
                A[j][k] = (A[j][k] - MUL * A[i][k]) % 73;
                if (A[j][k] < 0) A[j][k] += 73;
            } 
        }
        rank++;
    }
    x.assign(M, 0);   
    for (int i = rank; i--; ) {
        (b[i] *= inv_73[A[i][i]]) %= 73;
        x[col[i]] = b[i];
        for (int j = 0; j < i; j++) {
            (b[j] -= A[j][i] * b[i]) %= 73;
            if (b[j] < 0) b[j] += 73;
        }
    }
    return rank;
}


void solve() {
    precalc();
    cin >> N >> M;
    vector<vi> A(N, vi(M));
    vi B(N);
    for (int i = 0; i < N; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int duration = (convert_to_365(c, d) - convert_to_365(a, b) + 365) % 365;
        for (int j = 0; j < M; j++) {
            cin >> A[i][j];
        }
        B[i] = duration; 
    }
    vector<vi> A5 = A, A73 = A;    
    vi B5 = B, B73 = B;
    vi x5, x73;
    for (auto &v : A5) for (auto &e : v) e %= 5;
    for (auto &e : B5) e %= 5;
    for (auto &v : A73) for (auto &e : v) e %= 73;
    for (auto &e : B73) e %= 73;
    if (gaussian_elimination_5(A5, B5, x5) == -1 || gaussian_elimination_73(A73, B73, x73) == -1) {
        cout << -1 << '\n';
        return;
    }
    dbg(A, B);
    dbg(x5, x73);
    for (int i = 0; i < M; i++) {
        int m = (x73[i] - x5[i] + 73) * inv_73[5] % 73;
        int ans = (5 * m + x5[i]) % 365;
        cout << (ans == 0 ? 365 : ans) << " \n"[i == M - 1];
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

