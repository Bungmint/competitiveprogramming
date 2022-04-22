// Problem: Path Queries
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1138
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

// Uses zero index for the input
template<typename T>
struct BIT{
	int N, lg;
	vector<T> bit;
	BIT(int n) { bit.resize(n+1); N = n; lg=log2(N);}
	void upd(int i, T v){ 
		for (++i; i <= N; i += i & -i) bit[i] += v;	
	}
	T query(int i){
		T res = 0;
		for (++i; i > 0; i -= i & -i) res += bit[i];
		return res;
	}
	T range_query(int l, int r) {
		return query(r) - query(l - 1);
	}
	int lower_bound(T v){
		T sum = 0, id = 0;
		R0F(i, lg + 1){
			if (id + (1 << i) <= N && sum + bit[id + (1 << i)] < v){
				sum += bit[id + (1 << i)];
				id += (1 << i);
			}
		}
		return id; // Zero index
		// return id+1; // One index
	}
};

const int N = 2e5;
int timer, tin[N], tout[N], a[N];
int n, q;
vi g[N];
BIT<ll> sum(2 * N);

void dfs(int u, int pu) {
	tin[u] = timer++;
	sum.upd(tin[u], a[u]);
	for (auto &e : g[u]) {
		if (e != pu) dfs(e, u);
	}
	tout[u] = timer++;
	sum.upd(tout[u], -a[u]);
}

void solve()
{
	cin >> n >> q;
	F0R(i, n) cin >> a[i];
	REP(n - 1) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].pb(v), g[v].pb(u);
	}
	dfs(0, -1);
	REP(q) {
		int t;
		cin >> t;
		if (t == 1) {
			int s, x;
			cin >> s >> x;
			s--;
			sum.upd(tin[s], x - a[s]);
			sum.upd(tout[s], a[s] - x);
			a[s] = x;
		}else{
			int s;
			cin >> s;
			s--;
			cout << sum.range_query(0, tin[s]) << "\n";
		}
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