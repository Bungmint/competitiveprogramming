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
#define eb emplace_back
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
 * Description: Trie supporting string insertion
 * Source: Folklore, Benq
 * Verification: https://oj.uz/problem/view/IOI08_printer
 * Time complexity: O(|S_i|) per insertion
 */

template <int SZ, int ALPHA>
struct TrieAlpha {
    int nxt[SZ][ALPHA], sz[SZ], num = 0;
    TrieAlpha() { memset(nxt, 0, sizeof(nxt)), memset(sz, 0, sizeof(sz)); }
    void insert(const string& s, int cnt = 1) {
        int now = 0; 
        for (int i = 0; i < sz(s); i++) {
            int c = s[i] - 'a';
            if (!nxt[now][c]) nxt[now][c] = ++num;
            now = nxt[now][c];
            sz[now] += cnt;
        }
    }
};

TrieAlpha<800000, 26> trie[2];

void solve() {
    int Q;
    cin >> Q;
    for (int iter = 0; iter < Q; iter++) {
        string op;
        cin >> op;
        if (op == "find") {
            string s;
            cin >> s;
            int n = sz(s);
            int pos_A = 0, pos_B = 0;
            int len_A = 0;
            bool ok = 1;
            ll ans = 0;
            vi aa;
            for (int i = 0; i < n; i++) {
                if (trie[0].nxt[pos_A][s[i] - 'a'] == 0) {
                    break;
                } 
                pos_A = trie[0].nxt[pos_A][s[i] - 'a'];
                aa.pb(pos_A);
            }
            len_A = sz(aa);
            ok &= len_A > 0;
            for (int i = 0; i < n - len_A && ok; i++) {
                if (trie[1].nxt[pos_B][s[n - 1 - i] - 'a'] == 0) {
                    ok = 0;
                    break;
                }
                pos_B = trie[1].nxt[pos_B][s[n - 1 - i] - 'a'];
            }
            for (int i = 0; i < len_A && ok; i++) {
                ans += trie[0].sz[pos_A] * trie[1].sz[pos_B]; 
                aa.pop_back();
                if (sz(aa) == 0) break;
                pos_A = aa.back();
                if (trie[1].nxt[pos_B][s[len_A - 1 - i] - 'a'] == 0) {
                    break;
                }
                pos_B = trie[1].nxt[pos_B][s[len_A - 1 - i] - 'a'];
            }

            cout << ans * ok << '\n';
        } else {
            char ch;
            string s;
            cin >> ch >> s;
            int x = ch - 'A';
            int fl = (op == "add" ? 1 : -1);
            if (x) reverse(all(s));
            trie[x].insert(s, fl);
        }
    }
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	// cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

