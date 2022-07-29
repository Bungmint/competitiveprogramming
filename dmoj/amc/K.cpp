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

/**
 * Description: Pollard-Rho
 * Source: rkm0959's tistory
 * Verification:
 * Time complexity: O(logn)
 */

ll gcd(ll x, ll y)
{
	if(x==0) return y;
	if(y==0) return x;
	return gcd(y, x%y);
}

ll extm(ll x, ll y, ll mod)
{
	__int128 T = x; T *= y;
	return (ll)(T % mod);
}

/*
ll extm(ll x, ll y, ll mod)
{
	ll ret = 0;
	while(y)
	{
		if(y&1) 
		{
			ret+=x; y--;  
			if(ret>=mod) ret-=mod;
		}
		x<<=1; y>>=1;
		if(x>=mod) x-=mod; 
	}
	return ret;
}
*/

ll extexp(ll x, ll y, ll mod)
{
	ll ret=1;
	while(y)
	{
		if(y&1) ret=extm(ret, x, mod), y--;
		x=extm(x, x, mod); y>>=1;
	}
	return ret;
}

bool trial(ll N, ll x)
{
	if(N%x==0) return false;
	ll cnt=-1, d=N-1;
	while(d%2==0) d/=2, cnt++;
	ll p=extexp(x, d, N);
	if(p==1 || p==N-1) return true;
	while(cnt--)
	{
		p=extm(p, p, N);
		if(p==N-1) return true;
	}
	return false;
}

bool is_prime(ll N)
{
	if(N==1) return false;
	ll tc[12]={2,3,5,7,11,13,17,19,23,29,31,37};
	for(int i=0 ; i<12 ; i++)
	{
		if(N==tc[i]) return true;
		if(N>40 && !trial(N,tc[i])) return false;
	}
	if(N<=40) return false;
	return true;
}

void solve() {
	ll n; cin >> n;
	if (is_prime(n - 4)) {
		cout << 2 << ' ' << 2 << ' ' << n - 4 << '\n';
		return;
	}
	// Prime density: 1/60 worst case scenario
	for (ll i = 3; ; i += 2) {
		if (is_prime(n - (i + 3)) && is_prime(i)) {
			vl t = {3, i, n - (i + 3)};
			sort(all(t));
			for (auto &e : t) cout << e << ' ';
			cout << '\n';
			// cout << 3 << ' ' << i << ' ' << n - (i + 3) << '\n';
			return;
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
