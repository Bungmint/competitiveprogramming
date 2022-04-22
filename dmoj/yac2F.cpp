// Problem: P6 - Travel Budget
// Contest: DMOJ - Yet Another Contest 2
// URL: https://dmoj.ca/problem/yac2p6
// Memory Limit: 512 MB
// Time Limit: 1000 ms
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

struct Line {
	bool type;
	double x;
	ll m, c;
};

bool operator<(Line l1, Line l2) {
	if (l1.type || l2.type) return l1.x < l2.x;
	return l1.m > l2.m;
}

set<Line> cht;

bool has_prev(set<Line>::iterator it) {
	return it != cht.begin();
}
bool has_next(set<Line>::iterator it) {
	return it != cht.end() && next(it) != cht.end();
}

double intersect(set<Line>::iterator l1, set<Line>::iterator l2) {
	return (double)(l1->c - l2->c) / (l2->m - l1->m);
}

void calc_x(set<Line>::iterator it) {
	if (has_prev(it)) {
		Line l = *it;
		l.x = intersect(prev(it), it);
		cht.insert(cht.erase(it), l);
	}
}

bool bad(set<Line>::iterator it) {
	if (has_next(it) && next(it)->c <= it->c) return true;
	return (has_prev(it) && has_next(it) &&
			intersect(prev(it), next(it)) <= intersect(prev(it), it));
}

void add_line(ll m, ll c) {
	set<Line>::iterator it;

	it = cht.lower_bound({0, 0, m, c});
	if (it != cht.end() && it->m == m) {
		if (it->c <= c) return;
		cht.erase(it);
	}

	it = cht.insert({0, 0, m, c}).first;
	if (bad(it)) cht.erase(it);
	else {
		while (has_prev(it) && bad(prev(it))) cht.erase(prev(it));
		while (has_next(it) && bad(next(it))) cht.erase(next(it));

		if (has_next(it)) calc_x(next(it));
		calc_x(it);
	}
}

ll query(ll h) {
	Line l = *prev(cht.upper_bound({1, (double)h, 0, 0}));
	return l.m * h + l.c;
}

void solve()
{
	int n;
	cin >> n;
	vl dp(n, LINF);
	vl p(n), s(n), c(n), d(n);
	F0R(i, n) {
		cin >> p[i] >> s[i] >> c[i] >> d[i];
	}
	dp[0] = 0;
	if (n <= 2000) {
		F0R(i, n) F0R(j, i) {
			if (p[j] + s[j] >= p[i])ckmin(dp[i], dp[j] + d[j] - p[j] * c[j] + p[i] * c[j]);
		}
		cout << dp[n - 1] << "\n";
		return;
	}
	FOR(i, 1, n) {
		add_line(c[i - 1], dp[i - 1] + d[i - 1] - p[i - 1] * c[i - 1]);
		dp[i] = query(p[i]);
	}
	cout << dp[n - 1] << "\n";
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