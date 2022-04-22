// Problem: D1. Too Many Impostors (easy version)
// Contest: Codeforces - Codeforces Round #761 (Div. 2)
// URL: https://codeforces.com/contest/1617/problem/D1
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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

int ask(int a, int b, int c) {
	cout << "? " << a << ' ' << b << ' ' << c << endl;
	int x;
	cin >> x;
	return x;
}
void print(vi &a) {
	cout << "! " << sz(a);
	for (auto &e : a) cout << ' ' << e;
	cout << endl;
}
// Zero: imposter, one: crew

void solve()
{
	int n;
	cin >> n;
	int m = n / 3;
	vi a(m + 1);
	int imp, crew;
	FOR(i, 1, m + 1) {
		a[i] = ask(3 * i - 2, 3 * i - 1, 3 * i);
		if (a[i]) crew = i;
		else imp = i;
	}
	int x = imp * 3 - 2, y = crew * 3 - 2;
	int ii, cc;
	set<int> st;
	vi xx(2), yy(2);
	vi ans;
	FOR(i, 1, 3) {
		xx[i - 1] = ask(x, y, x + i);
		yy[i - 1] = ask(x, y, y + i);
		st.insert(xx[i - 1]);
		st.insert(yy[i - 1]);
	}
	if (sz(st) == 1) {
		if (*st.begin() == 0) ans.pb(x), ans.pb(y);
		st.clear();
		x++, y++;
		st.insert(ask(x, y, x - 1));
		st.insert(ask(x, y, y - 1));
		st.insert(ask(x, y, x + 1));
		st.insert(ask(x, y, y + 1));
		if (sz(st) == 1) {
			ii = x + 1, cc = y + 1;
			if (*st.begin() == 0) ans.pb(x), ans.pb(y);
			ans.pb(ii);
		}else{
			ii = x, cc = y;
			int k = ask(ii, cc, x + 1);
			if (!k) ans.pb(x + 1);
			k = ask(ii, cc, y + 1);
			if (!k) ans.pb(y + 1);
			ans.pb(ii);
		}
	}else{
		FOR(i, 1, 3) {
			if (xx[i - 1]) cc = x + i;
			else ii = x + i, ans.pb(x + i);
			if (yy[i - 1]) cc = y + i;
			else ii = y + i, ans.pb(y + i);
		}
		int k = ask(ii, cc, x);
		if (!k) ans.pb(x);
		k = ask(ii, cc, y);
		if (!k) ans.pb(y);
	}
	dbg(ii, cc);
	FOR(i, 1, m + 1) {
		if (i == imp || i == crew) {
			continue;
		}
		if (a[i]) {
			int k = ask(ii, 3 * i - 2, 3 * i - 1);
			if (k) {
				int kk = ask(ii, cc, 3 * i);
				if (!kk) ans.pb(3 * i);
			}else{
				int kk = ask(ii, cc, 3 * i - 2);
				if (!kk) ans.pb(3 * i - 2);
				else ans.pb(3 * i - 1);
			}
		}else{
			int k = ask(cc, 3 * i - 2, 3 * i - 1);
			if (k) {
				int kk = ask(ii, cc, 3 * i - 2);
				ans.pb(3 * i);
				if (!kk) ans.pb(3 * i - 2);
				else ans.pb(3 * i - 1);
			}else{
				ans.pb(3 * i - 2);
				ans.pb(3 * i - 1);
				int kk = ask(ii, cc, 3 * i);
				if (!kk) ans.pb(3 * i);
			}
		}
	}
	print(ans);
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