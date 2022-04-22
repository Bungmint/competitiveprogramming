// Problem: Robot Path
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1742
// Memory Limit: 512 MB
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
 
template<typename T, typename Merge = plus<T>>
struct SegTree{
	int sz;
	const Merge merge;
	vector<T> t;
	SegTree(int n) : merge(Merge()) {
		sz = 1;
		while (sz<n) sz*=2;
		t.resize(sz*2);
	}
	void build(vector<T> &vec, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        if (l < (int)vec.size())
	            t[x] = vec[l];
	        return;
	    }
	    int mid = (l + r) / 2;
	    build(vec, 2 * x + 1, l, mid);
	    build(vec, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void build(vector<T> &vec)
	{
	    build(vec, 0, 0, sz);
	}
	void upd(int i, const T& v, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        t[x] = v;
	        return;
	    }
	    int mid = (l + r) / 2;
	    if (i < mid)
	        upd(i, v, 2 * x + 1, l, mid);
	    else
	        upd(i, v, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void upd(int i, const T& v)
	{
	    upd(i, v, 0, 0, sz);
	}
	T query(int l, int r, int x, int lx, int rx)
	{
	    if (lx >= r || rx <= l)
	        return T();
	    if (lx >= l && rx <= r)
	        return t[x];
	    int mid = (lx + rx) / 2;
	    T a = query(l, r, 2 * x + 1, lx, mid);
	    T b = query(l, r, 2 * x + 2, mid, rx);
	    return merge(a, b);
	}
	T query(int l, int r)
	{
	    return query(l, r, 0, 0, sz);
	}
	void clear() {
		t.assign(sz * 2, T());
	}
};
 
struct Min {
	int x;
	Min(int x_ = INF) : x(x_) {}
	Min operator+(const Min& other) const {
		return {min(x, other.x)};
	}
};
 
#define int long long
struct Line {
	pll a, b;
	int id;
	Line() : id(-1) {}
	Line(pll x, pll y, int z) : a(x), b(y), id(z) {}
};
 
 
vl xs{{0}}, ys{{0}};
int getX(ll x) {
	return lb(all(xs), x) - xs.begin();
}
int getY(ll y) {
	return lb(all(ys), y) - ys.begin();
}
void insert_x(ll x) {
	xs.pb(x);
}
void insert_y(ll y) {
	ys.pb(y);
}
 
set<pair<char, char>> tt {{'L', 'R'}, {'U', 'D'}};
 
void solve()
{
	int n;
	cin >> n;
	pll cur = {0, 0};
	vl pref(n + 1);
	vi meet(n + 1, INF);
	vector<Line> a(n + 1);
	vector<Line> hori, vert;
	a[0] = {{0, 0}, {0, 0}, 0};
	char last{'a'};
	ll pos = LINF;
	FOR(i, 1, 1 + n) {
		char c;
		cin >> c;
		ll v;
		cin >> v;
		pll nxt;
		bool z = (c == 'L' || c == 'R');
		if (z) {
			int mul = (c == 'L' ? -1 : 1);
			nxt = {cur.fi + mul * v, cur.se};
			// cur.fi += mul;
		}else{
			int mul = (c == 'D' ? -1 : 1);
			nxt = {cur.fi, cur.se + mul * v};
			// cur.se += mul;
		}
		insert_x(nxt.fi);
		insert_y(nxt.se);
		// insert_x(cur.fi);
		// insert_y(cur.se);
		a[i] = {cur, nxt, i};
		if (z) hori.pb(a[i]);
		else vert.pb(a[i]);
		cur = nxt;
		pref[i] = v;
		pref[i] += pref[i - 1];
		if (tt.count(make_pair(last, c)) || tt.count(make_pair(c, last))) {
			pos = pref[i - 1];
			break;
		}
		last = c;
	}
	sort(all(xs));
	sort(all(ys));
	xs.resize(unique(all(xs)) - xs.begin());
	ys.resize(unique(all(ys)) - ys.begin());
	dbg(xs);
	for (auto &[x, y, z] : a) {
		dbg(x, y, z);
		x.fi = getX(x.fi);
		x.se = getY(x.se);
		y.fi = getX(y.fi);
		y.se = getY(y.se);
	}
	hori.pb(a[0]);
	vector<vector<Line>> yy(sz(ys)), xx(sz(xs));
	vector<ar<int, 4>> yonx, xony;
	for (auto &e : hori) {
		e = a[e.id];
		yy[e.a.se].pb(e);
		ll m = min(e.a.fi, e.b.fi);
		ll z = max(e.a.fi, e.b.fi);
		xony.pb({m, e.a.se, e.id, 1});
		xony.pb({z, e.a.se, e.id, -1});
	}
	for (auto &e : vert) {
		e = a[e.id];
		xx[e.a.fi].pb(e);
		ll m = min(e.a.se, e.b.se);
		ll z = max(e.a.se, e.b.se);
		yonx.pb({m, e.a.fi, e.id, 1});
		yonx.pb({z, e.a.fi, e.id, -1});
	}
	SegTree<Min> st1(sz(xs)), st2(sz(ys)), ts1(sz(xs)), ts2(sz(ys));
	vector<set<int>> storx(sz(xs)), story(sz(ys)), stx(sz(xs)), sty(sz(ys));
	sort(all(yonx)), sort(all(xony));
	int ptr = 0;
	F0R(i, sz(ys)) {
		vector<ar<int, 4>> toupd, toremove;
		while (ptr < sz(yonx) && yonx[ptr][0] == i) {
			auto &[y, x, id, tt] = yonx[ptr];
			if (tt == -1) toremove.pb(yonx[ptr]);
			else toupd.pb(yonx[ptr]);
			ptr++;
		}
		for (auto &[y, x, id, tt] : toupd) {
			storx[x].insert(id);
			st1.upd(x, *storx[x].begin());
		}
		vector<ar<int, 4>> qq;
		for (auto &e : yy[i]) {
			int x = min(e.a.fi, e.b.fi);
			int y = max(e.a.fi, e.b.fi);
			ckmin(meet[e.id], st1.query(x, y + 1).x);
			qq.pb({x, -1, e.id, y});
			qq.pb({y, 1, e.id, x});
		}
		sort(all(qq));
		F0R(j, sz(qq)) {
			vector<ar<int, 4>> toadd, toremover;
			if (qq[j][1] == -1) toadd.pb(qq[j]);
			else toremover.pb(qq[j]);
			while (j + 1 < sz(qq) && qq[j][0] == qq[j + 1][0]) {
				j++;
				if (qq[j][1] == -1) toadd.pb(qq[j]);
				else toremover.pb(qq[j]);
			}
			for (auto &[x, t, id, y] : toadd) {
				stx[x].insert(id);
				ts1.upd(x, *stx[x].begin());
			}
			for (auto &[x, t, id, y] : toremover){
				stx[y].erase(id);
				int z = (stx[y].empty() ? INF : *stx[y].begin());
				ts1.upd(y, z);
				stx[x].insert(id);
				ts1.upd(x, *stx[x].begin());
			}
			for (auto &[x, t, id, y] : toremover) {
				ckmin(meet[id], ts1.query(y, x + 1).x);
			}
		}
		for (auto &e : yy[i]) {
			int x = min(e.a.fi, e.b.fi);
			int y = max(e.a.fi, e.b.fi);
			if (stx[x].count(e.id)) {
				stx[x].erase(e.id);
				ts1.upd(x, INF);
			}
			if (stx[y].count(e.id)) {
				stx[y].erase(e.id);
				ts1.upd(y, INF);
			}
		}
		for (auto &[y, x, id, tt] : toremove) {
			storx[x].erase(id);
			int z = (storx[x].empty() ? INF : *storx[x].begin());
			st1.upd(x, z);
		}
	}
	
	ptr = 0;
	F0R(i, sz(xs)) {
		vector<ar<int, 4>> toupd, toremove;
		while (ptr < sz(xony) && xony[ptr][0] == i) {
			auto &[x, y, id, tt] = xony[ptr];
			if (tt == -1) toremove.pb(xony[ptr]);
			else toupd.pb(xony[ptr]);
			ptr++;
		}
		dbg(toupd, toremove);
		for (auto &[x, y, id, tt] : toupd) {
			story[y].insert(id);
			st2.upd(y, *story[y].begin());
		}
		vector<ar<int, 4>> qq;
		for (auto &e : xx[i]) {
			dbg(e.id);
			int x = min(e.a.se, e.b.se);
			int y = max(e.a.se, e.b.se);
			ckmin(meet[e.id], st2.query(x, y + 1).x);
			qq.pb({x, -1, e.id, y});
			qq.pb({y, 1, e.id, x});
		}
		sort(all(qq));
		F0R(j, sz(qq)) {
			vector<ar<int, 4>> toadd, toremover;
			if (qq[j][1] == -1) toadd.pb(qq[j]);
			else toremover.pb(qq[j]);
			while (j + 1 < sz(qq) && qq[j][0] == qq[j + 1][0]) {
				j++;
				if (qq[j][1] == -1) toadd.pb(qq[j]);
				else toremover.pb(qq[j]);
			}
			for (auto &[x, t, id, y] : toadd) {
				sty[x].insert(id);
				ts2.upd(x, *sty[x].begin());
			}
			for (auto &[x, t, id, y] : toremover){
				sty[y].erase(id);
				int z = (sty[y].empty() ? INF : *sty[y].begin());
				ts2.upd(y, z);
				sty[x].insert(id);
				ts2.upd(x, *sty[x].begin());
			}
			for (auto &[x, t, id, y] : toremover) {
				ckmin(meet[id], ts2.query(y, x + 1).x);
			}
			
		}
		for (auto &e : xx[i]) {
			int x = min(e.a.se, e.b.se);
			int y = max(e.a.se, e.b.se);
			if (sty[x].count(e.id)) {
				sty[x].erase(e.id);
				ts2.upd(x, INF);
			}
			if (sty[y].count(e.id)) {
				sty[y].erase(e.id);
				ts2.upd(y, INF);
			}
		}
		for (auto &[x, y, id, tt] : toremove) {
			story[y].erase(id);
			int z = (story[y].empty() ? INF : *story[y].begin());
			st2.upd(y, z);
		}
	}
	auto calc = [&](int i, int j) -> ll {
		auto [x, y, __] = a[i];
		auto [z, w, ___] = a[j];
		x.fi = xs[x.fi], x.se = ys[x.se];
		y.fi = xs[y.fi], y.se = ys[y.se];
		z.fi = xs[z.fi], z.se = ys[z.se];
		w.fi = xs[w.fi], w.se = ys[w.se];
		if (x.fi == y.fi && z.fi == w.fi) {
			if (x.fi != z.fi) return LINF;
			if (max(x.se, y.se) < min(z.se, w.se) || max(z.se, w.se) < min(x.se, y.se)) return LINF;
			return min(abs(z.se - x.se), abs(z.se - y.se));
		}else if (x.fi == y.fi) {
			int l = min(z.fi, w.fi);
			int r = max(z.fi, w.fi);
			if (z.se < min(x.se, y.se) || z.se > max(x.se, y.se)) return LINF;
			if (x.fi < l || x.fi > r) return LINF;
			return abs(z.fi - x.fi);
		}else if (z.fi == w.fi) {
			dbg(x, y, z, w);
			if (x.se < min(z.se, w.se) || x.se > max(z.se, w.se)) return LINF;
			if (z.fi < min(x.fi, y.fi) || z.fi > max(x.fi, y.fi)) return LINF;
			return abs(z.se - x.se);
		}else{
			if (x.se != z.se) return LINF;
			if (max(x.fi, y.fi) < min(z.fi, w.fi) || max(z.fi, w.fi) < min(x.fi, y.fi)) return LINF;
			return min(abs(z.fi - y.fi), abs(z.fi - x.fi));
		}
	};
	dbg(meet);
	F0R(i, n + 1) {
		if (meet[i] < i - 1) {
			dbg(i, pref[i - 1]);
			ll ans = pref[i - 1];
			ll ex = LINF;
			// dbg(calc(3, i));
			// dbg(calc(6, i));
			ROF(j, 0, i - 1) {
				ckmin(ex, calc(j, i));
				dbg(ex);
			}
			cout << min(ans + ex, pos) << '\n';
			return;
		}
	}
	cout << pref[n] << '\n';
}
 
int32_t main()
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