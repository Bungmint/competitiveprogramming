#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <list>
#include <chrono>
#include <random>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <utility>
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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
constexpr bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
constexpr bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

#ifdef LOCAL
#include "miscellaneous/debug.h"
#else
#define dbg(...) 42
#endif

#pragma endregion TEMPLATE

const int MAXN = 1e5 + 10;
int A[MAXN], D[MAXN];

void solve() {
	int N, k; cin >> N >> k;
	set<int> active;
	set<pii> minimums;
	ll ans{}, added{}, res{};
	for (int i = 0; i < N; i++) {
		cin >> A[i], D[i] = (A[i] >= k ? 0 : k - A[i]);
		if (D[i]) {
			active.insert({i});
			minimums.insert({D[i], i});
			ans = max(ans, (ll)D[i]);
		}
	}
	cout << ans << ' ';
	while (sz(active)) {
		while (sz(minimums) && added >= minimums.begin()->fi) {
			auto [d, id] = *minimums.begin();
			active.erase(id);
			minimums.erase(minimums.begin());
		}
		if (sz(minimums) == 0) break;
		auto [d, id] = *minimums.begin();
		int len = *--active.end() - *active.begin() + 1;
		res += 1LL*len*(d-added);
		added = d;
		minimums.erase(minimums.begin());
		active.erase(id);
	}
	cout << res << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int testcase = 1;
	cin >> testcase;
	for (int tc = 1; tc <= testcase; tc++) {
		cout << "Case #" << tc << '\n';
		solve();
	}
}
