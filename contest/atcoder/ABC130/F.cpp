// Problem: F - Minimum Bounding Box
// Contest: AtCoder - AtCoder Beginner Contest 130
// URL: https://atcoder.jp/contests/abc130/tasks/abc130_f
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
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

vi lx, rx, ly, ry;

void solve()
{
	int n;
	cin >> n;
	int mix = INF, mxx = -INF, miy = INF, mxy = -INF;
	ll ans = LINF;
	F0R(i, n) {
		int x, y;
		char c;
		cin >> x >> y >> c;
		x *= 2, y *= 2;
		if (c == 'D') ly.pb(y);
		else if (c == 'U') ry.pb(y);
		else if (c == 'R') rx.pb(x);
		else lx.pb(x);
		if (c == 'D' || c == 'U') {
			ckmin(mix, x);
			ckmax(mxx, x);
		}else{
			ckmin(miy, y);
			ckmax(mxy, y);
		}
	}
	sort(all(ly)), sort(all(lx)), sort(all(rx)), sort(all(ry));
	vi order = {0, (int)1e8};
	int l = 0, r = 1e8, res = 1e8;
	while (l <= r) {
		int mid = (l + r) / 2;
		int curmx = mxx, nxt = mxx;
		if (sz(lx)) ckmax(curmx, lx.back() - mid), ckmax(nxt, lx.back() - mid - 1);
		if (sz(rx)) ckmax(curmx, rx.back() + mid), ckmax(nxt, rx.back() + mid + 1);
		if (curmx > nxt) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	order.pb(res);
	order.pb(res + 1);
	l = 0, r = 1e8, res = 1e8;
	while (l <= r) {
		int mid = (l + r) / 2;
		int curmx = mxx, nxt = mxx;
		if (sz(lx)) ckmax(curmx, lx.back() - mid), ckmax(nxt, lx.back() - mid - 1);
		if (sz(rx)) ckmax(curmx, rx.back() + mid), ckmax(nxt, rx.back() + mid + 1);
		if (curmx >= nxt) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	order.pb(res);
	order.pb(res + 1);
	
	l = 0, r = 1e8, res = 1e8;
	while (l <= r) {
		int mid = (l + r) / 2;
		int cur = mxy, nxt = mxy;
		if (sz(ly)) ckmax(cur, ly.back() - mid), ckmax(nxt, ly.back() - mid - 1);
		if (sz(ry)) ckmax(cur, ry.back() + mid), ckmax(nxt, ry.back() + mid + 1);
		if (cur > nxt) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	order.pb(res);
	order.pb(res + 1);
	l = 0, r = 1e8, res = 1e8;
	while (l <= r) {
		int mid = (l + r) / 2;
		int cur = mxy, nxt = mxy;
		if (sz(ly)) ckmax(cur, ly.back() - mid), ckmax(nxt, ly.back() - mid - 1);
		if (sz(ry)) ckmax(cur, ry.back() + mid), ckmax(nxt, ry.back() + mid + 1);
		if (cur >= nxt) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	order.pb(res);
	order.pb(res + 1);
	
	l = 0, r = 1e8, res = 1e8;
	while (l <= r) {
		int mid = (l + r) / 2;
		int cur = mix, nxt = mix;
		if (sz(lx)) ckmin(cur, lx.front() - mid), ckmin(nxt, lx.front() - mid - 1);
		if (sz(rx)) ckmin(cur, rx.front() + mid), ckmin(nxt, rx.front() + mid + 1);
		if (cur < nxt) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	order.pb(res);
	order.pb(res + 1);
	l = 0, r = 1e8, res = 1e8;
	while (l <= r) {
		int mid = (l + r) / 2;
		int cur = mix, nxt = mix;
		if (sz(lx)) ckmin(cur, lx.front() - mid), ckmin(nxt, lx.front() - mid - 1);
		if (sz(rx)) ckmin(cur, rx.front() + mid), ckmin(nxt, rx.front() + mid + 1);
		if (cur <= nxt) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	order.pb(res);
	order.pb(res + 1);
	
	l = 0, r = 1e8, res = 1e8;
	while (l <= r) {
		int mid = (l + r) / 2;
		int cur = miy, nxt = miy;
		if (sz(ly)) ckmin(cur, ly.front() - mid), ckmin(nxt, ly.front() - mid - 1);
		if (sz(ry)) ckmin(cur, ry.front() + mid), ckmin(nxt, ry.front() + mid + 1);
		if (cur < nxt) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	order.pb(res);
	order.pb(res + 1);
	l = 0, r = 1e8, res = 1e8;
	while (l <= r) {
		int mid = (l + r) / 2;
		int cur = miy, nxt = miy;
		if (sz(ly)) ckmin(cur, ly.front() - mid), ckmin(nxt, ly.front() - mid - 1);
		if (sz(ry)) ckmin(cur, ry.front() + mid), ckmin(nxt, ry.front() + mid + 1);
		if (cur <= nxt) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	order.pb(res);
	order.pb(res + 1);
	
	sort(all(order)), order.resize(unique(all(order)) - order.begin());
	auto calc = [&](int x) -> ll {
		int maxx = mxx, minx = mix;
		if (sz(lx)) ckmax(maxx, lx.back() - x), ckmin(minx, lx.front() - x);
		if (sz(rx)) ckmax(maxx, rx.back() + x), ckmin(minx, rx.front() + x);
		int maxy = mxy, miny = miy;
		if (sz(ly)) ckmax(maxy, ly.back() - x), ckmin(miny, ly.front() - x);
		if (sz(ry)) ckmax(maxy, ry.back() + x), ckmin(miny, ry.front() + x);
		return 1LL * (maxx - minx) * (maxy - miny);
	};
	for (auto &x : order) {
		ckmin(ans, calc(x));
	}
	ans *= 25;
	
	if (ans % 100) {
		if (ans % 50) {
			cout << ans / 100 << '.' << ans % 100;
		}else cout << ans / 100 << '.' << 5;
	}else cout << ans / 100;
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