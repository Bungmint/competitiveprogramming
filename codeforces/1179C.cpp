// Problem: C. Serge and Dining Room
// Contest: Codeforces - Codeforces Round #569 (Div. 1)
// URL: https://codeforces.com/contest/1179/problem/C
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;
using pl = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pl>;
using ld = long double;

#define all(v) (v).begin(), (v).end()
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound

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
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

const int MX = 1<<20;

struct LazySegTree{
	const ll seg_initial = 0;
	const ll seg_lazy_sentinel = 0;
	const ll NEUTRAL = 0;
	ll sz;
	vl t,lazy;
	
	
	// Change the inline function accordingly to the q
	inline ll merge(ll a, ll b){
		return max(a,b);
	}
	inline ll lazy_apply(ll lazy_val, ll new_val){
		return lazy_val+new_val;
	}
	inline ll lazy_func(ll cur_val, ll lazy_val, ll l, ll r){
		return cur_val + lazy_val;
	}
	
	
	void init(int n){
		sz = 1;
		while(sz<n) sz*=2;
		t.assign(2*sz, seg_initial);
		lazy.assign(2*sz, seg_lazy_sentinel);
	}
	void seg_eval_lazy(int i, ll l, ll r)
	{
	    if (lazy[i] == seg_lazy_sentinel)
	        return;
	
	    t[i] = lazy_func(t[i], lazy[i], l, r);
	
	    if (r-l>1)
	    {
	        lazy[i * 2 + 1] = lazy_apply(lazy[i * 2 + 1], lazy[i]);
	       	lazy[i * 2 + 2] = lazy_apply(lazy[i * 2 + 2], lazy[i]);
	    }
	
	    lazy[i] = seg_lazy_sentinel;
	}
	ll upd(int x, int l, int r, int lx, int rx, int v)
	{
		seg_eval_lazy(x, lx, rx);
		if (lx>=r||rx<=l) return t[x];
		if (lx>=l&&rx<=r){
			lazy[x] = lazy_apply(lazy[x],v);
			seg_eval_lazy(x, lx ,rx);
			dbg(t[x], x, lx, rx);
			if (rx-lx>1)dbg(t[2*x+2], lazy[2*x+2]);
			return t[x];
		}
		if (rx-lx==1) return t[x];
	    
	    int mid = (lx + rx) / 2;
	    ll a = upd(2*x+1, l, r, lx, mid, v);
	    ll b = upd(2*x+2, l, r, mid, rx, v);
	   	return t[x] = merge(a, b);
	}
	void upd(int l, int r, int v)
	{
	    upd(0, l, r, 0, sz, v);
	}
	ll query(int x, int lx, int rx)
	{
	   	if (rx-lx==1) return lx;
	    int mid = (lx + rx) >>1;
	    seg_eval_lazy(x, lx, rx);
		seg_eval_lazy(2*x+1, lx, mid);
		seg_eval_lazy(2*x+2, mid, rx);
	    if (t[2*x+2]>0) return query(2*x+2, mid, rx);
	    return query(2*x+1, lx, mid);
	}
	ll query()
	{
		if (t[0]<=0) return -1;
	    return query(0, 0, sz);
	}
};

void solve()
{
	int n, m;
	scanf("%d%d",&n, &m);
	vi a(n), b(m);
	LazySegTree st;
	st.init(MX);
	vi order;
	for (int i=0;i<n;++i) scanf("%d", &a[i]),order.pb(a[i]);
	for (int i=0;i<m;++i) scanf("%d", &b[i]), order.pb(b[i]);
	
	
	int q;
	scanf("%d", &q);
	vector<ar<int,3>> Q(q);
	for(int i=0;i<q;++i){
		int t, id, x;
		scanf("%d%d%d", &t, &id, &x);
		id--;
		Q[i] = {t, id, x};
		order.pb(x);
	}
	sort(all(order)), order.resize(unique(all(order))-order.begin());
	dbg(order);
	for (int i=0;i<n;++i) a[i] = lb(all(order), a[i])-order.begin(), st.upd(0, a[i]+1, 1);
	for (int i=0;i<m;++i) b[i] = lb(all(order), b[i])-order.begin(), st.upd(0, b[i]+1, -1);
	dbg(st.query());
	for (int i=0;i<q;++i) Q[i][2] = lb(all(order), Q[i][2])-order.begin();
	for (int i=0;i<q;++i){
		auto [t, id, x] = Q[i];
		if (t==1) st.upd(0, a[id]+1, -1), st.upd(0, x+1, 1), a[id] = x;
		else st.upd(0, b[id]+1, 1), st.upd(0, x+1, -1), b[id] = x;
		int k = st.query();
		cout << (k==-1? k:order[k])<<"\n";
	}
}

int main()
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