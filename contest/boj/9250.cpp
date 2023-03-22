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



struct ACAutomaton {
    struct Node {
        ar<int, 26> to;
        int exit;
        int link;
        Node() { to = ar<int, 26>(); exit = -1; }
    };
    vector<Node> d{{}};
    int insert(const string& s) {
        int now = 0;
        dbg(s);
        for (auto &ch : s) {
            int nxt = ch - 'a'; 
            if (!d[now].to[nxt]) d[now].to[nxt] = sz(d), d.pb({});
            now = d[now].to[nxt];
            dbg(now, nxt);
        }
        d[now].exit = now;
        return now;
    }
    void init() {
        d[0].link = -1;
        queue<int> q;
        q.push(0);
        while (sz(q)) {
            int u = q.front();
            dbg(u);
            q.pop();
            for (int i = 0; i < 26; i++) {
                int v = d[u].to[i];
                if (!v) continue;
                d[v].link = (d[u].link == -1 ? 0 : d[d[u].link].to[i]);
                q.push(v); 
            }
            if (u) {
                if (d[u].exit == -1) d[u].exit = d[d[u].link].exit;
                for (int i = 0; i < 26; i++) {
                    if (!d[u].to[i]) d[u].to[i] = d[d[u].link].to[i];
                }
            }
        }
    }
};

void solve() {
    int N;
    cin >> N;
    ACAutomaton aho;
    vector<string> S(N);
    for (auto &s : S) cin >> s, aho.insert(s);
    aho.init();
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        string s;
        cin >> s;
        int now = 0;
        bool has_exit = 0;
        for (auto &ch : s) {
            now = aho.d[now].to[ch - 'a'];
            has_exit |= aho.d[now].exit != -1;
        }
        cout << (has_exit ? "YES" : "NO") << '\n';
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

