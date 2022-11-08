// Problem: F. Mountain
// Contest: Codeforces - ITMO Academy: pilot course - Segment Tree, part 2 - Step 4
// URL: https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/F
// Memory Limit: 512 MB
// Time Limit: 2000 ms
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

struct node{
	int height, max,elev, length;
};
ostream& operator<<(ostream& os, node n){
	os<<n.height <<" "<< n.max << " "<< n.elev<<" "<<n.length<< "\n";
	return os;
}



struct LazySegTree{
	const node seg_initial = {0,0,0,0};
	const ll seg_lazy_sentinel = -2*INF;
	const node NEUTRAL = {0,0,0,0};
	ll sz;
	vector<node> t;
	vl lazy;
	
	
	// Change the inline function accordingly to the q
	inline node merge(node a, node b){
		return {
			a.height+b.height,
			max(a.max, a.height+b.max),
			a.elev,
			a.length +b.length
		};
	}
	inline ll lazy_apply(ll lazy_val, ll new_val){
		return new_val;
	}
	inline node lazy_func(node cur_val, ll lazy_val, ll l, ll r){
		node res;
		res.height = cur_val.length*lazy_val;
		res.max = max(0, res.height);
		res.elev=lazy_val;
		res.length = cur_val.length;
		return res;
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
	void build(vector<node> &vec, int x, int l, int r)
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
	void build(vector<node> &vec)
	{
	    build(vec, 0, 0, sz);
	}
	node upd(int x, int l, int r, int lx, int rx, int v)
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
	    node a = upd(2*x+1, l, r, lx, mid, v);
	    node b = upd(2*x+2, l, r, mid, rx, v);
	   	return t[x] = merge(a, b);
	}
	void upd(int l, int r, int v)
	{
	    upd(0, l, r, 0, sz, v);
	}
	pair<pi,node> find(int h, int x, int lx, int rx){
		seg_eval_lazy(x, lx, rx);
		if (rx-lx==1){
			return {{lx, h}, t[x]};
		}
		int mid = (lx+rx)>>1;
		seg_eval_lazy(2*x+1, lx, mid);
		seg_eval_lazy(2*x+2, mid, rx);
		if (t[2*x+1].max>h) return find(h, 2*x+1, lx, mid);
		else return find(h-t[2*x+1].height,2*x+2, mid, rx);
	}
	pair<pi,node> find(int h){
		return find(h, 0,0,sz);
	}
	
};

struct Query{
	char c;
	int l, r, d, h;
};
ostream& operator<<(ostream& os, Query q){
	os<<q.c << " "<< q.l << " "<<q.r <<" "<< q.d <<" "<<q.h << "\n";
	return os;
}

void solve()
{
	int n;
	cin >> n;
	vector<Query> q;
	vi order;
	while(true){
		char c;
		cin >> c;
		Query s;
		if (c=='E') break;
		else if (c=='I'){
			int l, r, d;
			cin >> l >> r >> d;
			order.pb(l);
			order.pb(r);
			s = {c, l, r, d, 0};
		}else{
			int h;
			cin >> h;
			s = {c, 0,0,0, h};
		}
		q.pb(s);
	}
	order.pb(n);
	sort(all(order)), order.resize(unique(all(order))- order.begin());
	int cnt = sz(order);
	vector<node> v;
	for (int i=0;i<2*cnt-1;++i){
		if (i&1){
			v.pb({0,0,0,order[(i+1)/2]-order[i/2]-1});
		}else{
			v.pb({0,0,0,1});
		}
	}
	LazySegTree st;
	st.init(sz(v));
	st.build(v);
	for (Query& s:q){
		if (s.c =='I'){
			s.l = lb(all(order), s.l)-order.begin();
			s.l*=2;
			s.r = lb(all(order), s.r)-order.begin();
			s.r*=2;
			st.upd(s.l, s.r+1, s.d);
		}else{
			pair<pi,node> p  = st.find(s.h);
			auto [l, d] = p.fi;
			node nod = p.se;
			int ans = 0;
			if (l&1){
				if (l/2>=sz(order)) ans = n;
				else{
					ans = order[l/2];
					if (nod.elev<=0) ans += nod.length;
					else ans += min(nod.length, max(0, d/nod.elev));
				}
			}else{
				if (l/2>=sz(order)) ans = n;
				else{
					ans = order[l/2]-1;
					dbg(nod.length, d, nod.elev, ans);
					if (nod.elev<=0) ans += nod.length;
					else ans += min(nod.length, max(0, d/nod.elev));
				}
			}
			cout << ans << "\n";
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