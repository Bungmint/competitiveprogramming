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
    int N;
    cin >> N;
    vi L(N), R(N);
    vi query(30);
    for (int i = 0; i < N; i++) cin >> L[i] >> R[i];
    for (int i = 0; i < 30; i++) {
        int add = 0;
        int len = 1 << i;
        vi ind;
        for (int j = 0; j < N; j++) {
            if (R[j] - L[j] + 1 >= len) add++;
            else {
                    int l = L[j] % len;
                    int r = R[j] % len;
                    if (l <= r) {
                        ind.pb(l), ind.pb(r + 1);
                    } else {
                        ind.pb(l), ind.pb(len);
                        ind.pb(0), ind.pb(r + 1);
                    }
                }
        }
        dbg(ind);
        sort(all(ind)), ind.resize(unique(all(ind)) - ind.begin());
        dbg();
        vi pref(sz(ind) + 1);
        auto get_ind = [&](int x) {
            return lb(all(ind), x) - ind.begin();
        };
        for (int j = 0; j < N; j++) {
            if (R[j] - L[j] + 1 >= len) continue;
            int l = L[j] % len;
            int r = R[j] % len;
            if (l <= r) {
                pref[get_ind(l)]++;
                pref[get_ind(r + 1)]--;
            } else {
                pref[get_ind(l)]++;
                pref[get_ind(len)]--;
                pref[get_ind(0)]++;
                pref[get_ind(r + 1)]--;
            }
        }
        for (int j = 0; j < sz(ind); j++) pref[j + 1] += pref[j];
        query[i] = add + *max_element(all(pref));
    }
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int w;
        cin >> w;
        cout << query[__builtin_ctz(w)] << '\n';
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

