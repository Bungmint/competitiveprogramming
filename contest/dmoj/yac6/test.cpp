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

int sg[101][101][101][101];
int N, M;
int xum;

void precalc() {
    sg[1][1][1][1] = 0;
    for (int i = 1; i <= 100; i++) {
        for (int j = 1; j <= 100; j++) {
            for (int x = i; x >= 1; x--) {
                for (int y = j; y >= 1; y--) {
                	bitset<250> bs;
                    for (int k = x; k <= i - 1; k++) {
                        bs[sg[k][j][x][y]] = 1;
                    }
                    for (int k = i - x + 1; k <= i - 1; k++) {
                        bs[sg[k][j][k - i + x][y]] = 1;
                    }
                    for (int k = y; k <= j - 1; k++) {
                        bs[sg[i][k][x][y]] = 1;
                    }
                    for (int k = j - y + 1; k <= j - 1; k++) {
                        bs[sg[i][k][x][k - j + y]] = 1;
                    }
                    for (int k = 1; k <= 101; k++) {
                        if (x + k <= i) bs[sg[i][j][x + k][y]] = 1;
                        if (y + k <= j) bs[sg[i][j][x][y + k]] = 1;
                        if (x + k <= i && y + k <= j) bs[sg[i][j][x + k][y + k]] = 1;
                    }
                    for (int k = 0; k < 250; k++) {
                        if (!bs[k]) {
                            sg[i][j][x][y] = k;
                            break;
                        }
                    }
                }
            }
        }
    }
  	for (int i = 1; i <= 100; i++) cout << sg[i][i][1][1] << '\n';
}


int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
    precalc();
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}


