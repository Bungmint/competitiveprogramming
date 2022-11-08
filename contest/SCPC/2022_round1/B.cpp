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
#include <iomanip>
#include <assert.h>
using namespace std;
using ll = long long;

constexpr int MOD = 1e9 + 7;
constexpr int M = 5e5 + 100;
int a[M];
ll pref[M];
int dp[M], fact[M], inv_fact[M];

void add(int& x, int y) {
	x += y;
	if (x >= MOD) x -= MOD;
}
int mul(int x, int y) {
	return 1LL * x * y % MOD;
}
int bin_pow(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = (1LL * r * x) % MOD;
		x = (1LL * x * x) % MOD;
		y >>= 1;
	}
	return r;
}
void precalc() {
	fact[0] = 1;
	for (int i = 1; i < M; i++) {
		fact[i] = mul(fact[i - 1], i);
	}
	inv_fact[M - 1] = bin_pow(fact[M - 1], MOD - 2);
	for (int i = M - 2; i >= 0; i--) {
		inv_fact[i] = mul(inv_fact[i + 1], i + 1);
	}
}
int binom(int n, int k) {
	if (n < k) return 0;
	return mul(fact[n], mul(inv_fact[n - k], inv_fact[k]));
}




void solve(int tc) {
	cout << "Case #" << tc << '\n';
	memset(dp, 0, sizeof(dp));
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		pref[i] = pref[i - 1] + a[i];
	}
	if (pref[n] % k) {
		cout << 0 << '\n';
		return;
	}
	const ll t = pref[n] / k;
	if (t == 0) {
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			if (pref[i] == 0) {
				cnt++;
			}
		}
		cout << binom(cnt - 1, k - 1) << '\n';
		return;
	}
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		if (ll j = pref[i] / t; pref[i] % t == 0 && j > 0) {
			if (j < k || (j == k && i == n)) add(dp[j], dp[j - 1]);
		}
	}
	cout << dp[k] << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	precalc();
	int testcase = 1;
	cin >> testcase;
	for (int i = 1; i <= testcase; i++) {
		solve(i);
	}
	return 0;
}
