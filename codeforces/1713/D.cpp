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

int ask(int a, int b) {
	cout << "? " << a << ' ' << b << endl;
	int x; cin >> x;
	return x;
}
void answer(int a) {
	cout << "! " << a << endl;
}
// 1-a, 2-b, 0-a==b
void solve() {
	int n; cin >> n;
	if (n == 1) {
		if (ask(1, 2) == 1) answer(1);
		else answer(2);
		return;
	}
	int tot = 1 << n;
	vi potential(tot);
	iota(all(potential), 1);
	while (sz(potential) >= 4) {
		vi nxt;
		for (int i = 0; i < sz(potential); i += 4) {
			dbg(i, sz(potential));
			int a = potential[i], b = potential[i + 1];
			int c = potential[i + 2], d = potential[i + 3];
			int t = ask(a, c);
			if (t == 1) {
				t = ask(a, d);
				if (t == 1) nxt.pb(a);
				else nxt.pb(d);
			}else if (t == 2) {
				t = ask(b, c);
				if (t == 1) nxt.pb(b);
				else nxt.pb(c);
			}else{
				t = ask(b, d);
				assert(!!t);
				if (t == 1) nxt.pb(b);
				else nxt.pb(d);
			}
		}
		swap(potential, nxt);
	}
	if (sz(potential) == 2) {
		auto x = potential[0], y = potential[1];
		int t = ask(x, y);
		if (t == 2) swap(potential[0], potential[1]);
	}
	answer(potential[0]);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
