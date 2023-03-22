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
 * Description: Data structure that supports range idempotent queries on a static array
 * Source: Own
 * Verification:
 * Time Complexity: O(nlogn) build, O(1) query
 */

template <typename T>
struct SparseTable{
	vector<vector<T>> spar;
	const T ID = {INF, INF}; // change this
	inline T merge(const T& a, const T& b) { // change this
		return min(a, b);
	} 
	SparseTable() {}
	SparseTable(const vector<T>& a) {
		int lg = 32 - __builtin_clz(sz(a));
		spar.assign(lg, vector<T>(sz(a), ID));
		for (int i = 0; i < sz(a); ++i) spar[0][i] = a[i];
		for (int j = 1; j < lg; ++j) 
			for (int i = 0; i + (1 << j) <= sz(a); ++i)
				spar[j][i] = merge(spar[j - 1][i], spar[j - 1][i + (1 << (j - 1))]);
	}
	SparseTable(T a[], int n) {
		int lg = 32 - __builtin_clz(n);
		spar.assign(lg, vector<T>(n, ID));
		for (int i = 0; i < n; ++i) spar[0][i] = a[i];
		for (int j = 1; j < lg; ++j) 
			for (int i = 0; i + (1 << j) <= n; ++i)
				spar[j][i] = merge(spar[j - 1][i], spar[j - 1][i + (1 << (j - 1))]);
	}
	T query(int a, int b) {
		assert(a <= b);
		int dif = 31 - __builtin_clz(b - a + 1);
		return merge(spar[dif][a], spar[dif][b - (1 << dif) + 1]);
	}
};

void solve() {
    int N;
    cin >> N;
    vi p(N), tail(N, -1);
    vpi p_with_ind_even(N / 2), p_with_ind_odd(N / 2);
    vector<vi> g(N);
    for (auto &e : p) cin >> e, e--;
    for (int i = 0; i < N; i++) {
        if (i & 1) {
            p_with_ind_odd[i / 2] = {p[i], i};
        } else {
            p_with_ind_even[i / 2] = {p[i], i};
        }
    }
    dbg(p_with_ind_odd, p_with_ind_even);
    SparseTable<pii> even(p_with_ind_even), odd(p_with_ind_odd);
    auto dfs = y_combinator([&](auto self, int L, int R) -> int {
                                dbg(L, R);
                                if (L == R - 1) {
                                    tail[p[L]] = p[R];
                                    return p[L];
                                }
                                int next_L, next_R;
                                if (L & 1) {
                                    auto [_, x] = odd.query(L / 2, (R - 1) / 2);
                                    next_L = x;
                                    auto [__, y] = even.query((next_L + 1) / 2, R / 2);
                                    next_R = y;
                                } else {
                                    auto [_, x] = even.query(L / 2, (R - 1) / 2);
                                    next_L = x;
                                    auto [__, y] = odd.query((next_L + 1) / 2, R / 2);
                                    next_R = y;
                                }
                                tail[p[next_L]] = p[next_R];
                                if (L < next_L) {
                                    g[p[next_L]].pb(self(L, next_L - 1));
                                }
                                if (next_L + 1 < next_R) {
                                    g[p[next_L]].pb(self(next_L + 1, next_R - 1));
                                }
                                if (next_R < R) {
                                    g[p[next_L]].pb(self(next_R + 1, R));
                                }
                                dbg(next_L, next_R);
                                dbg(p[next_L], tail[p[next_L]]);
                                return p[next_L];
                            });
    int root = dfs(0, N - 1);
    vi ans;
    pqg<int> pq;
    pq.push(root);
    while (sz(pq)) {
        int u = pq.top();
        pq.pop();
        ans.pb(u), ans.pb(tail[u]);
        for (auto &v : g[u]) {
            pq.push(v);
        }
    }
    for (int i = 0; i < sz(ans); i++) cout << ans[i] + 1 << " \n"[i == sz(ans) - 1];
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

