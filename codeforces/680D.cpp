// Problem: D. Bear and Tower of Cubes
// Contest: Codeforces - Codeforces Round #356 (Div. 2)
// URL: https://codeforces.com/contest/680/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2022 Youngmin Park. All rights reserved.
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
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

#define all(v) (v).begin(), (v).end()
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define REP(a) F0R(_, a)

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v)
{
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}
void dbg_out()
{
    cerr << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

inline namespace RecursiveLambda{
	template <typename Fun>
	struct y_combinator_result{
		Fun fun_;
		template <typename T> 
		explicit y_combinator_result(T &&fun): fun_(forward<T>(fun)){}
		template <typename...Args>
		decltype(auto) operator()(Args &&...args){
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun){
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

void setIO(string s) // USACO
{
	#ifndef LOCAL
	    freopen((s + ".in").c_str(), "r", stdin);
	    freopen((s + ".out").c_str(), "w", stdout);
	#endif
}

const int N = 1e7;
pii dp[N + 1];
int a[N + 1];
pll cache[(int)1e5 + 10];
ll cube[(int)1e5 + 10];

pll go(ll L, ll R, ll x) {
	if (L) {
		pll res = go(L - cube[x], R - cube[x], 0);
		return {res.fi + 1, res.se + cube[x]};
	}
	if (R <= N) {
		return {dp[R].fi, dp[R].se};
	}
	if (x) {
		return cache[x];
	}
	x = cbrt(ld(R));
	if (cube[x + 1] <= R) x++;
	pll a = go(0, cube[x] - 1, x);
	pll b = go(0, R - cube[x], 0);
	b.fi++, b.se += cube[x];
	pll c = max(a, b);
	return c;
}

void solve()
{
	ll m;
	cin >> m;
	FOR(i, 1, 1e5 + 10) {
		cube[i] = (1LL * i) * i * i;
	}
	FOR(i, 1, N + 1) {
		int x = cbrt((ld)i);
		if (cube[x + 1] <= i) x++;
		dp[i] = dp[i - 1];
		a[i] = a[i - cube[x]] + 1;
		ckmax(dp[i], make_pair(a[i], i));
		if (i == m) {
			cout << dp[i].fi << " " << dp[i].se;
			return;
		}
	}
	pll ans = {dp[N].fi, dp[N].se};
	for (ll i = 0; cube[i] <= m; i++) {
		ll L = cube[i];
		ll R = min(m, cube[i + 1] - 1);
		pll val = go(L, R, i);
		ckmax(ans, val);
		if (R == cube[i + 1] - 1) {
			cache[i + 1] = max(cache[i], val);
		}
	}
	cout << ans.fi << " " << ans.se;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}