// Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

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

// TODO: Test Imp
/*
 * Basic Modular Operations assuming 0 <= a, b < MOD
 * Source: Own
 * Verification:
 * Time complexity: O(log(min(a, b))) for modular inverse and mod_pow, other operations are O(1)
**/
inline namespace ModUtil {
    int MOD{};
    int add(int a, const int& b) { 
        a += b;
        if (a >= MOD) a -= MOD;
        return a;
    }
    int mul(const int& a, const int& b) { return 1LL * a * b % MOD; }
    int sub(int a, const int& b) {
        a -= b;
        if (a < 0) a += MOD;
        return a;
    }
    int mod_pow(int a, int b) {
        int r = 1;
        while (b) {
            if (b & 1) r = mul(r, a);
            a = mul(a, a);
            b >>= 1;
        }
        return r;
    }
    template <typename T>
    T inverse(T a, T b) { // Assumes 0 < a < b, could overflow if using 64bit int
        return a > 1 ? b - inverse(b % a, a) * b / a : 1;
    }
}


void solve() {
	while (cin >> MOD) {
		MOD *= 9;
		int r = 1;
		for (int i = 1; i <= 11110; i++) {
			r = mul(r, 10);
			int cur = sub(r, 1);
			if (cur == 0) {
				cout << i << '\n';
				break;
			}
		}
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	// cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
