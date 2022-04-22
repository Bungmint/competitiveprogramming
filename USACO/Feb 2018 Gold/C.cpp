// Problem: Problem 3. Taming the Herd
// Contest: USACO - USACO 2018 February Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=815
// Memory Limit: 256 MB
// Time Limit: 4000 ms
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

int dp[101][101][101];

void solve()
{
	int n;
	cin >> n;
	vi a(n);
	for (auto &e : a) cin >> e;
	memset(dp, -1, sizeof(int) * 101 * 101 * 101);
	F0R(i, n) {
		if (!i) {
			dp[0][0][1] = (a[i] != 0);
		}else{
			F0R(num, n + 1) {
				F0R(j, i) {
					if (dp[i - 1][j][num] >= 0) {
						int x = (i - j) != a[i];
						if (dp[i][j][num] == - 1) dp[i][j][num] = x + dp[i - 1][j][num];
						else ckmin(dp[i][j][num], x + dp[i - 1][j][num]);
					}
					if (num && dp[i - 1][j][num - 1] >= 0) {
						int x = !!a[i];
						if (dp[i][i][num] == - 1) dp[i][i][num] = x + dp[i - 1][j][num - 1];
						else ckmin(dp[i][i][num], x + dp[i - 1][j][num - 1]);
					}
					dbg(i, j, num);
					dbg(dp[i][j][num]);
					dbg(dp[i][i][num]);
				}
			}
		}
	}
	vi ans(n + 1, INF);
	F0R(i, n) F0R(num, n + 1) {
		if (dp[n - 1][i][num] >= 0) ckmin(ans[num], dp[n - 1][i][num]);
	}
	FOR(i, 1, n + 1) {
		cout << ans[i] << '\n';
	}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    setIO("taming");
    while (testcase--)
    {
        solve();
    }
}