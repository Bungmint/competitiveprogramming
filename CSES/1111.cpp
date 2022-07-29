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
 * Description: Finds the length of the longest palindrome centered at i
 * Source: https://cp-algorithms.com/string/manacher.html#working-with-parities
 * Verification: 
 * Time Complexity: O(|S|)
 */

vi manacher(const string& s) {
    string t = "@";
    for (auto &ch : s)  t += ch, t += '#';
    t.back() = '^';
    vi ret(sz(t) - 1);
    for (int i = 1, l = 1, r = 1; i < sz(t) - 1; i++) {
        ret[i] = max(0, min(r - i, ret[l + (r - i)]));
        while (t[i - ret[i]] == t[i + ret[i]]) ret[i]++;
        if (i + ret[i] > r) l = i - ret[i], r = i + ret[i];
    }
	ret.erase(ret.begin());
	for (int i = 0; i < sz(ret); i++) {
		if (i % 2 == ret[i] % 2) ret[i]--;
	}
	return ret;
}

void solve() {
	string s;
	cin >> s;
	vi t = manacher(s);
	int it = max_element(all(t)) - t.begin();
	if (it & 1) {
		cout << s.substr((it+1)/2 - t[it]/2, t[it]) << '\n';
	}else{
		cout << s.substr(it/2 - t[it]/2, t[it]) << '\n';
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
