// Problem: Polynomial Queries
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1736
// Memory Limit: 512 MB
// Time Limit: 1000 ms
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

struct LazySegTree{
	struct node{
		ll add, num;
	};
	const ll seg_initial = 0;
	const node seg_lazy_sentinel = {0,0};
	const ll NEUTRAL = 0;
	ll sz;
	vl t;
	vector<node>lazy;
	
	
	// Change the inline function accordingly to the q
	inline ll merge(ll a, ll b){
		return a+b;
	}
	inline node lazy_apply(node lazy_val, node new_val){
		return {
			lazy_val.add+new_val.add,
			lazy_val.num+new_val.num
		};
	}
	inline ll lazy_func(ll cur_val, node lazy_val, ll l, ll r){
		return cur_val + (2*lazy_val.add+(r-l-1)*lazy_val.num)*(r-l)/2LL;
	}
	
	
	void init(int n){
		sz = 1;
		while(sz<n) sz*=2;
		t.assign(2*sz, seg_initial);
		lazy.assign(2*sz, seg_lazy_sentinel);
	}
	void seg_eval_lazy(int i, ll l, ll r)
	{
	    if (lazy[i].add==0)
	        return;
	
	    t[i] = lazy_func(t[i], lazy[i], l, r);
		ll mid = (r+l)>>1;
	    if (r-l>1)
	    {
	        lazy[i * 2 + 1] = lazy_apply(lazy[i * 2 + 1], lazy[i]);
	        lazy[i].add += (r-mid)*lazy[i].num;
	       	lazy[i * 2 + 2] = lazy_apply(lazy[i * 2 + 2], lazy[i]);
	    }
	
	    lazy[i] = seg_lazy_sentinel;
	}
	void build(vector<int> &vec, int x, int l, int r)
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
	void build(vector<int> &vec)
	{
	    build(vec, 0, 0, sz);
	}
	ll upd(int x, int l, int r, int lx, int rx, int v)
	{
		seg_eval_lazy(x, lx, rx);
		if (lx>=r||rx<=l) return t[x];
		if (lx>=l&&rx<=r){
			node s = {v+lx-l,1};
			lazy[x] = lazy_apply(lazy[x],s);
			seg_eval_lazy(x, lx ,rx);
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
	ll query(int l, int r, int x, int lx, int rx)
	{
		seg_eval_lazy(x, lx, rx);
	    if (lx >= r || rx <= l)
	        return NEUTRAL;
	    if (lx >= l && rx <= r)
	        return t[x];
	    int mid = (lx + rx) / 2;
	    ll a = query(l, r, 2 * x + 1, lx, mid);
	    ll b = query(l, r, 2 * x + 2, mid, rx);
	    return merge(a, b);
	}
	ll query(int l, int r)
	{
	    return query(l, r, 0, 0, sz);
	}
};

void solve()
{
	int n, q;
	cin >> n >> q;
	vi a(n);
	LazySegTree st;
	st.init(n);
	for (int i=0;i<n;++i)cin >> a[i];
	st.build(a);
	for (int i=0;i<q;++i){
		int t,x,y;
		cin >> t >> x >> y;
		x--;
		if (t==1){
			st.upd(x,y,1);
		}else cout << st.query(x,y)<<"\n";
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