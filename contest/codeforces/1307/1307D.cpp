// Problem: D. Cow and Fields
// Contest: Codeforces - Codeforces Round #621 (Div. 1 + Div. 2)
// URL: https://codeforces.com/problemset/problem/1307/D
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

void bfs(int source, vector<vi> &g, vi &dist){
	fill(all(dist), INF);
	dist[source] = 0;
	queue<int> q;
	q.push(source);
	while(sz(q)){
		int v = q.front();
		q.pop();
		for (int e:g[v]){
			if (dist[e]>dist[v]+1){
				dist[e] = dist[v]+1;
				q.push(e);
			}
		}
	}
}

template<typename T>
struct BIT{
	T n;
	vector<T> bit;
	BIT(int x){n=x;bit.resize(x+1);}
	void init(){bit.assign(n+1, INF);}
	void upd(int i, T v){
		for (;i<=n;i+=i&-i) ckmin(bit[i],v);	
	}
	T query(int i){
		T res = INF;
		for (;i>0;i-=i&-i) ckmin(res, bit[i]);
		return res;
	}
};

const int MX = 2e5+1;


void solve()
{
	int n,m,k;
	cin >> n >> m >>k;
	vector<vi> g(n+1);
	vi fromBessie(n+1), fromHome(n+1);
	vi a(k);
	for (int i=0;i<k;++i) cin >> a[i];
	for (int i=0;i<m;++i){
		int u,v;
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	bfs(1, g, fromBessie), bfs(n, g, fromHome);
	int res = fromBessie[n];
	int mx = 0, l = 0, r = res;
	while(l<=r){
		int mid = l + (r-l)/2;
		BIT<int> bit(MX);
		bit.init();
		bool ok = 0;
		for (int i=0;i<k;++i){
			int x = bit.query(fromBessie[a[i]]);
			ok |= (x<=fromHome[a[i]]);
			bit.upd(max(1, mid-fromHome[a[i]]-1), mid-fromBessie[a[i]]-1);
		}
		if (ok) mx = mid, l = mid+1;
		else r = mid-1;
	}
	
	
	cout << min(mx, res)<<endl;
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