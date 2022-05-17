// Problem: K - 遺産相続
// Contest: AtCoder - JOI春合宿2015 オンラインジャッジ
// URL: https://atcoder.jp/contests/joisc2015/tasks/joisc2015_k
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
const int N = 1000;

struct DSU{
	int p[N], sz[N];
	void init(){
		fill(sz, sz+N, 1);
		iota(p, p+N, 0);
		
	}
	int get(int x){
		dbg(x, p[x]);
		return (x==p[x]? x:p[x] = get(p[x]));
	}
	bool same(int x, int y){return get(x)==get(y);}
	void unite(int x,int y){
		x = get(x), y= get(y);
		if (x!=y){
			if (sz[x]<sz[y]) swap(x,y);
			p[y] = x;
			sz[x] += sz[y];
		}
	}
}child[10000];

struct Edge{
	int u,v, c, idx;
	bool operator>(const Edge& other) const{
		return c>other.c;
	}
};

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<Edge> edges(m);
	for (int i=0;i<m;++i){
		cin >> edges[i].u >> edges[i].v >> edges[i].c;
		edges[i].u--, edges[i].v--;
		edges[i].idx = i;
	}
	for (int i=0;i<k;++i) child[i].init();
	sort(all(edges), greater<Edge>());
	vi ans(m);
	for (int i=0;i<m;++i){
		Edge e = edges[i];
	
		int l = 0, r = k-1, res = -1;
		while(l<=r){
			int mid = l + (r-l)/2;
			if (!child[mid].same(e.u, e.v)){
				res = mid, r = mid-1;
			}else l = mid+1;
		}
		if (res!=-1) child[res].unite(e.u,e.v);
		ans[e.idx] = (res==-1? 0:res+1);
	}
	for (int x:ans) cout << x << "\n";
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