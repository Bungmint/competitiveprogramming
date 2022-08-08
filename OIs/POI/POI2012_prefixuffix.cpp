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

constexpr int NAX = 2e6+100;
int pal[NAX], pi[NAX];
bool good[NAX];
/**
 * Description: Finds the length of the longest palindrome centered at i
 * Source: https://cp-algorithms.com/string/manacher.html#working-with-parities
 * Verification: 
 * Time Complexity: O(|S|)
 */

void manacher(const string& s) {
    string t = "@";
    for (auto &ch : s)  t += ch, t += '#';
    t.back() = '^';
    for (int i = 1, l = 1, r = 1; i < sz(t) - 1; i++) {
        pal[i] = max(0, min(r - i, pal[l + (r - i)]));
        while (t[i - pal[i]] == t[i + pal[i]]) pal[i]++;
        if (i + pal[i] > r) l = i - pal[i], r = i + pal[i];
    }
	for (int i = 0; i < sz(t) - 2; i++) {
		pal[i] = pal[i+1]; // shift the result
		if (i % 2 == pal[i] % 2) pal[i]--;
	}
}

/**
 * Description: Knuth-Morris-Pratt Algorithm
 * Source: Academic paper
 * Verification: CSES 1753 - https://cses.fi/problemset/task/1753
 * Time complexity - O(n), n = length of the string
 */

void kmp(const string& s) {
    int n = sz(s);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
}

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	if (n & 1) {
		// remove the middle character
		string new_s;
		new_s.reserve(n);
		for (int i = 0; i < n; i++) {
			if (i == n/2) continue;
			new_s += s[i];
		}
		swap(new_s, s);
		string().swap(new_s);
		n--;
	}
	int k = n/2;
	kmp(s);
	string t; t.resize(n);
	for (int i = 0; i < k; i++) {
		t[2*i] = s[i];
	}
	for (int i = k; i < 2*k; i++) {
		t[2*(n-1-i) + 1] = s[i];
	}
	manacher(t);
	string().swap(s), string().swap(t);
	int ans{};
	for (int len = pi[n - 1]; len > 0; len = pi[len - 1]) {
		if (len > k) continue;
		good[len] = 1;
		dbg(len);
		ckmax(ans, len);
	}
	auto check_pal = [&](int l, int r) -> bool {
		if (((r-l+1) & 1) || r >= n) return 0;
		int id = l + r;
		return pal[id] >= r - l + 1;
	};
	for (int i = n - 2, p = 0; i >= 0; i--) {
		p += 2;
		while (p && !check_pal(i, i + p - 1)) {
			p -= 2;
		}
		if (i && (i % 2 == 0) && good[i/2]) {
			ckmax(ans, i/2 + p/2);
		}
	}
	cout << ans << '\n';
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
