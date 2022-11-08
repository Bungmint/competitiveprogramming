// Problem: F. Reverse
// Contest: Codeforces - Codeforces Round #760 (Div. 3)
// URL: https://codeforces.com/contest/1618/problem/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2022 Youngmin Park. All rights reserved.
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

ll flip(ll x) {
	ll lead = 63 - __builtin_clzll(x);
	ll res{};
	F0R(i, lead + 1) {
		if (x & (1LL << i)) {
			res += (1LL << (lead - i));
		}
	}
	return res;
}

void solve()
{
	ll x, y;
	cin >> x >> y;
	if (x == y) {
		cout << "YES\n";
		return;
	}
	if (__builtin_popcountll(x) > __builtin_popcountll(y)) {
		cout << "NO\n";
		return;
	}
	vl b;
	ll l = 63 - __builtin_clzll(y);
	R0F(i, l + 1) {
		b.pb(!!(y & (1LL << i)));
	}
	vl a(4);
	a[0] = flip(x),
	a[1] = flip(x * 2 + 1);
	a[2] = flip(a[0]);
	a[3] = flip(a[1]);
	F0R(i, 4) {
		vl c;
		ll r = 63 - __builtin_clzll(a[i]);
		R0F(ii, r + 1) {
			c.pb(!!(a[i] & (1LL << ii)));
		}
		if (sz(b) < sz(c)) continue;
		dbg(b);
		dbg(c);
		F0R(j, sz(b) - sz(c) + 1) {
			bool ok = 1;
			FOR(k, j, j + sz(c)) {
				if (b[k] != c[k - j]) {
					ok = 0;
					goto aaa;
				}
			}
			F0R(k, j) {
				if (!b[k]) {
					ok = 0;
					goto aaa;
				}
			}
			FOR(k, j + sz(c), sz(b)) {
				if (!b[k]) {
					ok = 0;
					goto aaa;
				}
			}
			aaa:;
			if (ok) {
				cout << "YES\n";
				return;
			}
		}
	}
	cout << "NO\n";
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