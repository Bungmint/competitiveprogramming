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

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
#define sz(x) (int)(x).size()

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353
char grid[51][51];
bool vis[51][51];
int dx[] = {0,0,-1,1}, dy[] = {-1, 1, 0,0}, n, m;

inline bool good(int x, int y){
	return (x>=0&&x<n&&y>=0&&y<m);
}

void solve()
{
	memset(vis, 0, sizeof(vis));
    vpi cool, bad;
	cin >> n >> m;
	for (int i=0;i<n;++i){
		string s;
		cin >> s;
		for (int j=0;j<m;++j){
			grid[i][j] = s[j];
			if (s[j]=='G') cool.PB({i,j});
			else if (s[j]=='B') bad.PB({i,j});
		}
	}
	bool ok = 1;
	for (pi p:bad){
	    int i = p.first, j = p.second;
	    for (int k=0;k<4;++k){
			int nextX = i+dx[k], nextY = j + dy[k];
			if (good(nextX, nextY)){
				if (grid[nextX][nextY]=='G'){
					ok = 0;
					break;
				}else if (grid[nextX][nextY]=='.') grid[nextX][nextY] = '#';
			}
		}
	}
	if (!ok){
		cout << "No\n";
		return;
	}
	if (grid[n-1][m-1]!='#'){
		queue<pi> q;
		q.push({n-1, m-1});
		vis[n-1][m-1] = 1;
		while(!q.empty()){
			int x = q.front().first, y = q.front().second;
			q.pop();
			for (int i=0;i<4;++i){
				int nx = x + dx[i], ny = y + dy[i];
				if (good(nx, ny)&&grid[nx][ny] !='#'&&!vis[nx][ny]){
					vis[nx][ny] = 1;
					q.push({nx, ny});
				}
			}
		}
	}
	for (pi p:cool){
		ok &= vis[p.first][p.second];
	}
	for (pi p:bad){
		ok &= !(vis[p.first][p.second]);
	}
	cout << (ok ? "Yes\n":"No\n");
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while(t-->0){
    	solve();
    }
}