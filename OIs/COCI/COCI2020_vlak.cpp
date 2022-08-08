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

// TODO: Test imp
/**
 * Description: Trie supporting string insertion
 * Source: Folklore, Benq
 * Verification:
 * Time complexity: O(|S_i|) per insertion
 */

template <int SZ, int ALPHA>
struct TrieAlpha {
    int trie[SZ][ALPHA], sz[SZ][2], par[SZ], num;
	bool is_win[SZ][2];
    TrieAlpha() { memset(trie, 0, sizeof(trie)), memset(sz, 0, sizeof(sz)); }
    void insert(const string& s, bool fl) {
        int now = 0; sz[now][fl]++;
        for (int i = 0; i < sz(s); i++) {
            int c = s[i] - 'a';
            if (!trie[now][c]) trie[now][c] = ++num;
			par[trie[now][c]] = now;
            now = trie[now][c];
            sz[now][fl]++;
        }
    }
	int calc() {
		for (int now = num; now; now--) {
			is_win[now][0] &= !!sz[now][0];
			is_win[now][1] &= !!sz[now][1];
			int p = par[now];
			if (!is_win[now][0] && sz[now][1]) is_win[p][1] = 1;
			if (!is_win[now][1] && sz[now][0]) is_win[p][0] = 1;
		}
		return is_win[0][0];
	}
};

const string FIRST = "Nina", SECOND = "Emilija";
const int NAX = 2e5 + 100, ALPHA = 26;
TrieAlpha<NAX, ALPHA> trie;

void solve() {
	int n, m;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		trie.insert(s, 0);
	}
	cin >> m;
	for (int i = 0; i < m; i++) {
		string s; cin >> s;
		trie.insert(s, 1);
	}
	cout << (trie.calc() ? FIRST : SECOND) << '\n';
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
