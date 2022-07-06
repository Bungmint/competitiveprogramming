#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
int mul(int a, int b) {
	return 1LL * a * b % MOD;
}
int add(int a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
	if (a < 0) a += MOD;
	return a;
}
int mod_pow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}

const int N = 3e5;
int fact[N], invfact[N];
void precalc() {
	fact[0] = 1;
	for (int i = 1; i < N; i++) fact[i] = mul(fact[i - 1], i);
	invfact[N - 1] = mod_pow(fact[N - 1], MOD - 2);
	for (int i = N - 2; i >= 0; i--) invfact[i] = mul(invfact[i + 1], i + 1);
}
int binom(int n, int r) {
	if (n < r || n < 0) return 0;
	return mul(fact[n], mul(invfact[n - r], invfact[r]));
}


void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	int ans = 0;
	for (int i = 0; i <= min(m, k / n); i++) {
		int fl = (i & 1) ? -1 : 1;
		ans = add(ans, mul(fl, mul(binom(m, i), binom(k - n*i + m - 1, m - 1))));
	}
	cout << ans << '\n';
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	precalc();
	while (testcase--)
	{
		solve();
	}
}
