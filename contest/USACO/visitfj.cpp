// Problem: Problem 1. Why Did the Cow Cross the Road
// Contest: USACO - USACO 2017 February Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=717
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
int grid[101][101];
int dist[101][101][3];
int dx[] = {0,0,-1, 1}, dy[] = {-1,1,0,0};
int n,t;

bool good(int x, int y){
	return (x>=0&&x<n&&y>=0&&y<n);
}

void solve()
{
	cin >> n>>t;
	for (int i=0;i<n;++i) for (int j=0;j<n;++j) cin >> grid[i][j];
	memset(dist, 0x3f, sizeof(dist));
	dist[0][0][0] = 0;
	pqg<pair<pi,pi>> pq;
	pq.push({{0, 0}, {0,0}});
	while(!pq.empty()){
		auto [d, cnt] = pq.top().fi;
		auto [x,y] = pq.top().se;
		pq.pop();
		if (dist[x][y][cnt]<d) continue;
		for (int i=0;i<4;++i){
			int nX = x+dx[i], nY = y+dy[i];
			if (!good(nX,nY)) continue;
			if ((cnt+1)%3==0){
				if (dist[nX][nY][0]>d+t+grid[nX][nY]){
					dist[nX][nY][0]=d+t+grid[nX][nY];
					pq.push({{dist[nX][nY][0], 0}, {nX,nY}});
				}
			}else{
				if (dist[nX][nY][cnt+1]>d+t){
					dist[nX][nY][cnt+1]=d+t;
					pq.push({{dist[nX][nY][cnt+1], cnt+1}, {nX,nY}});
				}
			}
		}
	}
	int res = INT_MAX;
	for (int i=0;i<3;++i){
		if (res>dist[n-1][n-1][i]){
			res = dist[n-1][n-1][i];
		}
	}
	cout << res << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef LOCAL
    	setIO("visitfj");
    #endif
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}