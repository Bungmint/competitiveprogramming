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
mt19937_64 rng();
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

#define div div_

const int MAXN = 5e4 + 100, MOD = 998244353;
int N, K, P;
int p[MAXN];
int E[70][1<<10];

int mul(int a, int b) { return 1LL*a*b%MOD; }
int add(int a, int b) {
	a += b; if (a >= MOD) a -= MOD;
	return a;
}
int sub(int a, int b) {
	a -= b; if (a < 0) a += MOD;
	return a;
}
int bin_pow(int a, int b) {
	int r = 1;
	while (b) {
		if (b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return a;
}
int inv(int a) { return bin_pow(a, MOD-2); }
int div(int a, int b) {
	return mul(a, inv(b));
}

void solve() {
	cin >> N >> K;
	P = 0;
	for (int i = 0; i < N; i++) cin >> p[i], P += p[i];
	if (N > 10) {
		cout << 0 << endl;
		return;
	}
	memset(E, 0, sizeof(E));
	E[0][0] = 1;
	int ans{};
	for (int i = 1; i <= K; i++) {
		int cur{};
		for (int mask = 1; mask < (1 << N); mask++) {
			for (int j = 0; j < N; j++) {
				if (mask>>j & 1) {
					int p_mask = mask ^ (1<<j);
					E[i][mask] = add(E[i][mask], mul(p[j], add(E[i-1][p_mask], E[i-1][mask])));
				}
			}
			cur = add(cur, mul(__builtin_popcount(mask), E[i][mask]));
		}
		ans ^= cur;
	}
	cout << ans << endl;
	
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int testcase = 1;
	cin >> testcase;
	for (int tc = 1; tc <= testcase; tc++) {
		cout << "Case #" << tc << endl;
		solve();
	}
}
