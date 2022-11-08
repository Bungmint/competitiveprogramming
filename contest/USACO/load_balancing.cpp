// Problem: Problem 1. Load Balancing
// Contest: USACO - USACO 2016 February Contest, Platinum
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=624
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

template<typename T>
struct SegTree{

	int sz;
	vector<T> t;
	T single(int v, int tt){T res = {0,0}; if (tt)res.b=v; else res.a=v; return res;}
	T NEUTRAL = {0,0}; //ALSO HAS TO CHANGE
	T merge(T a, T b){
		return {a.a+b.a, a.b+b.b};
	}
	
	void init(int n){
		sz = 1;
		while(sz<n) sz*=2;
		t.resize(sz*2);
	}
	void upd(int i, int v, int tt, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        t[x] = merge(t[x], single(v, tt));
	        return;
	    }
	    int mid = (l + r) / 2;
	    if (i < mid)
	        upd(i, v,tt, 2 * x + 1, l, mid);
	    else
	        upd(i, v,tt, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void upd(int i, int v, int tt)
	{
	    upd(i, v, tt, 0, 0, sz);
	}
	int find(int x, int lx, int rx, int l1, int r1, int l2, int r2){
		if (rx-lx==1){
			auto [a,b] = t[x];
			(l1<r1? l1:r1) += a;
			(l2<r2? l2:r2) += b;
			return max({l1,l2,r1,r2});
		}
		int mid = (lx+rx)>>1;
		auto [a,b] = t[2*x+1];
		auto [c,d] = t[2*x+2];
		if (max(l1+a,l2+b)<max(r1+c, r1+d)){
			return find(2*x+2, mid, rx, l1+a, r1, l2+b, r2);
		}else{
			return find(2*x+1, lx, mid, l1, r1+c, l2, r2+d);
		}
	}
	int find(){
		return find(0,0,sz, 0,0,0,0);
	}
};

struct Point{
	int x, y;
};

struct Node{
	int a, b;
};

void solve()
{
	int n;
	scanf("%d",&n);
	vector<Point> p(n);
	vector<vi> xCoord(n*2);
	vi order;
	for (int i=0;i<n;++i){
		int x, y;
		scanf("%d%d",&x, &y);
		p[i] = {x,y};
		order.pb(x), order.pb(y);
	}
	sort(all(order)), order.resize(unique(all(order))-order.begin());
	for (int i=0;i<n;++i){
		p[i] = {(int)(lb(all(order), p[i].x)-order.begin()), (int)(lb(all(order), p[i].y)-order.begin())};
		xCoord[p[i].x].pb(p[i].y);
	}
	SegTree<Node> st;
	st.init(n*2);
	for (int i=0;i<n;++i){
		st.upd(p[i].y, 1, 1);
	}
	int res = st.find();
	for (int i=0;i<2*n;++i){
		for (int y:xCoord[i]){
			st.upd(y,1, 0);
			st.upd(y,-1, 1);
		}
		res = min(res, st.find());
	}
	cout << res << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    setIO("balancing");
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}