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

int ask(int i, int j) {
	cout << "? " << i << ' ' << j << endl;
	int x;
	cin >> x;
	return x;
}
void answer(vi& ans) {
	cout << '!';
	for (auto &e : ans) cout << ' ' << e;
	cout << endl;
}

void solve() {
	vi a{4, 8, 15, 16, 23, 42};
	map<int, pii> ret;
	ll prod{1};
	for (auto &e : a) prod *= e;
	dbg(prod);
	for (int i = 0; i < 6; i++) 
		for (int j = 0; j < i; j++) {
		ret[a[i]*a[j]] = {j, i};
	}
	vi ans(6);
	auto [x, y] = ret[ask(1, 2)];
	auto [z, w] = ret[ask(3, 4)];
	auto [c, d] = ret[ask(1, 3)];
	ans[4] = sqrt(ask(5, 5));
	ans[5] = prod/(a[x]*a[y]*a[z]*a[w]*ans[4]);
	if (x == c || x == d) {
		ans[0] = a[x];
		ans[1] = a[y];
	}else{
		ans[0] = a[y];
		ans[1] = a[x];
	}
	if (z == c || z == d) {
		ans[2] = a[z];
		ans[3] = a[w];
	}else{
		ans[2] = a[w];
		ans[3] = a[z];
	}
	answer(ans);
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
