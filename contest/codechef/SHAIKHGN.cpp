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

const int MAX_N = 500;
using Matrix = array<bitset<MAX_N>, MAX_N>;
using Vector = bitset<MAX_N>;
Matrix ID{};
Matrix f[30];

Matrix transpose(const Matrix& mat) {
	Matrix r{};
	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_N; j++) {
			r[i][j] = mat[j][i];
		}
	}
	return r;
}
Matrix operator*(const Matrix& a, const Matrix& b) {
	Matrix res{};
	Matrix trans_b = transpose(b);
	for (int r = 0; r < MAX_N; r++) {
		for (int c = 0; c < MAX_N; c++) {
			res[r][c] = (a[r] & trans_b[c]).any();
		}
	}
	return res;
}
Matrix identity() {
	Matrix r{};
	for (int i = 0; i < MAX_N; i++) {
		r[i][i] = 1;
	}
	return r;
}
Vector operator*(const Vector& v, const Matrix& m) {
	Vector res{};
	for (int i = 0; i < MAX_N; i++) {
		if (v[i] == 1) res |= m[i]; 
	}
	return res;
}

void solve() {
	Matrix adj{};
	ID = identity();
	int N, M, K, x;
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> x;
			adj[i][j] = x;
		}
	}
	f[0] = adj;
	for (int L = 1; L < 30; L++) {
		f[L] = f[L-1] * f[L-1];
	}
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> K >> x;
		x--;
		Vector ret{};
		ret[x] = 1;
		for (int L = 0; L < 30; L++) {
			if (K>>L & 1) ret = ret * f[L];
		}
		int cnt = ret.count();
		cout << cnt << '\n';
		for (int j = 0; j < N; j++) {
			if (ret[j]) cout << j + 1 << ' ';
		}
		if (!cnt) cout << -1;
		cout << '\n';
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
