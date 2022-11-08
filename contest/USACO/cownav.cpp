// Problem: Problem 3. Cow Navigation
// Contest: USACO - USACO 2017 January Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=695
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
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
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
    size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}


char grid[21][21];
int dp[400][4][400][4];
int shortPath[20][20][4];
int n;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
//0: down, 1:right, 2: up, 3: left

int conv(int x, int y){
	return x*n+y;
}
pii conv(int v){
	return make_pair(v/n, v%n);
}
bool good(int x, int y){
	return x>=0&&x<n&&y>=0&&y<n;
}

void solve()
{
	cin >> n;
	int stx = n-1, sty = 0, enx = 0, eny = n-1;
	F0R(i, n)F0R(j, n)cin >> grid[i][j];
	F0R(i, n)F0R(j, n)F0R(k, 4){
		int dist[n][n][4];
		queue<pair<int,ar<int,3>>> q;
		F0R(x, n)F0R(y, n)F0R(d, 4) dist[x][y][d] =INF;
		dist[i][j][k] = 0;
		q.push({0, {i, j, k}});
		while(sz(q)){
			auto [x, y, dr] = q.front().se;
			int d = q.front().fi;
			q.pop();
			if (dist[x][y][(dr+1)%4]>d+1) dist[x][y][(dr+1)%4] = d+1, q.push({d+1, {x, y, (dr+1)%4}});
			if (dist[x][y][(dr+3)%4]>d+1) dist[x][y][(dr+3)%4] = d+1, q.push({d+1, {x, y, (dr+3)%4}});
			int nx = x + dx[dr], ny = y + dy[dr];
			int NX = x, NY = y;
			if (good(nx, ny)&&grid[nx][ny]=='E') NX = nx, NY = ny;
			if (dist[NX][NY][dr]>d+1) dist[NX][NY][dr]= d+1, q.push({d+1, {NX,NY,dr}});
		}
		shortPath[i][j][k] = *min_element(dist[enx][eny], dist[enx][eny]+4);
	}
	F0R(i, 400)F0R(j, 4)F0R(k, 400)F0R(l, 4) dp[i][j][k][l] = INF;
	dp[conv(stx,sty)][2][conv(stx, sty)][1] = 0;
	queue<ar<int,4>> q;
	q.push({conv(stx, sty), 2, conv(stx, sty), 1});
	int ans = INF;
	while(sz(q)){
		auto [v1, dr1, v2, dr2] = q.front();
		q.pop();
		auto [x1, y1] = conv(v1);
		auto [x2, y2] = conv(v2);
		int d = dp[v1][dr1][v2][dr2];
		dbg(x1,y1, x2,y2, dr1, dr2, d);
		if (x1==enx&&y1==eny){
			ckmin(ans, d+shortPath[x2][y2][dr2]);
			continue;
		}else if (x2==enx&&y2==eny){
			ckmin(ans, d+shortPath[x1][y1][dr1]);
			continue;
		}
		//rotate
		//left
		if (dp[v1][(dr1+1)%4][v2][(dr2+1)%4]>d+1){
			dp[v1][(dr1+1)%4][v2][(dr2+1)%4] = d+1;
			q.push({v1, (dr1+1)%4, v2, (dr2+1)%4});
		}
		//right
		if (dp[v1][(dr1+3)%4][v2][(dr2+3)%4]>d+1){
			dp[v1][(dr1+3)%4][v2][(dr2+3)%4] = d+1;
			q.push({v1, (dr1+3)%4, v2, (dr2+3)%4});
		}
		
		//Forward
		int nx1 = x1+dx[dr1], ny1 = y1+dy[dr1];
		int nx2 = x2 + dx[dr2], ny2 = y2+dy[dr2];
		int NX1 = x1, NY1 = y1, NX2= x2, NY2= y2;
		if (good(nx1, ny1)&&grid[nx1][ny1]=='E'){
			NX1 = nx1, NY1 = ny1;
		}
		if (good(nx2, ny2)&&grid[nx2][ny2]=='E'){
			NX2 = nx2, NY2 = ny2;
		}
		if (dp[conv(NX1, NY1)][dr1][conv(NX2, NY2)][dr2]>d+1){
			dp[conv(NX1, NY1)][dr1][conv(NX2, NY2)][dr2] = d +1;
			q.push({conv(NX1, NY1), dr1, conv(NX2, NY2), dr2});
		}
	}
	cout << ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    #ifndef LOCAL
    	setIO("cownav");
    #endif
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}