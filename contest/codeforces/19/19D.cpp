// Problem: D. Points
// Contest: Codeforces - Codeforces Beta Round #19
// URL: https://codeforces.com/contest/19/problem/D
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
		return {val};
	}
	T NEUTRAL = {0}; //ALSO HAS TO CHANGE
	T merge(T a, T b){
		return (a>b ? a:b);
	}
	
	void init(int n){
		sz = 1;
		while(sz<n) sz*=2;
		t.resize(sz*2);
	}
	void upd(int i, int v, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        t[x] = v;
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
	int query(int X, int Y, int x, int lx, int rx)
	{
		if (rx<=X||t[x]<=Y) return -1;
	    if (rx-lx==1){
	    	return lx;
	    }
	    int mid = (lx+rx)>>1;
    	int p = query(X, Y, 2*x+1, lx, mid);
    	if (p==-1)p = query(X, Y, 2*x+2, mid, rx);
    	return p;
	}
	int query(int x, int y)
	{
	    return query(x, y, 0, 0, sz);
	}
};

char s[20];
set<int> cache[200010<<1];


void solve()
{
	int n;
	scanf("%d", &n);
	vi c;
	vector<ar<int,3>> q(n);
	for (int i=0;i<n;++i){
		int x, y;
		scanf("%s %d%d", s, &x, &y);
		int t = s[0]-'a';
		if (t==5) t = 2;
		else if (t>5) t = 1;
		q[i] = {t,x,y};
		c.pb(x);
	}
	sort(all(c)), c.resize(unique(all(c))-c.begin());
	int cnt = sz(c);
	SegTree<int> st;
	st.init(cnt);
	for (int i=0;i<n;++i){
		auto &[t,x,y] = q[i];
		x = lb(all(c),x)-c.begin();
		if (t==0){
			cache[x].insert(y);
			st.upd(x, *--cache[x].end());
		}else if (t==1){
			cache[x].erase(y);
			if (cache[x].empty()) st.upd(x, 0);
			else st.upd(x, *--cache[x].end());
		}else{
			int p = st.query(x+1, y);
			if (p!=-1){
				int ans = *cache[p].lb(y+1);
				cout << c[p]<< " "<< ans << "\n";
			}
			else cout << -1 << "\n";
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