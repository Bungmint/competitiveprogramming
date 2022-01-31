// Problem: D. Misha and Permutations Summation
// Contest: Codeforces - Codeforces Round #285 (Div. 2)
// URL: https://codeforces.com/contest/501/problem/D
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

struct SegTree{

	int sz;
	struct Node{
		int val;
	};
	vector<Node> t;
	
	
	Node single(int val){
		return {val};
	}
	const Node NEUTRAL = {0}; //ALSO HAS TO CHANGE
	Node merge(Node a, Node b){
		return {a.val+b.val};
	}
	
	void init(int n){
		sz = 1;
		while(sz<n) sz*=2;
		t.assign(sz*2, NEUTRAL);
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
	void upd(int i, int v)
	{
	    upd(i, v, 0, 0, sz);
	}
	Node query(int l, int r, int x, int lx, int rx)
	{
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
	int findKth(int k, int x, int lx, int rx){
		if (rx-lx==1){
			return lx;
		}
		int mid = (lx+rx)>>1;
		int v = mid-lx- t[2*x+1].val;
		if (k<v){
			return findKth(k, 2*x+1, lx ,mid);
		}
		return findKth(k-v, 2*x+2, mid, rx);
	}
	int findKth(int k){
		return findKth(k, 0, 0, sz);
	}
};

void solve()
{
	int n;
	cin >> n;
	vi a(n), b(n);
	vi factorial(n);
	for (int &e:a) cin >> e;
	for (int&e:b) cin >> e;
	SegTree st;
	st.init(n);
	for (int i=0;i<n;++i){
		int k = st.query(0, a[i]).val;
		factorial[i] += a[i]-k;
		st.upd(a[i], 1);
	}
	st.init(n);
	for (int i=0;i<n;++i){
		int k = st.query(0, b[i]).val;
		factorial[i] += b[i]-k;
		st.upd(b[i], 1);
	}
	dbg(factorial);
	for (int i=n-1;i>=0;i--){
		if (factorial[i]>n-1-i){
			if(i) factorial[i-1]++;
			factorial[i]-= (n-i);
		}
	}
	st.init(n);
	for (int i=0;i<n;++i){
		int x = st.findKth(factorial[i]);
		cout << x << " ";
		st.upd(x, 1);
	}
	cout << endl;
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