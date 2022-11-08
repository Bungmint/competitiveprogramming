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

void solve() {
	int n; cin >> n;
	vi a(n);
	vpi b(n);
	for (int i = 0; i < n; i++) {
		cin >> b[i].fi;
		b[i].se = i;
	}
	sort(all(b));
	for (int i = 0; i < n; i++) {
		vpi todo{b[i]};
		int lo = b[i].fi, cnt = 1;
		vi last{b[i].se};
		while (i + 1 < n && b[i + 1].fi <= b[i].fi + 1) {
			todo.pb(b[++i]);
			if (b[i].fi == lo) cnt++;
		}
		if (cnt % lo) {
			cout << -1 << '\n';
			return;
		}
		for (int j = 0; j < cnt; j += lo) {
			for (int k = 0; k < lo; k++) {
				auto [val, id] = todo[j + k];
				if (k == lo - 1) a[id] = todo[j].se;
				else a[id] = todo[j + k + 1].se;
			}
		}
		for (int j = cnt; j < sz(todo); j++) {
			auto [val, id] = todo[j];
			a[id] = last[val - lo - 1];
			if (sz(last) == val - lo) last.pb(id);
		}
	}
	for (int i = 0; i < n; i++) cout << a[i] + 1 << " \n"[i == n - 1];
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
