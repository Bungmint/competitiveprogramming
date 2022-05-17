//Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
#include "crocodile.h"
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

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[])
{
	vector<vpi> g(N);
	F0R(i, M) {
		g[R[i][0]].pb({R[i][1], L[i]});
		g[R[i][1]].pb({R[i][0], L[i]});
	}
	vpl dist(N, make_pair(LINF, LINF));
	pqg<pll> pq;
	F0R(i, K) {
		dist[P[i]] = {0, 0};
		pq.push({0, P[i]});
	}
	while (sz(pq)) {
		auto [d, u] = pq.top();
		pq.pop();
		if (d > dist[u].se) continue;
		for (auto &[v, w] : g[u]) {
			ll nxt = d + w;
			if (dist[v].fi > nxt) {
				if (dist[v].se != dist[v].fi) pq.push({dist[v].fi, v});
				dist[v].se = dist[v].fi;
				dist[v].fi = nxt;
			}else if (dist[v].se > nxt) {
				dist[v].se = nxt;
				pq.push({dist[v].se, v});
			}
		}
	}
	return dist[0].se;
}
// 
// void solve()
// {
	// int n, m, k;
	// cin >> n >> m >> k;
	// int r[m][2], l[m], p[k];
	// F0R(i, m) cin >> r[i][0] >> r[i][1];
	// F0R(i, m) cin >> l[i];
	// F0R(i, k) cin >> p[i];
	// cout << travel_plan(n, m, r, l, k, p);
// }
// 
// int main()
// {
    // cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    // int testcase=1;
    // // cin >> testcase;
    // while (testcase--)
    // {
        // solve();
    // }
// }