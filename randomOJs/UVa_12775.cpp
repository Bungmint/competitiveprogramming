// Problem: 12775 - Gift Dilemma
// Contest: UVa Online Judge
// URL: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4628
// Memory Limit: 32 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2021 Youngmin Park. All rights reserved.
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

// inline namespace RecursiveLambda{
	// template <typename Fun>
	// struct y_combinator_result{
		// Fun fun_;
		// template <typename T> 
		// explicit y_combinator_result(T &&fun): fun_(forward<T>(fun)){}
		// template <typename...Args>
		// decltype(auto) operator()(Args &&...args){
			// return fun_(ref(*this), forward<Args>(args)...);
		// }
	// };
	// template <typename Fun>
	// decltype(auto) y_combinator(Fun &&fun){
		// return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	// }
// };

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

#define int long long

int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a % b);
}

int ex_gcd(int a, int b, int& x, int& y){
	if (!a){
		x = 0, y = 1;
		return b;
	}
	int g = ex_gcd(b % a, a, x, y);
	int xx = y - (b / a) * x;
	int yy = x;
	return x = xx, y = yy, g;
}

void solve()
{
	int a, b, c, p;
	cin >> a >> b >> c >> p;
	int ggg = gcd(gcd(a, b), c);
	if (p % ggg){
		cout << 0 << "\n";
		return;
	}
	p /= ggg, a /= ggg, b /= ggg, c /= ggg;
	int x, y;
	int g = ex_gcd(a, b, x, y);
	a /= g, b /= g;
	ll ans = 0, dL = 0, dR = 0;
	while (p >= 0){
		if (p % g){
			p -= c;
			continue;
		}
		int pp = p / g;
		int xx = x * pp, yy = y * pp;
		dbg(xx, yy, pp, a, b);
		int L = -xx / b, R = yy / a;
		while (-xx > L * b) L++;
		while (R * a > yy) R--;
		ans += max(0LL, R - L + 1);
		p -= c;
	}
	cout << ans << "\n";
}

int32_t main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    cin >> testcase;
    FOR(i, 1, testcase + 1)
    {
    	cout << "Case " << i << ": ";
        solve();
    }
}