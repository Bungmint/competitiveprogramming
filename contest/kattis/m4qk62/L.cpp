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

vector<string> make_vector(const string& s) {
    vector<string> res(1);
    for (auto &ch : s) {
        if (ch == ' ') res.pb({});
        else res.back().pb(ch);
    }
    return res;
}

void solve() {
    string line1, line2;
    getline(cin, line1);
    getline(cin, line2);
    vector<string> a = make_vector(line1), b = make_vector(line2);
    if (sz(a) != sz(b)) {
        cout << "-" << '\n';
        return;
    }
    int n = sz(a);
    map<string, vector<string>> g;
    map<string, string> vis;
    for (auto &e : a) if (e[0] == '<') e.pb('a');
    for (auto &e : b) if (e[0] == '<') e.pb('b');
    dbg(n, a, b);
    for (int i = 0; i < n; i++) {
        g[a[i]].pb(b[i]); 
        g[b[i]].pb(a[i]);
    }
    vector<string> cc;
    auto dfs = y_combinator([&](auto self, string u) -> void {
                                vis[u] = "";
                                for (auto &v : g[u]) {
                                    if (!vis.count(v)) {
                                        self(v);
                                    }
                                }
                                cc.pb(u);
                            });
    for (int i = 0; i < n; i++) {
        if (!vis.count(a[i])) {
            cc.clear();
            dfs(a[i]); 
            vector<string> not_pattern;
            for (auto &e : cc) {
                if (e[0] != '<') {
                    not_pattern.pb(e);
                }
            }
            bool ok = 1;
            for (auto &e : not_pattern) if (e != not_pattern[0]) ok = 0;
            if (!ok) {
                cout << '-' << '\n';
                return;
            }
            string res = (sz(not_pattern) ? not_pattern[0] : "a");
            for (auto &e : cc) vis[e] = res;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << vis[a[i]] << " \n"[i == n - 1];
    }
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	// cin.exceptions(cin.failbit);
	int testcase = 1;
	string s;
    getline(cin, s);
    testcase = stoi(s);
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

