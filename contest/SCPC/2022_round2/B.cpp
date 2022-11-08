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
#include <bitset>
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
mt19937_64 rng;
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

/**
 * Find the largest interval that isn't completely included in another interval
 */

const int MAXN = 3e5 + 100;
int N, A[MAXN], B[MAXN];
int bit[MAXN];
vi ind[MAXN];
bitset<MAXN> vis{};

void init() {
	memset(bit, 0, sizeof(int)*(N+5));
	for (int i = 1; i <= N; i++) {
		bit[i]++;
		int nxt = i + (i&-i);
		if (nxt <= N) bit[nxt] += bit[i];
	}
	
}
void upd(int i, int v) {
	for (i++; i <= N; i += i&-i) bit[i] += v;
}
int query(int i) {
	int res{};
	for (i++; i > 0; i -= i&-i) res += bit[i];
	return res;
}
int query(int l, int r)	{
	return query(r) - query(l-1);
}


void solve() {
	cin >> N;
	for (int i = 0; i < N; i++) ind[i].clear();
	for (int i = 0; i < N; i++) {
		cin >> A[i], vis[i] = 0;
		B[i] = sz(ind[A[i]]);
		ind[A[i]].pb(i);
	}
	ll ans{};
	init();
	for (int i = 0; i < N; i++) {
		if (vis[i]) continue;
		int j = ind[A[i]][sz(ind[A[i]]) - 1 - B[i]];
		vis[i] = vis[j] = 1;
		ans += query(i, j) - 1;
		upd(i, -1);
		if (i != j) upd(j, -1);
	}
	cout << ans << '\n';
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
