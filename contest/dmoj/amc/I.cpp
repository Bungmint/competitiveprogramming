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
 * Solution: Primitive roots + Euclidean Algo
 */


/**
 * Description: Primitive root generator for p^e
 * Source: rkm0959's tistory blog
 * Verification:
 * Time complexity: O(sqrt(p))
 */

// for n = 2, 4 : 3 is a generator of both
// now assume n = p^e and we will search a generator of n
// we need factorization of p-1, and here we'll use O(sqrt(p)) factorization
// if p is very large, simply use Pollard-Rho for factorization

vector<ll> pr; 

void factorize(ll n)
{
	for(ll i=2 ; i*i<=n ; i++)
	{
		if(n%i==0)
		{
			pr.push_back(i);
			while(n%i==0) n/=i;
		}
	}
	if(n!=1) pr.push_back(n);
}

ll exp(ll x, ll y, ll mod)
{
	ll ret=1;
	while(y)
	{
		if(y&1) ret=(ret*x)%mod, y--;
		x=(x*x)%mod; y>>=1;
	}
	return ret;
}

ll order(ll g, ll n, ll phi_n)
{
	ll ord=phi_n;
	for(ll i=0 ; i<pr.size() ; i++)
		while(ord%pr[i]==0 && exp(g, ord/pr[i], n)==1) ord/=pr[i];
	return ord;
}

ll minv(ll a, ll b) // ax == 1 (mod b)
{
	if(a==0 && b==1) return 0;
	if(a==1) return 1; // a = 1
	return b - minv(b%a, a) * b / a;
}

ll phi(ll n)
{
	ll i; ll ret=n;
	for(i=2 ; i*i<=n ; i++)
	{
		if(n%i==0)
		{
			ret-=ret/i;
			while(n%i==0) n/=i;
		}
	}
	if(n!=1) ret-=ret/n;
	return ret;
}

map<ll, ll> M;

ll discrete_log(ll g, ll h, ll ord, ll n)
{
	ll B = (ll)sqrt(ord) + 1;
	ll g_inv = minv(g, n);
	ll cur = h;
	for(ll i=0 ; i<B ; i++)
	{
		M[cur] = i;
		cur = (cur * g_inv) % n;
	}
	ll g_B = exp(g, B, n); cur = 1;
	for(ll i=0 ; i<B ; i++)
	{
		if(M.find(cur)!=M.end()) return (i * B + M[cur]) % ord;
		cur = (cur * g_B) % n;
	}
	return -1;
}

// p : odd prime, e >= 1
// searches generator of p^e
// n = p^e, phi_n = p^{e-1}(p-1)
ll get_generator(ll p, ll e)
{
	ll n=1, phi_n, ord; pr.clear(); 
	for(ll i=1 ; i<=e ; i++) n=n*p;
	phi_n=n-n/p; factorize(p-1);
	if(e>=2) pr.push_back(p);
	for(ll g=2 ; ; g++)
	{
		if(g==0 || g==1) continue;
		if(order(g, n, phi_n)==phi_n) return g;
	}
}


/**
 * Extended Euclidean Algorithm 
 * Returns {x, y}, such that ax + by = g 
 * Source: Folklore
 * Verification:
 * Time complexity: O(log(min(a, b)))
 */

template <typename T>
pair<T, T> extended_gcd(T a, T b) {
    if (b == 0) return {1, 0};
    auto [x, y] = extended_gcd(b, a % b);
    T z = y % b;
    if (z < 0) z += b;
    return {z, (1LL - z * a) / b};
}

void solve() {
	int a, n, p; 
	cin >> a >> n >> p;
	int r = get_generator(p, 1);
	int k = discrete_log(r, a, p - 1, p);
	M.clear();
	int m = discrete_log(r, n, p - 1, p);
	int g = gcd(k, p - 1);
	dbg(r, k, m);
	if (m % g) {
		cout << "DNE" << '\n';
		return;
	}
	k /= g, m /= g;
	dbg(k, (p-1)/g);
	auto [x, y] = extended_gcd((ll)k, (ll)(p-1)/g);
	dbg(x, y);
	x *= m, y *= m;
	y = -y;
	x %= (p-1)/g;
	if (x < 0) x += (p-1)/g;
	cout << x << '\n';
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
