// Problem: D. Ezzat and Grid
// Contest: Codeforces - Codeforces Round #737 (Div. 2)
// URL: https://codeforces.com/contest/1557/problem/D
// Memory Limit: 256 MB
// Time Limit: 2500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
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

#define all(v) (v).begin(), (v).end()
#define ar array
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
#define dbg(...)
#endif

struct chash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
    size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

#define int long long

struct node{
	int min, x;
};

template<typename T>
struct LazySegTree{
	const T seg_initial = {LINF, 0};
	const node seg_lazy_sentinel = {LINF,0};
	const T NEUTRAL = {LINF,0};
	int sz;
	vector<T> t;
	vector<node> lazy;
	
	
	// Change the inline function accordingly to the q
	inline T merge(T a, T b){
		if (a.min<=b.min) return a;
		else return b;
	}
	inline node lazy_apply(node lazy_val, ll new_val,int par){
		if (new_val<=lazy_val.min) return {new_val, par};
		else return lazy_val;
	}
	inline node lazy_apply(node lazy_val, node new_val){
		if (new_val.min<=lazy_val.min) return new_val;
		else return lazy_val;
	}
	inline T lazy_func(T cur_val, node lazy_val, ll l, ll r){
		if (cur_val.min<=lazy_val.min) return cur_val;
		else return lazy_val;
	}
	
	
	void init(int n){
		sz = 1;
		while(sz<n) sz*=2;
		t.assign(2*sz, seg_initial);
		lazy.assign(2*sz, seg_lazy_sentinel);
	}
	void seg_eval_lazy(int i, ll l, ll r)
	{
	    if (lazy[i].min == LINF)
	        return;
	
	    t[i] = lazy_func(t[i], lazy[i], l, r);
	
	    if (r-l>1)
	    {
	        lazy[i * 2 + 1] = lazy_apply(lazy[i * 2 + 1], lazy[i]);
	       	lazy[i * 2 + 2] = lazy_apply(lazy[i * 2 + 2], lazy[i]);
	    }
	
	    lazy[i] = seg_lazy_sentinel;
	}
	T upd(int x, int l, int r, int lx, int rx, int v, int par)
	{
		seg_eval_lazy(x, lx, rx);
		if (lx>=r||rx<=l) return t[x];
		if (lx>=l&&rx<=r){
			lazy[x] = lazy_apply(lazy[x],v, par);
			seg_eval_lazy(x, lx ,rx);
			return t[x];
		}
		if (rx-lx==1) return t[x];
	    
	    int mid = (lx + rx) / 2;
	    T a = upd(2*x+1, l, r, lx, mid, v, par);
	    T b = upd(2*x+2, l, r, mid, rx, v, par);
	   	return t[x] = merge(a, b);
	}
	void upd(int l, int r, int v, int par)
	{
	    upd(0, l, r, 0, sz, v, par);
	}
	T query(int l, int r, int x, int lx, int rx)
	{
		seg_eval_lazy(x, lx, rx);
	    if (lx >= r || rx <= l)
	        return NEUTRAL;
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
};


struct seg{
	int l, r;
};

const int MX = 5e5+3;
ll dp[MX], dp2[MX];
int par[MX], par2[MX];

void solve()
{
	 int n, m;
	 cin >> n >> m;
	 vector<vector<seg>> rows(n+1);
	 LazySegTree<node> st, back;
	 st.init(2*MX), back.init(2*MX);
	 vi order;
	 F0R(i, m){
	 	int id, l, r;
	 	cin >> id >> l >> r;
	 	rows[id].pb({l,r});
	 	order.pb(l), order.pb(r);
	 }
	 sort(all(order)), order.resize(unique(all(order))-order.begin());
	 dp[0] = 0;
	 FOR(row, 1, n+1){
	 	dp[row] = row-1;
	 	par[row] = 0;
	 	for (auto &[l, r]: rows[row]){
	 		l = lb(all(order), l)-order.begin();
	 		r = lb(all(order), r)- order.begin();
	 		node q = st.query(l, r+1);
	 		if (ckmin(dp[row], row+q.min-1)) par[row] = q.x;
	 	}
	 	int cnt=0;
	 	for (auto &[l, r]: rows[row]){
	 		st.upd(l, r+1, dp[row]-row, row);
	 		cnt++;
	 	}
	 }
	 
	 
	 
	 
	 ll ans = LINF;
	 int last = 0;
	 FOR(row, 1, n+1){
	 	if (ckmin(ans, dp[row]+n-row)) last = row;
	 }
	 cout << ans << endl;
	 vi removed;
	 FOR(i, last+1, n+1) removed.pb(i);
	 while(last!=0){
	 	int prev = par[last];
	 	dbg(last, prev);
	 	FOR(i, prev+1, last) removed.pb(i);
	 	last = prev;
	 }
	 for (int x: removed)cout << x << " ";
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}