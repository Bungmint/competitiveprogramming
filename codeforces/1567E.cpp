// Problem: E. Non-Decreasing Dilemma
// Contest: Codeforces - Codeforces Round #742 (Div. 2)
// URL: https://codeforces.com/contest/1567/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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
#define dbg(...) 42
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

struct node{
	ll total, suf, pref, start, last, length;
};
ostream& operator << (ostream &os, node n){
	os << n.total<<" "<< n.suf<<" "<<n.pref <<" "<<n.start << " "<<n.last << " "<<n.length;
	return os;
}

template<typename T>
struct SegTree{

	int sz;
	vector<T> t;
	
	T single(ll val){
		return {1, 1, 1, val, val, 1};
	}
	T NEUTRAL = {0,0,0,0,0,0}; //ALSO HAS TO CHANGE
	T merge(T a, T b){
		if (a.length==0) return b;
		if (b.length==0) return a;
		dbg(a);dbg(b);
		T res;
		res.total = a.total+b.total;
		res.suf = b.suf;
		res.pref = a.pref;
		res.start = a.start, res.last = b.last;
		res.length = a.length+b.length;
		if(a.last<=b.start){
			if (b.suf == b.length) res.suf = b.suf + a.suf;
			if (a.pref == a.length) res.pref = b.pref + a.pref;
			res.total += a.suf*b.pref;
		}
		dbg(res);
		return res;
	}
	
	void init(int n){
		sz = 1;
		while(sz<n) sz*=2;
		t.resize(sz*2);
	}
	void build(vector<int> &vec, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        if (l < (int)vec.size())
	            t[x] = single(vec[l]);
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
	void upd(int i, ll v, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        t[x] = single(v);
	        return;
	    }
	    int mid = (l + r) / 2;
	    if (i < mid)
	        upd(i, v, 2 * x + 1, l, mid);
	    else
	        upd(i, v, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void upd(int i, ll v)
	{
	    upd(i, v, 0, 0, sz);
	}
	T query(int l, int r, int x, int lx, int rx)
	{
	    if (lx >= r || rx <= l)
	        return NEUTRAL;
	    if (lx >= l && rx <= r)
	        return t[x];
	    int mid = (lx + rx) / 2;
	    T a = query(l, r, 2 * x + 1, lx, mid);
	    T b = query(l, r, 2 * x + 2, mid, rx);
	    dbg(lx,mid, rx, a);
	    dbg(b);
	    return merge(a, b);
	}
	T query(int l, int r)
	{
	    return query(l, r, 0, 0, sz);
	}
};



void solve()
{
	int n, q;
	cin >> n >> q;
	vi a(n);
	F0R(i, n) cin >> a[i];
	SegTree<node> st;
	st.init(n);
	st.build(a);
	while(q--){
		int t, x, y;
		cin >> t >> x >> y;
		x--;
		if (t==1) st.upd(x, y);
		else{
			cout << st.query(x, y).total<<"\n";
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