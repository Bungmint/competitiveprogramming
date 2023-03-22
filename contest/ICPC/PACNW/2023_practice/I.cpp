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

template <typename T>
bool compare(vector<T>& a, vector<T>& b) {
    if (sz(a) != sz(b)) return false;
    sort(all(a)), sort(all(b));
    for (int i = 0; i < sz(a); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

void solve() {
    ar<vl, 2> del{};
    ar<vector<pair<ll, char>>, 2> ins{};
    ar<int, 2> len{};
    for (int i = 0; i < 2; i++) {
        while (true) {
            char op;
            cin >> op;
            if (op == 'E') {
                break;
            }
            ll ind;
            cin >> ind;
            if (op == 'D') {
                len[i]--;
                bool ok = 0;
                for (int j = 0; j < sz(ins[i]); j++) {
                    auto &[pos, _] = ins[i][j];
                    if (pos == ind) {
                        ok = 1;
                        ins[i].erase(ins[i].begin() + j);
                        break;
                    }
                } 
                if (!ok) {
                    ll true_val = ind;
                    for (auto &[pos, _] : ins[i]) {
                        if (pos < ind) true_val--;
                    }
                    for (auto &pos : del[i]) {
                        if (pos <= true_val) true_val++;
                    }
                    del[i].pb(true_val);
                }
                for (auto &[pos, _] : ins[i]) {
                    if (pos > ind) pos--; 
                }
            } else {
                len[i]++;
                char ch;
                cin >> ch;
                for (auto &[pos, _] : ins[i]) {
                    if (pos >= ind) {
                        pos++;
                    }
                }
                ins[i].pb({ind, ch}); 
            }
            sort(all(ins[i])), sort(all(del[i]));
        }
    } 
    if (len[0] != len[1]) {
        cout << 1 << '\n';
        return;
    }
    if (!compare(del[0], del[1]) || !compare(ins[0], ins[1])) {
        cout << 1 << '\n';
        return;
    }


    cout << 0 << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	// cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

