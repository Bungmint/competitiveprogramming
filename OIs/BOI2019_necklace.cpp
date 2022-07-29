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


/**
 * Description: Knuth-Morris-Pratt Algorithm
 * Source: Academic paper
 * Verification: CSES 1753 - https://cses.fi/problemset/task/1753
 * Time complexity - O(n), n = length of the string
 */

vi kmp(const string& s) {
    int n = sz(s);
    vi pi(n);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}


void solve() {
	string s, t;
	cin >> s >> t;
	pii ans{};
	int global_max{};
	for (int iter = 0; iter < 2; iter++, reverse(all(t))) {
		pii cur{};
		int cur_max{};
		for (int i = 0; i < sz(s); i++) {
			string r(s.begin(), s.begin() + i + 1);
			reverse(all(r));
			reverse(all(t));
			r += '#';
			r += t;
			vi pi_a = kmp(r);
			dbg("0~i:", r);
			string().swap(r);
			reverse(all(t));
			r = {s.begin() + i + 1, s.end()};
			r += '#';
			r += t;
			vi pi_b = kmp(r);
			dbg("i+1~n-1:", r);
			for (int j = 0; j < sz(t); j++) {
				int blen = pi_b[sz(s)-i+j];
				int alen = pi_a[sz(t)+i-j];
				if (ckmax(cur_max, alen+blen)) {
					dbg(i, j, alen, blen, iter);
					cur = {i-alen+1, j-blen+1};
				}
			}
			string().swap(r);
			vi().swap(pi_a);
			vi().swap(pi_b);
		}
		if (ckmax(global_max, cur_max))	{
			if (iter == 0) ans = cur;
			else {
				dbg(cur, sz(t));
				// int tt = sz(t) - 1 - cur.se;
				cur.se += cur_max - 1;
				cur.se = sz(t) - 1 - cur.se;
				ans = cur;
			}
		}
	}
	cout << global_max << '\n';
	cout << ans.fi << ' ' << ans.se << '\n';
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
