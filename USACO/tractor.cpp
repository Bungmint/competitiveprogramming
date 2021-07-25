// Problem: Problem 2. Tractor
// Contest: USACO - USACO 2013 February Contest, Silver
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=245
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

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
const int N =500*500+500;

namespace DSU{
	int sz[N], p[N];
	int cnt = 1; 
	void init(){
		fill(sz, sz+N,1);
		iota(p, p+N, 0);
		cnt =1;
	}
	int get(int x){return (x==p[x]? x:p[x] = get(p[x]));}
	void unite(int x, int y){
		x = get(x), y = get(y);
	
		if (x!=y){
			if (sz[x]<sz[y]) swap(x,y);
			sz[x]+=sz[y];
			p[y] = x;
			cnt =max(cnt, sz[x]);
		}
	}
}
using namespace DSU;

int dx[] = {0,0,-1, 1}, dy[] = {-1, 1, 0, 0};

void solve()
{
	int n;
	cin >> n;
	vector<vi> grid(n, vi(n));
	for (int i=0;i<n;++i) for (int j=0;j<n;++j){
		cin >> grid[i][j];
	}
	int l = 0;
	int r = 1e6+100;
	int ans = -1;
	while(l<=r){
		int m = l + (r-l)/2;
		init();
		for (int i=0;i<n;++i) for (int j=0;j<n;++j){
			int c = i*n + j;
			for (int k=0;k<4;++k){
				int nX = dx[k] + i, nY = dy[k] + j;
				if (nX<0||nX>=n||nY<0||nY>=n){
					continue;
				}
				if (abs(grid[nX][nY]-grid[i][j])<=m) unite(i*n+j, nX*n+nY);
			}
		}
		dbg(m, cnt);
		if (cnt>=(n*n+1)/2){
			r = m-1;
			ans = m;
		}else l = m+1;
	}
	cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef LOCAL
    	setIO("tractor");
    #endif
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}