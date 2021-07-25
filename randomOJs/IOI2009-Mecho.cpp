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
int n, s;
int dx[] = {0,0,-1, 1}, dy[] = {-1, 1, 0,0};
char grid[801][801];
bool vis[801][801];

bool good(int x, int y){
	return (x>=0&&x<n&&y>=0&&y<n);
}


void solve()
{
	cin >> n >> s;
	for (int i=0;i<n;++i) for (int j=0;j<n;++j)cin >> grid[i][j];
	vector<vi> distFromHives(n, vi(n, INF));
	queue<pi> q;
	int mX, mY, homeX, homeY;
	for (int i=0;i<n;++i) for (int j=0;j<n;++j){
		if (grid[i][j]=='M'){
			mX = i, mY = j;
		}else if (grid[i][j]=='D'){
			homeX = i, homeY = j;
		}else if (grid[i][j] == 'H'){
			q.push({i,j});
			distFromHives[i][j] = 0;
		}
	}
	while(sz(q)){
		auto [x,y] = q.front();
		q.pop();
		for (int i=0;i<4;++i){
			int nX = x + dx[i], nY = y + dy[i];
			if (good(nX, nY)&&grid[nX][nY]!='D'&&grid[nX][nY]!='T'&&distFromHives[nX][nY]>distFromHives[x][y]+1){
				distFromHives[nX][nY] = distFromHives[x][y] + 1;
				q.push({nX, nY});
			}
		}
	}
	dbg(distFromHives);
	int l = 0, r = distFromHives[mX][mY]-1, ans = -1;
	while(l<=r){
		int start = l + (r-l)/2, t = start;
		queue<pi> nxt;
		queue<pair<int,pi>> cur;
		memset(vis, 0, sizeof(vis));
		vis[mX][mY] = 1;
		cur.push({0,{mX, mY}});
		while(sz(cur)){
			while(sz(cur)){
				int d = cur.front().fi;
				auto [x,y] = cur.front().se;
				cur.pop();
				if (d==s){
					if (distFromHives[x][y]>t+1)nxt.push({x,y});
					continue;
				}
				for (int i=0;i<4;++i){
					int nX = x + dx[i], nY = y + dy[i];
					if (good(nX, nY)&&!vis[nX][nY]&&grid[nX][nY]!='T'&&distFromHives[nX][nY]>t){
						vis[nX][nY] = 1;
						cur.push({d+1,{nX, nY}});
					}
				}
			}
			while(sz(nxt)) cur.push({0, nxt.front()}), nxt.pop();
			t++;
		}
		
		if (vis[homeX][homeY]) ans = start, l = start+1;
		else r = start-1;
	}
	
	cout << ans << endl;
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