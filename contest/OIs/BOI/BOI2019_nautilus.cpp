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

/**
 * Solution: O(RCM) dp optimized to O(RCM/w) using bitsets
 */ 

array<bitset<500>, 500> state, nxt, init_map;
int r, c, m;

void update(char ch) {
	nxt = {};
	switch (ch) {
		case 'N':
			for (int i = 1; i < r; i++) {
				swap(nxt[i-1], state[i]);
			}
			break;
		case 'S':
			for (int i = 0; i < r-1; i++) {
				swap(nxt[i+1], state[i]);
			}
			break;
		case 'E':
			for (int i = 0; i < r; i++) {
				swap(nxt[i], state[i]);
				nxt[i] <<= 1;
			}
			break;
		case 'W':
			for (int i = 0; i < r; i++) {
				swap(nxt[i], state[i]);
				nxt[i] >>= 1;
			}
			break;
		case '?':
			for (int i = 0; i < r; i++) {
				if (i) nxt[i-1] |= state[i];
				if (i < r-1) nxt[i+1] |= state[i];
				nxt[i] |= (state[i] << 1);
				nxt[i] |= (state[i] >> 1);
			}
			break;
	}
	swap(nxt, state);
	for (int i = 0; i < r; i++) {
		state[i] &= init_map[i];
	}
}
int calc() {
	int res{};
	for (int i = 0; i < r; i++) {
		res += state[i].count();
	}
	return res;
}

void solve() {
	cin >> r >> c >> m;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			char ch; cin >> ch;
			if (ch == '.') init_map[i][j] = 1;
		}
	}
	string s;
	cin >> s;
	state = init_map;
	for (auto &ch : s) {
		update(ch);
	}
	cout << calc() << '\n';
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
