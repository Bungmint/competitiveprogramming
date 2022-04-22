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

int dp[1 << 20];
int leftover[1 << 20];
int a[20], b[20];
int n, m;

void solve()
{
	cin >> n >> m;
	F0R(i, n) cin >> a[i];
	F0R(i, m) cin >> b[i];
	FOR(mask, 1, 1 << m) {
		F0R(i, m) {
			if (!(mask & (1 << i))) continue;
			int prevMask = mask - (1 << i);
			if (dp[mask] > dp[prevMask]) continue;
			if (ckmax(dp[mask], dp[prevMask])) {
				if (leftover[prevMask] + b[i] == a[dp[prevMask]]) {
					dp[mask] = dp[prevMask] + 1;
					leftover[mask] = 0;
				}else if (leftover[prevMask] + b[i] < a[dp[prevMask]]) {
					leftover[mask] = leftover[prevMask] + b[i];
				}else{
					leftover[mask] = leftover[prevMask];
					if (b[i] < a[dp[mask]]) ckmax(leftover[mask], b[i]);
				}
				continue;
			} 
			if (leftover[prevMask] + b[i] == a[dp[prevMask]]) {
				dp[mask] = dp[prevMask] + 1;
				leftover[mask] = 0;
			}else if (leftover[prevMask] + b[i] < a[dp[prevMask]]) {
				ckmax(leftover[mask], leftover[prevMask] + b[i]);
			}else{
				ckmax(leftover[mask], leftover[prevMask]);
				if (b[i] < a[dp[mask]]) ckmax(leftover[mask], b[i]);
			}
		}
		if (dp[mask] == n) {
			cout << "YES\n";
			return;
		}
	}
	cout << (dp[(1 << m) - 1] == n ? "YES" : "NO") << "\n";
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