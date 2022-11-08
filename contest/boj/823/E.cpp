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
	int N, L, Q;
	cin >> N >> L >> Q;
	int G = L;
	map<int, int> single;
	map<int, multiset<int>> rs;
	int cnt = 0;
	ll sum{};
	for (int i = 0; i < Q; i++) {
		int ty, x, t;
		cin >> ty >> x;
		if (ty == 1) {
			cin >> t;
			if (single.count(x)) {
				bool was_bad = sz(rs[x % G]) && *rs[x % G].begin() != *--rs[x % G].end();
				rs[x % G].erase(rs[x % G].find(single[x]));
				if (was_bad && *rs[x % G].begin() == *--rs[x % G].end()) cnt--;
				if (rs[x % G].find(single[x]) == rs[x % G].end()) sum -= single[x];
				if (sz(rs[x % G]) == 0) rs.erase(x % G);
			}
			single[x] = t;
			x %= G;
			if (!rs.count(x)) {
				rs[x].insert(t);
				sum += t;
			}else{
				if (rs[x].find(t) == rs[x].end()) sum += t;
				bool was_bad = sz(rs[x]) && *rs[x].begin() != *--rs[x].end();
				rs[x].insert(t);
				if (!was_bad && *rs[x].begin() != *--rs[x].end()) cnt++;
			}
		}else{
			int er = single[x];
			single.erase(x);
			x %= G;
			bool was_bad = sz(rs[x]) && (*rs[x].begin() != *--rs[x].end());
			rs[x].erase(rs[x].find(er));
			if (was_bad && *rs[x].begin() == *--rs[x].end()) cnt--;
			if (rs[x].find(er) == rs[x].end()) sum -= er;
			if (sz(rs[x]) == 0) rs.erase(x);
		}
		if (cnt == 0) cout << "YES" << ' ' << sum << '\n';
		else cout << "NO\n";
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
