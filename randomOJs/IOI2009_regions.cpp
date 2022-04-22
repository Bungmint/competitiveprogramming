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

const int N = 2e5, R = 25000;
const int B = 450;
vi adj[N];
int region[N], tin[N], tout[N];
vi reg[R];
int n, r, q, timer;
int co;
pll cache[N / B][R];
int id[R];
int ts[N];
bool isBig[R];

void dfs(int u, int pu) {
	tin[u] = timer++;
	reg[region[u]].pb(u);
	for (auto &v : adj[u]) if (v != pu)	dfs(v, u);
	tout[u] = timer - 1;
}
inline ll calc(int i, int j) { // i - supervisor, j - employee
	int ptr = 0;
	ll res = 0;
	int en = -1;
	F0R(x, sz(reg[j])) {
		int cur = tin[reg[j][x]];
		while (en >= 0 && tout[ts[en]] < cur) en--;
		while (ptr < sz(reg[i]) && tin[reg[i][ptr]] <= cur) {
			if (tout[reg[i][ptr]] >= cur) ts[++en] = (reg[i][ptr]);
			ptr++;
		}
		res += en + 1;
	}
	return res;
}

void solve()
{
	cin >> n >> r >> q;
	F0R(i, n) {
		if (i == 0) {
			cin >> region[i], region[i]--;
		}else{
			int p;
			cin >> p >> region[i];
			region[i]--, p--;
			adj[p].pb(i), adj[i].pb(p);
		}
	}
	dfs(0, -1);
	vi big;
	F0R(i, r) {
		if (sz(reg[i]) >= B) {
			big.pb(i);
			isBig[i] = 1;
		}
	}
	for (auto &rr : big) {
		id[rr] = co++;
		F0R(i, r) {
			if (i == rr) continue;
			cache[id[rr]][i] = {calc(rr, i), calc(i, rr)};
		}
	}
	REP(q) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		int res = {};
		if (isBig[u]) {
			res = cache[id[u]][v].fi;
		}else if (isBig[v]) {
			res = cache[id[v]][u].se;
		}else{
			res = calc(u, v);
		}
		cout << res << endl;
	}
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