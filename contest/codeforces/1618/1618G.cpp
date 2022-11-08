// Problem: G. Trader Problem
// Contest: Codeforces - Codeforces Round #760 (Div. 3)
// URL: https://codeforces.com/contest/1618/problem/G
// Memory Limit: 512 MB
// Time Limit: 4500 ms
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

void solve()
{
	int n, m, q;
	cin >> n >> m >> q;
	vl ans(q), a(n), b(m);
	vpl c;
	vpl query(q);
	ll sum{};
	for (auto &e : a) cin >> e, c.pb({e, 1}), sum += e;
	for (auto &e : b) cin >> e, c.pb({e, 0});
	sort(all(c));
	vl pref(sz(c) + 1), cnt(sz(c) + 1);
	set<pii> range;
	set<pii> nxt;
	F0R(i, sz(c)) {
		pref[i + 1] = pref[i] + c[i].fi;
		cnt[i + 1] = cnt[i] + c[i].se;
		range.insert({i + 1, i + 1});
		if (i + 1 < sz(c)) {
			nxt.insert({c[i + 1].fi - c[i].fi, i + 1});
		}
	}
	F0R(i, q) {
		int x;
		cin >> x;
		query[i] = {x, i};
	}
	sort(all(query));
	auto calc = [&](int l, int r) ->ll {
		int c = cnt[r] - cnt[l - 1];
		return pref[r] - pref[r - c];
	};
	for (auto &[k, id] : query) {
		while (sz(nxt) && nxt.begin()->fi <= k) {
			auto [dif, ii] = *nxt.begin();
			nxt.erase(nxt.begin());
			auto it = range.lb({ii + 1, ii + 1});
			auto [l, r] = *it;
			it--;
			auto [x, y] = *it;
			range.erase(range.find({x, y}));
			range.erase(range.find({l, r}));
			range.insert({x, r});
			sum += calc(x, r) - calc(x, y) - calc(l, r);
		}
		ans[id] = sum;
	}
	for (auto &e : ans) cout << e << "\n";
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