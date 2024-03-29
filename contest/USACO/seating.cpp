// Problem: Problem 3. Seating
// Contest: USACO - USACO 2013 January Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=231
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

struct LazySegTree{
	struct Node{
		int pref, suf, sum, len;
	};
	const Node seg_initial = {0,0,0,0};
	const ll seg_lazy_sentinel = -1;
	const Node NEUTRAL = {0,0,0,0};
	ll sz;
	vector<Node> t;
	vl lazy;
	
	
	// Change the inline function accordingly to the q
	inline Node merge(Node a, Node b){
		Node res;
		res.pref = (a.sum==a.len? a.sum+b.pref:a.pref);
		res.suf = (b.sum==b.len? a.suf+b.sum:b.suf);
		res.sum = max({a.sum,b.sum, a.suf+b.pref});
		res.len = a.len+b.len;
		return res;
	}
	inline ll lazy_apply(ll lazy_val, ll new_val){
		return new_val;
	}
	inline Node lazy_func(Node cur_val, int lazy_val, int l, int r){
		if (!lazy_val) return {r-l,r-l,r-l,r-l}; 
		else return {0,0,0,r-l};
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
	Node upd(int x, int l, int r, int lx, int rx, int v)
	{
		seg_eval_lazy(x, lx, rx);
		if (lx>=r||rx<=l) return t[x];
		if (lx>=l&&rx<=r){
			lazy[x] = lazy_apply(lazy[x],v);
			seg_eval_lazy(x, lx ,rx);
			return t[x];
		}
		if (rx-lx==1) return t[x];
	    
	    int mid = (lx + rx) / 2;
	    Node a = upd(2*x+1, l, r, lx, mid, v);
	    Node b = upd(2*x+2, l, r, mid, rx, v);
	   	return t[x] = merge(a, b);
	}
	void upd(int l, int r, int v)
	{
	    upd(0, l, r, 0, sz, v);
	}
	
	int query(int k, int x, int lx, int rx)
	{
		seg_eval_lazy(x, lx, rx);
		if (t[x].sum<k) return -1;
		if (rx-lx==1){
			assert(k==1);
			upd(lx, rx, 1);
			return 0;
		}
	    int mid = (lx + rx) >>1;
	    seg_eval_lazy(2*x+1, lx, mid), seg_eval_lazy(2*x+2, mid,rx);
	    if (t[2*x+1].sum>=k) return query(k, 2*x+1, lx, mid);
	    else if (t[2*x+1].suf + t[2*x+2].pref>=k){
	    	upd(mid-t[2*x+1].suf, mid-t[2*x+1].suf+k, 1);
	    	return 0;
	    }
	    else return query(k, 2*x+2, mid, rx);
	}
	int query(int k)
	{
	    return query(k, 0, 0, sz);
	}
};

void solve()
{
	int n, m;
	cin >> n >>m;
	LazySegTree st;
	st.init(n);
	st.upd(0, n, 0);
	int ans = 0;
	for (int i=0;i<m;++i){
		char c;
		cin >> c;
		if (c=='L'){
			int l, r;
			cin >> l >> r;
			l--;
			st.upd(l, r, 0);
		}else{
			int p;
			cin >> p;
			if (st.query(p)==-1) ans++;
		}
	}
	cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    setIO("seating");
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}