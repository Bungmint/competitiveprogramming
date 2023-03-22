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
    int n, q;
    cin >> n >> q;
    map<int, int> good_seg;
    set<int> bad, not_bad;
    for (int i = 1; i <= n; i++) {
        not_bad.insert(i);
    }
    not_bad.insert(0), not_bad.insert(n + 1);
    auto range_upd = [&](int l, int r) -> void {
        auto it = not_bad.lb(l);
        while (it != not_bad.end() && *it <= r) {
            bad.insert(*it);
            it = not_bad.erase(it); 
        }
    };
    auto upd = [&](int l, int r) -> void {
        if (good_seg.empty()) {
            good_seg[l] = r;
            return;
        }
        auto it = good_seg.ub(l);
        if (it != good_seg.end() && it->se <= r) {
            return; 
        }
        if (good_seg.count(l) && good_seg[l] <= r) {
            return;
        }
        good_seg[l] = r;
        while (true) {
            it = good_seg.lb(l);
            if (it == good_seg.begin()) return;
            it--;
            if (it->se >= r) {
                good_seg.erase(it);
            } else return;
        }
    };
    for (int i = 0; i < q; i++) {
        int op;
        cin >> op;
        if (op == 0) {
            int l, r, x;
            cin >> l >> r >> x;
            if (x == 1) {
                upd(l, r); 
            } else {
                range_upd(l, r);
            }
        } else {
            int x;
            cin >> x;
            if (bad.count(x)) {
                cout << "NO" << '\n';
            } else {
                auto it = not_bad.ub(x);
                int r = *it - 1;
                it--, it--;
                int l = *it + 1;
                dbg(good_seg);
                dbg(l, r);
                auto mapit = good_seg.lb(l);
                if (mapit != good_seg.end() && mapit->se <= r) {
                    cout << "YES\n";
                } else {
                    cout << "N/A\n";
                }
            }
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

