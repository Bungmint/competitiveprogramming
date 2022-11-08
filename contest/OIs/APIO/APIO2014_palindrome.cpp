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
 * Description: Trie-like structure storing distinct palindromes. Also called eertree
    * Edge from u to v with character c: S_v = "c" + S_u + "c"
    * Suffix links: Links to the longest nontrivial palindromic suffix
    * Root 1 = Length -1, Root 2 = Length 0
 * Source: http://adilet.org/blog/palindromic-tree/ 
 * Verification:
 * Time complexity: O(|S|)
 * Memory complexity: O(\sigma |S|) but can be reduced by not storing all edges
    * Check adamant's comment - https://codeforces.com/blog/entry/13959?#comment-313090
 */

struct Node {
    int to[26];
    int len;
    int suf_link;
	ll freq;
};

const int MAXN = 3e5+10;
Node tree[MAXN];
string s;
int ind, last_suf; 

bool add_char(int pos) {
    int c = s[pos] - 'a';
    int cur = last_suf, cur_len = 0;
    while (1) {
		dbg(cur, cur_len, s[pos]);
        cur_len = tree[cur].len;
        if (pos-1-cur_len >= 0 && s[pos-1-cur_len] == s[pos]) {
            break;
        }
        cur = tree[cur].suf_link;
    }
    if (tree[cur].to[c]) {
        last_suf = tree[cur].to[c];
		tree[last_suf].freq++;
        return false;
    }
    ind++;
    tree[cur].to[c] = ind;
    tree[ind].len = 2 + tree[cur].len;
	tree[ind].freq++;
	last_suf = ind;
    if (tree[ind].len == 1) {
        tree[ind].suf_link = 2;
        return true;
    }
    while (1) {
        cur = tree[cur].suf_link;
        cur_len = tree[cur].len;
        if (pos-1-cur_len >= 0 && s[pos-1-cur_len] == s[pos]) {
            tree[ind].suf_link = tree[cur].to[c];
            return true;
        }
    }
}

void init_tree() {
    tree[1].len = -1; tree[2].len = 0;
    tree[1].suf_link = tree[2].suf_link = 1;
    ind = last_suf = 2;
}

void solve() {
	cin >> s;
	int n = sz(s);
	init_tree();
	for (int i = 0; i < n; i++) {
		add_char(i);
	}
	ll ans{};
	for (int i = ind; i; i--) {
		tree[tree[i].suf_link].freq += tree[i].freq;
		ckmax(ans, tree[i].freq*tree[i].len);
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
