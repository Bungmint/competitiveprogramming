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
    static const int ALPHA = 26;
    struct Node {
        ar<int, ALPHA> to;
        int link;
    };
    vector<Node> d{{}};
    int insert(const string& s) {
        int now = 0;
        for (auto &ch : s) {
            int c = ch - 'a';
            if (!d[now].to[c]) d[now].to[c] = sz(d), d.pb({});
            now = d[now].to[c];
        }
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
                for (int c = 0; c < ALPHA; c++) {
                    if (!d[u].to[c]) d[u].to[c] = d[d[u].link].to[c];
                }
            }
        }
    }
};


/**
 * Description: Performs range prefix sum queries and point updates. lower_bound returns the first prefix sum >= v
 * Source: Own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=693
 * Time Complexity: O(log n) for query and update
 * 0-indexing
 */

template <typename T>
struct BIT {
	int N; vector<T> bit;
	BIT(int n) : N(n), bit(n + 1) {}
	void upd(int id, T v) {
		for (id++; id <= N; id += id & -id)
			bit[id] += v;
	}
	T query(int id) {
		T res = 0;
		for (id++; id > 0; id -= id & -id)
			res += bit[id];
		return res;
	}
	T query(int l, int r) {
		return l > r ? 0 : query(r) - query(l - 1);
	}
};

constexpr int MAXN = 1'111'111;
AhoCorasick aho;
vi g[MAXN];
int tin[MAXN], tout[MAXN], timer;
BIT<int> bit(MAXN);
int n, k, m;

void dfs(int u) {
    tin[u] = timer++;
    for (auto &e : g[u]) {
        dfs(e); 
    }
    tout[u] = timer - 1;
}
void init() {
    m = sz(aho.d); 
    for (int i = 1; i < m; i++) {
        g[aho.d[i].link].pb(i);
    }
    dfs(0);
}


void solve() {
    cin >> n >> k;
    vi ind(k), in(k);
    for (int i = 0; i < k; i++) {
        string s;
        cin >> s;
        ind[i] = aho.insert(s);
    }
    aho.init();
    init();
    for (int i = 0; i < k; i++) {
        int v = ind[i];
        bit.upd(tin[v], 1), bit.upd(tout[v] + 1, -1);
        in[i] = 1;
    }
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (s[0] == '+') {
            int id = stoi(string(1 + all(s))) - 1;
            int v = ind[id];
            if (!in[id]) {
                in[id] = 1;
                bit.upd(tin[v], 1); 
                bit.upd(tout[v] + 1, -1);
            }
        } else if (s[0] == '-') {
            int id = stoi(string(1 + all(s))) - 1;
            int v = ind[id];
            if (in[id]) {
                in[id] = 0;
                bit.upd(tin[v], -1); 
                bit.upd(tout[v] + 1, 1);
            }
        } else {
            s.erase(s.begin());
            int now = 0;
            int ans = 0;
            for (auto &ch : s) {
                now = aho.d[now].to[ch - 'a']; 
                ans += bit.query(tin[now]);
            }
            cout << ans << '\n';
        }
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

