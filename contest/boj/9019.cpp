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

void solve() {
    int n, m;
    cin >> n >> m;
    vi dist(10000, INF);
    vector<pair<int, char>> par(10000);
    queue<int> q;
    dist[n] = 0; 
    q.push(n);
    auto d = [&](int x) {
        return (2 * x) % 10000;
    };
    auto s = [&](int x) {
        return (x + 10000 - 1) % 10000;
    };
    auto l = [&](int x) {
        return (x - (x / 1000) * 1000) * 10 + x / 1000;
    };
    auto r = [&](int x) {
        return x / 10 + 1000 * (x % 10);
    };
    while (sz(q)) {
        auto u = q.front();
        q.pop();
        if (u == m) {
            break;
        }
        if (ckmin(dist[d(u)], dist[u] + 1)) {
            par[d(u)] = {u, 'D'};
            q.push(d(u));
        }
        if (ckmin(dist[s(u)], dist[u] + 1)) {
            par[s(u)] = {u, 'S'};
            q.push(s(u));
        }
        if (ckmin(dist[l(u)], dist[u] + 1)) {
            par[l(u)] = {u, 'L'};
            q.push(l(u));
        }
        if (ckmin(dist[r(u)], dist[u] + 1)) {
            par[r(u)] = {u, 'R'};
            q.push(r(u));
        }
    }
    int cur = m;
    string ans;
    while (cur != n) {
        ans += par[cur].se;
        cur = par[cur].fi;
    }
    reverse(all(ans));
    cout << ans << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

