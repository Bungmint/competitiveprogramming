// Problem: E. Little Elephant and Inversions
// Contest: Codeforces - Codeforces Round #136 (Div. 1)
// URL: https://codeforces.com/contest/220/problem/E
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
	
	T single(int val){
		return val;
	}
	T NEUTRAL = 0; //ALSO HAS TO CHANGE
	T merge(T a, T b){
		return a+b;
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
	void upd(int i, int v, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        t[x] += v;
	        return;
	    }
	    int mid = (l + r) / 2;
	    if (i < mid)
	        upd(i, v, 2 * x + 1, l, mid);
	    else
	        upd(i, v, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void upd(int i, int v)
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
	int n;ll k;
	scanf("%d%lld",&n,&k);
	vi order, a(n);
	for (int i=0;i<n;++i){
		scanf("%d", &a[i]);
		order.pb(a[i]);
	}
	sort(all(order)), order.resize(unique(all(order))-order.begin());
	for (int i=0;i<n;++i) a[i] = lb(all(order), a[i])-order.begin();
	SegTree<int> L, R;
	vl pref(n);
	L.init(n),R.init(n);
	for (int i=n-1;i>=0;--i){
		R.upd(a[i], 1);
		int x = R.query(0, a[i]);
		pref[i] = (i<n-1? pref[i+1]+ x:x);
	}
	ll res = 0, sum = 0;
	int l =-1;
	dbg(a, pref);
	dbg(R.query(0,2));
	for (int r=0;r<n;++r){
		sum += pref[r];
		if (r) {
			sum -= pref[r-1] + L.query(a[r-1]+1, n);
			R.upd(a[r-1], -1);
		}
		
		
		while(l+1<r&&sum<=k){
			int x = L.query(a[l+1]+1, n), y = R.query(0, a[l+1]);
			sum += x+y;
			dbg(r, x, y, l, sum);
			L.upd(a[l+1],1);
			l++;
			if (sum>k||l>=r){
				l--;
				L.upd(a[l+1],-1);
				sum -= x+y;
				break;
			}
		}
		dbg(l,r,sum);
		if (sum<=k&&l<r)res += l+1;
	}
	cout << res << endl;
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