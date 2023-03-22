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

struct AC {
    struct Node {
        ar<int, 3> to;
        int link;
        int sum;
    };
    vector<Node> d{{}};
    void insert(const string& s, int score) {
        int now = 0;
        for (auto &ch : s) {
            int nxt = ch - 'A';
            if (!d[now].to[nxt]) d[now].to[nxt] = sz(d), d.pb({}); 
            now = d[now].to[nxt];
        }
        d[now].sum += score;
    }
    void init() {
        d[0].link = -1;
        queue<int> q;
        q.push(0);
        while (sz(q)) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 3; i++) {
                int v = d[u].to[i];
                if (!v) continue;
                d[v].link = (d[u].link == -1 ? 0 : d[d[u].link].to[i]);
                q.push(v);
            }
            if (u) {
                d[u].sum += d[d[u].link].sum;
                dbg(u, d[u].sum);
                for (int i = 0; i < 3; i++) {
                    if (!d[u].to[i]) d[u].to[i] = d[d[u].link].to[i];
                }
            }
        }
    }
};

void solve() {
    int N, K;
    cin >> N >> K;
    AC aho;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        aho.insert(s, 1);
    }
    aho.init();
    int M = sz(aho.d);
    vector<vi> dp(K + 1, vi(M, -INF));
    dp[0][0] = 0;
    for (int len = 0; len < K; len++) {
        for (int v = 0; v < M; v++) {
            if (dp[len][v] == -INF) continue;
            for (int i = 0; i < 3; i++) {
                int nxt = aho.d[v].to[i];
                if (aho.d[nxt].sum) dbg(aho.d[nxt].sum);
                ckmax(dp[len + 1][nxt], dp[len][v] + aho.d[nxt].sum);
            }
        }
    }
    dbg(dp);
    cout << *max_element(all(dp[K])) << '\n';
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

