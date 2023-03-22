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

vector<string> generate(int k) {
    if (k == 0) return {{}};
    vector<string> res;
    for (int i = 1; i <= min(9, k); i++) {
        vector<string> tmp = generate(k - i);
        for (auto &s : tmp) res.pb(s + (char)(i + '0'));
    }
    return res;
}
bool check(const string& s, int x) {
    for (int i = 0; i < sz(s); i++) {
        int sum = 0;
        for (int j = i; j < sz(s); j++) {
            sum += s[j] - '0';
            if (x % sum == 0 && x > sum) return false;
        }
    }
    return true;
}
vector<string> x_prime(int x) {
    vector<string> res = generate(x), ans;
    for (auto &s : res) if (check(s, x)) ans.pb(s);
    return ans;
}

/**
 * Description: Deterministic Finite Automaton of a dictionary of strings
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Light/ACfixed.h
 * Verification: 
 * Time Complexity: O(\sigma |S|)
 */

struct AhoCorasick {
    static const int ALPHA = 9;
    struct Node {
        ar<int, ALPHA> to;
        int link;
        bool exit;
    };
    vector<Node> d{{}};
    int insert(const string& s) {
        int now = 0;
        for (auto &ch : s) {
            int c = ch - '1';
            if (!d[now].to[c]) d[now].to[c] = sz(d), d.pb({});
            now = d[now].to[c];
        }
        d[now].exit = 1;
        return now;
    }
    void init() {
        d[0].link = -1;
        queue<int> q;
        q.push(0);
        while (sz(q)) {
            int u = q.front(); q.pop();
            for (int c = 0; c < ALPHA; c++) {
                int v = d[u].to[c]; 
                if (!v) continue;
                d[v].link = d[u].link == -1 ? 0 : d[d[u].link].to[c];
                q.push(v);
            }
            if (u) {
                d[u].exit |= d[d[u].link].exit;
                for (int c = 0; c < ALPHA; c++) {
                    if (!d[u].to[c]) d[u].to[c] = d[d[u].link].to[c];
                }
            }
        }
    }
};

int dp[1111][5111];

void solve() {
    AhoCorasick aho;
    string s;
    int x;
    cin >> s >> x;
    vector<string> xprime = x_prime(x);
    // dbg(generate(8));
    dbg(xprime);
    for (auto &s : xprime) aho.insert(s);
    aho.init();
    int m = sz(aho.d);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < sz(s); i++) {
        for (int v = 0; v < m; v++) {
            if (aho.d[v].exit || dp[i][v] == 0x3f3f3f3f) continue;
            dbg(dp[i][v], i, v);
            int nxt = s[i] - '1';
            int pos = aho.d[v].to[nxt];
            ckmin(dp[i + 1][v], dp[i][v] + 1);
            if (!aho.d[pos].exit) ckmin(dp[i + 1][pos], dp[i][v]);
        }
    }
    cout << *min_element(dp[sz(s)], dp[sz(s)] + m) << '\n';
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

