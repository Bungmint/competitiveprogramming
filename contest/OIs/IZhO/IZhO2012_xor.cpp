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

constexpr int MAXN = 250'001;
int tree[MAXN * 30][2], min_ind[MAXN * 30];
int root = 0;
int cur = 1;

void init() {
    memset(min_ind, 0x3f, sizeof(min_ind));
}
void add(int x, int i) {
    int now = root;
    for (int b = 29; b >= 0; b--) {
        int fl = x >> b & 1; 
        if (!tree[now][fl]) tree[now][fl] = cur++;
        now = tree[now][fl];
        ckmin(min_ind[now], i);
    }
}
int query(int lim, int x) {
    int now = root;
    int res = 0x3f3f3f3f;
    for (int b = 29; b >= 0; b--) {
        int fl = x >> b & 1;
        int fl_lim = lim >> b & 1;
        if (fl_lim) {
            if (fl && tree[now][!fl]) {
                now = tree[now][!fl]; 
            } else if (!fl && tree[now][!fl]) {
                now = tree[now][!fl];
            } else break;
        } else {
            dbg(b, x, lim, tree[now][fl]);
            if (tree[now][!fl]) ckmin(res, min_ind[tree[now][!fl]]);
            if (!tree[now][fl]) break;
            now = tree[now][fl];
        }
        if (b == 0) ckmin(res, min_ind[now]), dbg(min_ind[now]);
    }
    return res;
}

void solve() {
    int N, x;
    cin >> N >> x;
    int pref = 0;
    add(pref, 0);
    int id = -1, ans = -1;
    for (int i = 1; i <= N; i++) {
        int a;
        cin >> a;
        pref ^= a;
        add(pref, i);
        int q = query(x, pref);
        dbg(i, q);
        if (q < i && ckmax(ans, i - q)) id = q + 1;
    } 
    cout << id << ' ' << ans << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    init();
	int testcase = 1;
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

