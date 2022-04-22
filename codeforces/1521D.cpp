// Problem: D. Nastia Plays with a Tree
// Contest: Codeforces - Codeforces Round #720 (Div. 2)
// URL: https://codeforces.com/contest/1521/problem/D
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

void solve()
{
	int n;
	cin >> n;
	vector<vi> g(n);
	REP(n - 1) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].pb(v), g[v].pb(u);
	}
	vector<vi> dp(n, vi(2, INF));
	vector<bool> leaf(n);
	auto calc = [&](int v) -> int {
		return dp[v][0] - min(dp[v][0], dp[v][1]);
	};
	auto dfsInit = y_combinator([&](auto dfsInit, int u, int pu) -> void {
		int minSum{}, cnt{};
		for (auto &v : g[u]) {
			if (v != pu) {
				dfsInit(v, u);
				minSum += min(dp[v][0], dp[v][1]) + 1;
				cnt++;
			}
		}
		leaf[u] = !(cnt);
		if (!cnt) {
			dp[u][0] = 0;
			return;
		}
		sort(all(g[u]), [&](int i, int j) {
			if (i == pu) return false;
			if (j == pu) return true;
			return calc(i) < calc(j);
		});
		dp[u][0] = minSum - 1 + calc(g[u][0]);
		if (cnt > 1) dp[u][1] = minSum - 2 + calc(g[u][0]) + calc(g[u][1]);
	});
	dfsInit(0, -1);
	vpi toCut, toGlue;
	auto cut = y_combinator([&](auto cut, int u, int pu, bool add) -> pii {
		if (leaf[u]) {
			if (add) ;
			else if (!add) {
				toGlue.pb({u, u});
			}
			return {u, u};
		}
		if (add) {
			int ch = g[u][0];
			pii tmp = cut(ch, u, 1);
			for (auto &v : g[u]) {
				if (v != ch && v != pu) {
					toCut.pb({v, u});
					cut(v, u, 0);
				}
			}
			return {u, tmp.se};
		}
		if (dp[u][0] < dp[u][1]) {
			int ch = g[u][0];
			pii tmp = cut(ch, u, 1);
			for (auto &v : g[u]) {
				if (v != ch && v != pu) {
					toCut.pb({v, u});
					cut(v, u, 0);
				}
			}
			toGlue.pb({u, tmp.se});
			return {u, tmp.se};
		}else{
			int ch1 = g[u][0], ch2 = g[u][1];
			pii t1 = cut(ch1, u, 1), t2 = cut(ch2, u, 1);
			for (auto &v : g[u]) {
				if (v != ch1 && v != ch2 && v != pu) {
					toCut.pb({v, u});
					cut(v, u, 0);
				}
			}
			toGlue.pb({t1.se, t2.se});
			return {t1.se, t2.se};
		}	
	});
	cut(0, -1, 0);
	dbg(toGlue, toCut);
	cout << sz(toCut) << "\n";
	F0R(i, sz(toCut)) {
		auto [u, v] = toCut[i];
		auto w = toGlue[i].se;
		auto z = toGlue[i + 1].fi;
		cout << u + 1 << " " << v + 1 << " " << w + 1 << " " << z + 1 << "\n";
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