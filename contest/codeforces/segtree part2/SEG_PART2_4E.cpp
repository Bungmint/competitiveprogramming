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

template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
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

struct custom_hash
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;

struct LazySegTree{
	struct Node{
		int mi, mx;
	};
	struct Range{
		int lo, hi;
		bool operator==(Range r){
			return r.lo==lo&&r.hi==hi;
		}
	};
	
	const Node seg_initial = {0,0};
	const Range seg_lazy_sentinel = {0, INF};
	const Node NEUTRAL = {INF,0};
	ll sz;
	vector<Node> t;
	vector<Range> lazy;
	
	
	// Change the inline function accordingly to the q
	inline Node merge(Node a, Node b){
		return {min(a.mi, b.mi), max(a.mx, b.mx)};
	}
	inline Range lazy_apply(Range lazy_val, int new_val, int ty){
		if (ty==1){
			return {max(lazy_val.lo, new_val), max(lazy_val.hi, new_val)};
		}else{
			dbg(lazy_val , new_val);
			return {min(lazy_val.lo, new_val), min(lazy_val.hi, new_val)};
		}
	}
	inline Range lazy_apply(Range lazy_val, Range new_val){
		dbg(lazy_val, new_val);
		if (lazy_val.hi<new_val.lo) return {new_val.lo, new_val.lo};
		if (new_val.hi<lazy_val.lo) return {new_val.hi, new_val.hi};
		return {max(lazy_val.lo, new_val.lo), min(lazy_val.hi, new_val.hi)};
	}
	inline Node lazy_func(Node cur_val, Range lazy_val, ll l, ll r){
		if (lazy_val.hi<cur_val.mi) return {lazy_val.hi, lazy_val.hi};
		if (lazy_val.lo>cur_val.mx) return {lazy_val.lo, lazy_val.lo}; 
		return cur_val;
	}
	
	
	void init(int n){
		sz = 1;
		while(sz<n) sz*=2;
		t.assign(2*sz, seg_initial);
		lazy.assign(2*sz, seg_lazy_sentinel);
	}
	void seg_eval_lazy(int i, ll l, ll r)
	{
	    if (lazy[i].hi ==INF&&!lazy[i].lo)
	        return;
	
	    t[i] = lazy_func(t[i], lazy[i], l, r);
	    if (r-l>1)
	    {
	    	dbg(lazy[2*i+1]);
	        lazy[i * 2 + 1] = lazy_apply(lazy[i * 2 + 1], lazy[i]);
	        dbg(lazy[2*i+1]);
	       	lazy[i * 2 + 2] = lazy_apply(lazy[i * 2 + 2], lazy[i]);
	    }
	
	    lazy[i] = seg_lazy_sentinel;
	}
	Node upd(int x, int l, int r, int lx, int rx, int v, int ty)
	{
		seg_eval_lazy(x, lx, rx);
		if (lx>=r||rx<=l) return t[x];
		if (lx>=l&&rx<=r){
			lazy[x] = lazy_apply(lazy[x],v, ty);
			dbg(lazy[x], v, ty);
			seg_eval_lazy(x, lx ,rx);
			return t[x];
		}
		if (rx-lx==1) return t[x];
	    
	    int mid = (lx + rx) / 2;
	    Node a = upd(2*x+1, l, r, lx, mid, v, ty);
	    Node b = upd(2*x+2, l, r, mid, rx, v, ty);
	   	return t[x] = merge(a, b);
	}
	void upd(int l, int r, int v, int ty)
	{
	    upd(0, l, r, 0, sz, v, ty);
	}
	Node query(int l, int r, int x, int lx, int rx)
	{
		seg_eval_lazy(x, lx, rx);
	    if (lx >= r || rx <= l)
	        return NEUTRAL;
	    if (lx >= l && rx <= r)
	        return t[x];
	    int mid = (lx + rx) / 2;
	    Node a = query(l, r, 2 * x + 1, lx, mid);
	    Node b = query(l, r, 2 * x + 2, mid, rx);
	    return merge(a, b);
	}
	Node query(int l, int r)
	{
	    return query(l, r, 0, 0, sz);
	}
};

ostream& operator<<(ostream& os, LazySegTree::Node nod){
	os <<"{"<< nod.mi << " "<< nod.mx <<"}";
	return os;
}
ostream& operator<<(ostream& os, LazySegTree::Range nod){
	os <<"{"<< nod.lo << " "<< nod.hi <<"}";
	return os;
}

void solve()
{
	LazySegTree st;
	int n, k;
	cin >> n >> k;
	st.init(n);
	while(k--){
		int t, l, r, h;
		cin >> t>>l >> r >> h;
		r++;
		if (t==1){
			st.upd(l, r, h, 1);
		}else{
			st.upd(l, r, h, 2);
		}
	}
	for (int i=0;i<n;++i){
		cout << st.query(i, i+1).mi << "\n";
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