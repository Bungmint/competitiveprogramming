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
 * Description: Deterministic Finite Automaton of a dictionary of strings
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Light/ACfixed.h
 * Verification: 
 * Time Complexity: O(\sigma |S|)
 */

struct AhoCorasick {
    static const int ALPHA = 26;
    struct Node {
        ar<int, 26> to;
        int link;
		int cnt_exit{};
    };
    vector<Node> d{{}};
    int insert(const string& s) {
        int now = 0;
        for (auto &ch : s) {
            int c = ch - 'a';
            if (!d[now].to[c]) d[now].to[c] = sz(d), d.pb({});
            now = d[now].to[c];
        }
		d[now].cnt_exit++;
        return now;
    }
    void init() {
        d[0].link = -1;
        queue<int> q;
        q.push(0);
        while (sz(q)) {
            int u = q.front(); q.pop();
			if (u) d[u].cnt_exit += d[d[u].link].cnt_exit;
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

void solve() {
	string t; cin >> t;
	vector<vi> ret(2, vi(sz(t)));
	int N; cin >> N;
	vector<string> str(N);
	for (auto &s : str) cin >> s;
	for (int iter = 0; iter < 2; iter++) {
		AhoCorasick aho;
		for (int i = 0; i < N; i++) aho.insert(str[i]);
		aho.init();
		int state = 0;
		// traverse the automaton
		for (int i = 0; i < sz(t); i++) {
			state = aho.d[state].to[t[i] - 'a'];
			ret[iter][i] = aho.d[state].cnt_exit;
		}
		for (int i = 0; i < N; i++) reverse(all(str[i]));
		reverse(all(t));
	}
	reverse(all(ret[1]));
	ll ans{};
	for (int i = 0; i < sz(t) - 1; i++) {
		ans += 1LL*ret[0][i]*ret[1][i + 1];
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
