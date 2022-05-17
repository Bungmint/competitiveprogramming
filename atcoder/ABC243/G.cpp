// Problem: G - Sqrt
// Contest: AtCoder - AtCoder Beginner Contest 243
// URL: https://atcoder.jp/contests/abc243/tasks/abc243_g
// Memory Limit: 1024 MB
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


__int128_t read()
{
    __int128_t x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(__int128_t x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
bool cmp(__int128_t x, __int128_t y) { return x > y; }
using i128 = __int128_t;

i128 sqSum(ll l, ll r) {
	i128 x = i128(r) * i128(r + 1) * i128(2 * r + 1) / i128(6);
	i128 y = i128(l - 1) * i128(l) * i128(2 * l - 1) / i128(6);
	return ll(x - y);
}

// Second step = 1
// Third step = s_(x * x) ˜ s_(nn)
//            = nn + 1 - x * x

ll mySqrt(ll x) {
	ll l = 1, r = x, ans = 1;
	while (l <= r) {
		ll mid = (l + r) / 2;
		i128 cur = i128(mid) * i128(mid);
		if (cur <= x) {
			ans = mid, l = mid + 1;
		}else r = mid - 1;
	}
	return ans;
}

ll dp[60000], tmp[60000];
i128 pref[60000];
#define sqrt mySqrt

void solve()
{
	ll n;
	cin >> n;
	ll nn = sqrt(n);
	ll nnn = sqrt(nn);
	// Starting from step 3
	memset(tmp, 0, sizeof(tmp));
	memset(dp, 0, sizeof(dp));
	for (ll cur = nnn, last = nn; ; last = cur, cur = sqrt(cur)) {
		if (cur == nnn) {
			FOR(i, 1, cur + 1) {
				dp[i] = nn + 1 - 1LL * i * i;
			}
		}else{
			FOR(i, 1, last + 1) {
				pref[i] = pref[i - 1] + tmp[i];
			}
			FOR(i, 1, cur + 1) {
				dp[i] = pref[last] - pref[i * i - 1];
			}
		}
		if (cur == 1) {
			cout << dp[1] << "\n";
			return;
		}
		F0R(i, cur + 1) tmp[i] = dp[i];
	}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}