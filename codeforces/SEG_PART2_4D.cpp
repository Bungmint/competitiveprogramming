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
		ll wSum, sum;
	};
	
	const Node seg_initial = {0,0};
	const ll seg_lazy_sentinel = 0;
	const Node NEUTRAL = {0,0};
	ll sz;
	vector<Node> t;
	vl lazy;
	
	
	// Change the inline function accordingly to the q
	inline Node merge(Node a, Node b){
		return {a.wSum+b.wSum, a.sum + b.sum};
	}
	inline ll lazy_apply(ll lazy_val, ll new_val){
		return lazy_val+new_val;
	}
	inline Node lazy_func(Node cur_val, ll lazy_val, ll l, ll r){
		return {cur_val.wSum + (r-l)*(r+l-1)*lazy_val/2LL, cur_val.sum + (r-l)*lazy_val};
	}
	inline Node single(ll x, ll l){
		return {x*l, x};
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
		dbg(l, r, t[i], lazy[i]);
	    if (r-l>1)
	    {
	        lazy[i * 2 + 1] = lazy_apply(lazy[i * 2 + 1], lazy[i]);
	       	lazy[i * 2 + 2] = lazy_apply(lazy[i * 2 + 2], lazy[i]);
	    }
	
	    lazy[i] = seg_lazy_sentinel;
	}
	void build(vector<int> &vec, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        if (l < (int)vec.size())
	            t[x] = single(vec[l], l);
	        dbg(t[x]);
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
	    dbg(a, b, lx, rx);
	   	return t[x] = merge(a, b);
	}
	void upd(int l, int r, int v)
	{
	    upd(0, l, r, 0, sz, v);
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

ostream& operator<<(ostream& os, LazySegTree::Node n){
	os <<"{"<< n.wSum << " "<< n.sum<<"}";
	return os;
}

void solve()
{
	LazySegTree st;
	int n, m;
	cin >> n >> m;
	vi a(n);
	for (int i=0;i<n;++i) cin >> a[i];
	st.init(n);
	st.build(a);
	while(m--){
		int op;
		cin >> op;
		if (op==1){
			int l, r,d;
			cin >> l >> r >> d;
			l--;
			st.upd(l,r,d);
		}else{
			int l, r;
			cin >> l >> r;
			l--;
			LazySegTree::Node node = st.query(l,r);
			dbg(node);
			cout << node.wSum - node.sum*((ll)l-1LL)<<"\n";
		}
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