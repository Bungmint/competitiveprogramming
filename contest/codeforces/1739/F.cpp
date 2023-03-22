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
 * Description: Deterministic Finite Automaton of a dictionary of strings
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Light/ACfixed.h
 * Verification: 
 * Time Complexity: O(\sigma |S|)
 */

struct AhoCorasick {
    static const int ALPHA = 12;
    struct Node {
        ar<int, ALPHA> to;
        int link;
        int score = 0;
    };
    vector<Node> d{{}};
    int insert(const string& s, int score) {
        int now = 0;
        for (auto &ch : s) {
            int c = ch - 'a';
            if (!d[now].to[c]) d[now].to[c] = sz(d), d.pb({});
            now = d[now].to[c];
        }
        d[now].score += score;
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
                d[u].score += d[d[u].link].score;
                for (int c = 0; c < ALPHA; c++) {
                    if (!d[u].to[c]) d[u].to[c] = d[d[u].link].to[c];
                }
            }
        }
    }
};
bool convert(string& s) {
    vi deg(12);
    bool g[12][12]{};
    for (int i = 0; i < sz(s) - 1; i++) {
        int a = s[i] - 'a', b = s[i + 1] - 'a';
        if (g[a][b]) continue;
        g[a][b] = g[b][a] = 1;
        deg[a]++, deg[b]++;
    }
    if (*max_element(all(deg)) >= 3) return false;
    string res;
    vi vis(12);
    int st = -1;
    for (int i = 0; i < 12; i++) {
        if (deg[i] == 1) {
            st = i;
            break;
        }
    }
    if (st == -1) return false;
    queue<int> q;
    q.push(st);
    while (sz(q)) {
        int u = q.front();
        q.pop();
        res += (char)('a' + u);
        vis[u] = 1;
        for (int i = 0; i < 12; i++) {
            if (g[u][i] && !vis[i]) {
                q.push(i);
            }
        }
    }
    s = res;
    return true;
}

void solve() {
    AhoCorasick aho;	
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int c;
        string s;
        cin >> c >> s;
        if (convert(s)) aho.insert(s, c), reverse(all(s)), aho.insert(s, c);
        dbg(s);
    }
    aho.init();
    int m = sz(aho.d);
    vector<vi> dp(1 << 12, vi(m, -INF)); 
    vector<vpi> par(1 << 12, vpi(m, make_pair(-1, -1)));
    dp[0][0] = 0;
    for (int mask = 0; mask < (1 << 12); mask++) {
        for (int i = 0; i < 12; i++) {
            if (mask >> i & 1) continue;
            for (int v = 0; v < m; v++) {
                if (dp[mask][v] == -INF) continue;
                int nxt = aho.d[v].to[i];
                if (ckmax(dp[mask | (1 << i)][nxt], dp[mask][v] + aho.d[nxt].score)) {
                    par[mask | (1 << i)][nxt] = {mask, v};
                }
            }
        }
    }
    int mask = (1 << 12) - 1;
    int v = max_element(all(dp[(1 << 12) - 1])) - dp[(1 << 12) - 1].begin();
    string res;
    while (mask) {
        auto [pmask, pv] = par[mask][v];
        int diff = __builtin_ctz(pmask ^ mask);
        res += (char)('a' + diff);
        mask = pmask, v = pv;
    }
    reverse(all(res));
    cout << res << '\n';
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

