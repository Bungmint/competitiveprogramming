// Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

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

/*
 * Solution: Mo's Algorithm
 */

constexpr int LOGN = 20;
constexpr int MAXN = 1 << LOGN;

ll hilbertorder(int x, int y)
{
	ll d = 0;
	for (int s = 1 << (LOGN - 1); s; s >>= 1) {
		bool rx = x & s, ry = y & s;
		d = d << 2 | (rx * 3 ^ static_cast<int>(ry));
		if (!ry) {
			if (rx) {
				x = MAXN - x;
				y = MAXN - y;
			}
			swap(x, y);
		}
	}
	return d;
}

struct Query {
    int l, r, idx;
    ll ord;
	inline void calcOrder() {
		ord = hilbertorder(l, r);
	}
};
inline bool operator<(const Query &a, const Query &b) {
	return a.ord < b.ord;
}

using vq = vector<Query>;

constexpr int M = 1e5 + 50;
constexpr int SQRT = 320;
int L[M * 2], R[M * 2], pref[M];
vi ind[M * 2];
int cnt[SQRT * SQRT], buck[SQRT];

void remove(int idx, const bool is_left) {
	dbg();
	const int ID = pref[idx] + M;
	int &l = L[ID], &r = R[ID];
	if (r - l + 1 >= 2) {
		int diff = ind[ID][r] - ind[ID][l];
		cnt[diff]--;
		buck[diff / SQRT]--;
	} 
	if (is_left) l++;
	else r--;
	if (r - l + 1 >= 2) {
		int diff = ind[ID][r] - ind[ID][l];
		cnt[diff]++;
		buck[diff / SQRT]++;
	}
}
void add(int idx, const bool is_left) {
	const int ID = pref[idx] + M;
	int &l = L[ID], &r = R[ID];
	dbg(r, l, is_left, ID);
	if (r - l + 1 >= 2) {
		int diff = ind[ID][r] - ind[ID][l];
		cnt[diff]--;
		buck[diff / SQRT]--;
	} 
	if (is_left) l--;
	else r++;
	if (r - l + 1 >= 2) {
		int diff = ind[ID][r] - ind[ID][l];
		cnt[diff]++;
		buck[diff / SQRT]++;
	}
}     
int get_answer() {
	for (int i = SQRT - 1; i >= 0; i--) {
		if (buck[i] == 0) continue;
		else{
			for (int j = SQRT - 1; j >= 0; j--) {
				if (cnt[i * SQRT + j]) {
					return i * SQRT + j;
				}
			}
		}
	}
	return 0;
}

vi mo(vq queries) {
   	vi answers(queries.size());
    for (auto &e : queries) e.calcOrder();
    sort(queries.begin(), queries.end());
	memset(R, -1, sizeof(R));

    int cur_l = 0;
    int cur_r = -1;
    for (Query q : queries) {
		dbg(q.l, q.r, q.idx);
        while (cur_l > q.l) { cur_l--; add(cur_l, 1); }
        while (cur_r < q.r) { cur_r++; add(cur_r, 0); }
        while (cur_l < q.l) { remove(cur_l, 1); cur_l++; }
        while (cur_r > q.r) { remove(cur_r, 0); cur_r--; }
        answers[q.idx] = get_answer();
    }
    return answers;
}




void solve() {
	int n;
	cin >> n;
	vi a(n);
	for (auto &e : a) cin >> e;
	ind[M].pb(0);
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += a[i - 1];
		pref[i] = sum;
		ind[sum + M].pb(i);
	}
	int q;
	cin >> q;
	vq queries(q);
	for (int i = 0; i < q; i++) {
		auto &[l, r, idx, _] = queries[i];
		idx = i;
		cin >> l >> r; l--;
	}
	vi ans = mo(queries);
	for (int i = 0; i < q; i++) cout << ans[i] << " \n"[i == q - 1];
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
