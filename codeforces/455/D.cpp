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

const int NAX = 1e5 + 100, B = 350;
int a[NAX], n, q, last_ans;
int freq[B][NAX];
vi block[B];


void cyclic(int l, int r) {
	int val{}, ptr{};
	for (int i = 0; i < B; i++) {
		if (sz(block[i]) == 0) continue;
		int L = ptr, R = ptr + sz(block[i]) - 1;
		if (L <= r && r <= R) {
			val = block[i][r - L];
			freq[i][val]--;
			block[i].erase(block[i].begin() + r - L);
			break;
		}
		ptr += sz(block[i]);
	}
	dbg(val);
	ptr = 0;
	for (int i = 0; i < B; i++) {
		if (sz(block[i]) == 0) continue;
		int L = ptr, R = ptr + sz(block[i]) - 1;
		if (L <= l && l <= R) {
			freq[i][val]++;
			block[i].insert(block[i].begin() + l - L, val);
			dbg(block[i]);
			break;
		}
		ptr += sz(block[i]);
	}
}
int get(int k, int l, int r) {
	int ans{};
	int ptr{};
	for (int i = 0; i < B; i++) {
		if (sz(block[i]) == 0) continue;
		int L = ptr, R = ptr + sz(block[i]) - 1;
		dbg(L, R, l, r, k);
		if (r < L) break;
		if (R < l) {
			ptr += sz(block[i]);
			continue;
		}
		if (l <= L && R <= r) ans += freq[i][k];
		else{
			L = max(L, l);
			R = min(R, r);
			for (int j = L; j <= R; j++) {
				dbg(block[i][j - ptr], k);
				ans += (block[i][j - ptr] == k);
			}
		}
		ptr += sz(block[i]);
	}
	return ans;
}
void rebuild() {
	vi arr;
	for (int i = 0; i < B; i++) {
		for (auto &it : block[i]) {
			freq[i][it] = 0;
			arr.pb(it);
		}
		vi().swap(block[i]);
	}
	assert(sz(arr) == n);
	for (int i = 0; i < B; i++) {
		int L = i*B, R = min(n-1, (i+1)*B-1);
		for (int j = L; j <= R; j++) {
			block[i].pb(arr[j]);
			freq[i][arr[j]]++;
		}
	}
	vi().swap(arr);
}
void init() {
	for (int i = 0; i < B; i++) {
		int L = i*B, R = min(n-1, (i+1)*B-1);
		if (L > R) break;
		for (int j = L; j <= R; j++) {
			block[i].pb(a[j]);
			freq[i][a[j]]++;
		}
		// dbg(block[i]);
	}
}

void solve() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	init();
	cin >> q;
	for (int i = 0; i < n; i++) {
		if (i && i % B == 0) {
			rebuild();
		}
		int t, l, r; cin >> t >> l >> r;
		l = (l + last_ans - 1) % n;
		r = (r + last_ans - 1) % n;
		if (l > r) swap(l, r);
		if (t == 1) {
			// dbg(l, r);
			if (l == r) continue;
			cyclic(l, r);
		}else{
			int k; cin >> k;
			k = (k + last_ans - 1) % n + 1;
			cout << (last_ans = get(k, l, r)) << '\n';
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
