// Problem: Mountain Time
// Contest: CS Academy
// URL: https://csacademy.com/contest/archive/task/mountain-time
// Memory Limit: 512 MB
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
const int MAXN = 1001;
const int N = MAXN*MAXN;
int grid[MAXN][MAXN], ans[MAXN][MAXN],n,m;
vpi h[N];
list<pi> notSet[N];
namespace DSU{
	int p[N], mx[N];
	
	void init(){
		iota(p, p+N, 0);
	}
	int get(int x){return (x==p[x]?x:p[x]=get(p[x]));}
	void unite(int x, int y, int h){
		x = get(x), y = get(y);
		if (x==y) return;
	
		if (mx[x]==mx[y]){
			notSet[x].splice(notSet[x].begin(), notSet[y]);
			p[y] = x;
			return;
		}
		if (mx[x]>mx[y]){
			swap(x,y);
		}
		p[x] = y;
		for (auto [i,j]: notSet[x]){
			ans[i][j] = grid[i][j] - h;
			dbg(x, i,j, grid[i][j], h);
		}
		notSet[x].clear();
		
	}
};
using namespace DSU;

int to_int(int x, int y){
	return x*m+y;
}

int dx[] = {0,0,-1,1}, dy[] = {-1,1,0,0};


void solve()
{
	cin >> n >> m;
	for (int i=0;i<n;++i) for (int j=0;j<m;++j){
		cin >> grid[i][j];
		h[grid[i][j]].pb({i,j});
		mx[to_int(i,j)] = grid[i][j];
		notSet[to_int(i,j)].pb({i,j});
	}
	init();
	for (int i=N-1;i>=0;i--){
		for (auto [x, y]:h[i]){
			for (int j=0;j<4;++j){
				int nx = x+dx[j], ny = y +dy[j];
				if (nx<0||nx>=n||ny<0||ny>=m) continue;
			
				if (grid[x][y]<=grid[nx][ny]){
					dbg(x, y, nx, ny, i);
					unite(to_int(x,y), to_int(nx, ny), i);
				}
			}
		}
	}
	for (int i=0;i<n;++i) for (int j=0;j<m;++j){
		int c = get(to_int(i,j));
		for (auto [x,y]:notSet[c]){
			ans[x][y] = grid[x][y];
			dbg(x,y);
		}
		notSet[c].clear();
	}
	for (int i=0;i<n;++i) {
		for (int j=0;j<m;++j){
			cout << ans[i][j]<< " ";
		}
		cout << "\n";
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