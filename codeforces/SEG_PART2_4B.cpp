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
	const ll seg_initial = 0;
	const pl seg_lazy_sentinel = {0,0};
	const ll NEUTRAL = 0;
	ll sz;
	vl t;
	vpl lazy;
	
	
	// Change the inline function accordingly to the q
	inline ll merge(ll a, ll b){
		return a+b;
	}
	inline pl lazy_apply(pl lazy_val, pl new_val){
		return {lazy_val.fi+new_val.fi, lazy_val.se+new_val.se};
	}
	inline ll lazy_func(ll cur_val, pl lazy_val, ll l, ll r){
		dbg(cur_val, l, r, lazy_val, cur_val + (ll)(r-l)*(ll)lazy_val.fi + (ll)(r-l-1)*(ll)(r-l)/2LL * (ll)lazy_val.se);
		return cur_val + (ll)(r-l)*(ll)lazy_val.fi + (ll)(r-l-1)*(ll)(r-l)/2LL * (ll)lazy_val.se;
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
		dbg(t[i], l, r);
	    t[i] = lazy_func(t[i], lazy[i], l, r);
	    dbg(t[i]);
		ll mid = (l+r)>>1;
	    if (r-l>1)
	    {
	        lazy[i * 2 + 1] = lazy_apply(lazy[i * 2 + 1], lazy[i]);
	       	lazy[i * 2 + 2] = lazy_apply(lazy[i * 2 + 2], make_pair(lazy[i].fi+(ll)lazy[i].se*(ll)(mid-l), lazy[i].se));
	    }
	
	    lazy[i] = seg_lazy_sentinel;
	}
	ll upd(int x, int l, int r, int lx, int rx, ll a, ll d)
	{
		seg_eval_lazy(x, lx, rx);
		if (lx>=r||rx<=l) return t[x];
		if (lx>=l&&rx<=r){
			lazy[x] = lazy_apply(lazy[x],make_pair(a+(ll)d*(ll)(lx-l),d));
			seg_eval_lazy(x, lx ,rx);
			return t[x];
		}
		if (rx-lx==1) return t[x];
	    
	    int mid = (lx + rx) / 2;
	    ll c = upd(2*x+1, l, r, lx, mid, a, d);
	    ll b = upd(2*x+2, l, r, mid, rx, a,d);
	   	return t[x] = merge(c, b);
	}
	void upd(int l, int r, ll a, ll d)
	{
	    upd(0, l, r, 0, sz, a, d);
	}
	ll query(int l, int r, int x, int lx, int rx)
	{
		seg_eval_lazy(x, lx, rx);
	    if (lx>=r||rx<=l) return NEUTRAL;
	    if (lx>=l&&rx<=r){
	    	return t[x];
	    }
	    int mid = (lx + rx)>>1;
	    ll a = query(l,r, 2*x+1, lx,mid);
	    ll b = query(l,r, 2*x+2, mid, rx);
	    return merge(a,b);
	}
	ll query(int l, int r)
	{
	    return query(l,r, 0, 0, sz);
	}
};

void solve()
{
	LazySegTree st;
	int n, m;
	cin >> n >> m;
	st.init(n);
	for (int i=0;i<m;++i){
		int op;
		cin >> op;
		if (op==1){
			ll l,r,a,d;
			cin >> l >> r >> a >> d;
			l--;
			st.upd(l,r,a,d);
		}else{
			int k;
			cin >> k;
			k--;
			cout << st.query(k, k+1)<<"\n";
		}
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase=1;
    //cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}