// Problem: N. Teleport
// Contest: Codeforces - Teamscode Summer 2021
// URL: https://codeforces.com/gym/103241/problem/N
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

char grid[1000][1000];
bool hasT[1000][1000];
pii dest[1000][1000];
int dist[1000][1000];
int n, m, k;

bool good(int x, int y){
	return x>=0&&x<n&&y>=0&&y<m;
}

void solve()
{
	cin >> n >> m>>k;
	F0R(i,n)F0R(j,m)cin >> grid[i][j];
	
	F0R(i, k){
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		x1--,y1--,x2--,y2--;
		hasT[x1][y1] = 1;
		dest[x1][y1] = {x2,y2};
	}
	F0R(i, n) F0R(j, m) dist[i][j] = INF;
	dist[0][0] = 0;
	queue<pair<int,pii>> q;
	q.push({0, {0,0}});
	while(sz(q)){
		auto [x, y] = q.front().se;
		int d = q.front().fi;
		q.pop();
		if (d>dist[x][y]) continue;
		if (hasT[x][y]){
			auto [nx,ny] = dest[x][y];
			if (dist[nx][ny]>d) q.push({d, {nx,ny}}),dist[nx][ny] = d;
		}else{
			F0R(j, 4){
				int nx = x + dx[j], ny = y+ dy[j];
				if (good(nx,ny)&&grid[nx][ny]!='#'&&dist[nx][ny]>d+1){
					q.push({d+1, {nx,ny}});
					dist[nx][ny] = d+1;
				}
			}
		}
	}
	cout << dist[n-1][m-1];
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