// Problem: Cat and Mice
// Contest: Kattis
// URL: https://open.kattis.com/problems/catandmice
// Memory Limit: 1024 MB
// Time Limit: 10000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2021 Youngmin Park. All rights reserved.
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

const ld EPS = 1e-9;
int x[15], y[15], s[15];
ld dp[1 << 15][15];
bool vis[1 << 15][15];
ld speed[15];


int sq(int x) {return x * x;}
ld dist(int i, int j) {
	return sqrt((ld)(sq(x[i] - x[j]) + sq(y[i] - y[j])));
}
ld distO(int i) {
	return sqrt((ld)(sq(x[i]) + sq(y[i])));
}


void solve()
{
	int n;
	cin >> n;
	F0R(i, n) cin >> x[i] >> y[i] >> s[i];
	ld m;
	cin >> m;
	ld l = 0, r = 2e5, ans = 0;
	while (l + EPS < r) {
		ld mid = (l + r) / 2;
		speed[0] = mid;
		FOR(i, 1, n) speed[i] = speed[i - 1] * m;
		memset(vis, 0, sizeof(bool) * 15 * (1 << 15));
		F0R(i, (1 << 15)) F0R(j, 15) dp[i][j] = LINF;
		F0R(i, n) {
			ld t = distO(i) / speed[0];
			if (s[i] + EPS > t) {
				vis[1 << i][i] = 1;
				dp[1 << i][i] = t;
			}
		}
		FOR(mask, 1, 1 << n) {
			int cnt = __builtin_popcount(mask);
			if (cnt <= 1) continue;
			F0R(i, n) {
				if (!(mask & (1 << i))) continue;
				int prevMask = mask - (1 << i);
				F0R(j, n) {
					if ((prevMask & (1 << j)) && vis[prevMask][j]) {
						ld t = dp[prevMask][j] + dist(i, j) / speed[cnt - 1];
						if (s[i] + EPS > t) {
							vis[mask][i] = 1;
							if (dp[mask][i] > t + EPS) dp[mask][i] = t + EPS;
						}
					}
				}
			}
		}
		bool ok = 0;
		F0R(i, n) {
			ok |= vis[(1 << n) - 1][i];
		}
		if (ok) ans = mid, r = mid;
		else l = mid;
	}
	cout << fixed << setprecision(20) << ans << "\n";
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