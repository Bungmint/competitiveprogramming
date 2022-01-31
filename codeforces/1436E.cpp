// Problem: E. Complicated Computations
// Contest: Codeforces - Codeforces Round #678 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1436/E
// Memory Limit: 256 MB
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
	
	T single(ll val){
		return val;
	}
	T NEUTRAL = INF; //ALSO HAS TO CHANGE
	T merge(T a, T b){
		return min(a,b);
	}
	
	void init(int n){
		sz = 1;
		while(sz<n) sz*=2;
		t.assign(sz*2, -1);
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
	    return merge(a, b);
	}
	T query(int l, int r)
	{
	    return query(l, r, 0, 0, sz);
	}
};

template<typename T>
struct SegTreew{

	int sz;
	vector<T> t;
	
	T single(ll val){
		return val;
	}
	T NEUTRAL = 0; //ALSO HAS TO CHANGE
	T merge(T a, T b){
		return max(a,b);
	}
	
	void init(int n){
		sz = 1;
		while(sz<n) sz*=2;
		t.assign(sz*2, INF);
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
	    return merge(a, b);
	}
	T query(int l, int r)
	{
	    return query(l, r, 0, 0, sz);
	}
};

void solve()
{
	int n;
	cin >> n;
	vi a(n);
	SegTree<int> st;
	SegTreew<int> t;
	st.init(n+10);
	vi last(n+1, -1);
	vector<bool> good(n+2);
	F0R(i, n){
		cin >> a[i];
		st.upd(a[i], i);
		int q = st.query(1, a[i]);
		dbg(q);
		if (a[i]==1&&last[a[i]]+1<i) good[a[i]] = 1;
		else if (q>=last[a[i]]+1&&a[i]!=1) good[a[i]] = 1;
		last[a[i]] = i;
	}
	int q = st.query(1, n+2);
	if (q>=0) good[n+1] = 1;
	dbg(good);
	t.init(n+10);
	fill(all(last), n);
	R0F(i, n){
		t.upd(a[i], i);
		int q = t.query(1, a[i]);
		dbg(q,a[i]);
		if (a[i]==1&&last[a[i]]>i+1) good[a[i]] = 1;
		else if (q+1<=last[a[i]]&&a[i]!=1) good[a[i]] = 1;
		last[a[i]] = i;
	}
	dbg(good);
	FOR(i, 1, n+2){
		if (st.query(1, i)!=-1&&st.query(1,i+1)==-1) good[i]=1;
	}
	FOR(i, 1, n+2){
		dbg(t.query(1,i), t.query(1, i+1));
		if (t.query(1, i)!=INF&&t.query(1,i+1)==INF) good[i]=1;
	}
	
	FOR(i, 1, n+2){
		if (!good[i]){cout << i << endl;return;}
	}
	cout << n+2<<endl;
	
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