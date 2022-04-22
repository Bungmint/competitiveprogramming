// Problem: B. Pyramid
// Contest: Yandex - IOI 2006
// URL: https://contest.yandex.com/ioi/contest/562/problems/B/
// Memory Limit: 32 MB
// Time Limit: 1000 ms
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

void setIO(string s) // USACO
{
	#ifndef LOCAL
	    freopen((s + ".in").c_str(), "r", stdin);
	    freopen((s + ".out").c_str(), "w", stdout);
	#endif
}

int pref[1011][1011];
pii acmin[1011][1011];

int calc(int i1, int i2, int j1, int j2) {
	return pref[i2][j2] - pref[i2][j1 - 1] - pref[i1 - 1][j2] + pref[i1 - 1][j1 - 1];
}

void solve()
{
	int m, n, a, b, c, d;
	cin >> m >> n >> a >> b >> c >> d;
	FOR(i, 1, n + 1) FOR(j, 1, m + 1) {
		cin >> pref[i][j];
	}
	FOR(i, 1, n + 1) FOR(j, 1, m + 1) {
		pref[i][j] += pref[i][j - 1] + pref[i - 1][j] - pref[i - 1][j - 1];
	}
	FOR(i, 1, n + 1) {
		if (i + d - 1 > n) break;
		deque<int> q;
		auto add = [&](int x) {
			int z = calc(i, i + d - 1, x, x + c - 1);
			while (sz(q) && calc(i, i + d - 1, q.back(), q.back() + c - 1) > z) q.pop_back();
			q.pb(x);
		};
		auto remove = [&](int x) {
			while (sz(q) && q.front() <= x) q.pop_front();
		};
		auto findMin = [&]() {
			return make_pair(i, q.front());
		};
		FOR(j, 1, a - c) {
			add(j);
		}
		acmin[i][1] = findMin();
		FOR(j, a - c, m + 1) {
			if (j + c - 1 > m) break;
			remove(j - a + c + 1);
			add(j);
			acmin[i][j - a + c + 2] = findMin();
		}
	}
	pii ans = {1, 1};
	pii within = {1, 1};
	int val = -INF;
	FOR(j, 2, m - a + 3) {
		deque<pii> q;
		auto add = [&](int i) {
			int ii, jj;
			tie(ii, jj) = acmin[i][j];
			int z = calc(ii, ii + d - 1, jj, jj + c - 1);
			while (sz(q)) {
				int iii, jjj;
				tie(iii, jjj) = q.back();
				if (calc(iii, iii + d - 1, jjj, jjj + c - 1) > z) q.pop_back();
				else break;
			}
			q.pb({ii, jj});
		};
		auto remove = [&](int x) {
			while (sz(q) && q.front().fi <= x) q.pop_front();
		};
		auto check = [&](int i) -> void {
			int ii, jj;
			tie(ii, jj) = q.front();
			int z = calc(ii, ii + d - 1, jj, jj + c - 1);
			int x = calc(i - 1, i - 1 + b - 1, j - 1, j - 1 + a - 1);
			if (ckmax(val, x - z)) {
				ans = {i - 1, j - 1};
				within = {ii, jj};
			}
		};
		FOR(i, 2, b - d + 1) {
			add(i);
		}
		check(2);
		FOR(i, b - d + 1, n - d + 1) {
			remove(i - b + d + 1);
			add(i);
			check(i - b + d + 2);
		}
	}
	cout << ans.se << ' ' << ans.fi << "\n";
	cout << within.se << ' ' << within.fi << "\n";
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