// Problem: Problem 3. Fenced In
// Contest: USACO - USACO 2016 February Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=623
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


// From the USACO tutorial lol
const int sz = 4004002;
namespace DSU{
	   int par[sz], size[sz];
	   void init(){ for(int i=0; i<sz; i++) par[i]=i, size[i]=1; }
	   int get(int v){//finds the representative of a union
			  return(v==par[v] ? v : par[v]=get(par[v]));
	   }
	   void unite(int a, int b){
			  a=get(a); b=get(b);
			  if (size[a] < size[b]) swap(a, b);
			  par[b]=a; size[a]+=size[b];
	   }
}
using namespace DSU;

struct edge{
	   int w, u, v;
	   bool operator<(const edge & other) const{ return w<other.w; } // sort by ascending weights
};

edge edges[(int)1e7];
int p[sz], s[sz], a[2003], b[2003];
int A, B, n, m;
ll res = 0;
int ptr=0;
int cnt =0;



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef LOCAL
    	setIO("fencedin");
    #endif
    cin >> A >> B>>n >> m;
	init();
	for (int i=1;i<=n;++i) cin >> a[i];
	a[n+1] = A;
	for (int j=1;j<=m;++j) cin >> b[j];
	b[m+1] = B;
	sort(a, a+n+2); sort(b, b+m+2);
	for (int i=1;i<=n+1;++i){
		for (int j=1;j<=m+1;++j){
			if (j<=m) edges[cnt++] = {a[i]-a[i-1] , ptr, ptr+1};
			if (i<=n) edges[cnt++] = {b[j]-b[j-1], ptr, ptr+m+1};
			ptr++;
		}
	}
	sort(edges, edges+cnt);
	for (int i=0;i<cnt;++i){
		edge e= edges[i];
		if (get(e.u)!=get(e.v)){
			unite(e.u,e.v);
			res += e.w;
		}
	}
	cout << res;
}