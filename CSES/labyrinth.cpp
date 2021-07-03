#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vii = vector<vector<int>>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;
using vll = vector<ll>;

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
char maze[1000][1000];
bool vis[1000][1000];
int p[1000][1000]; int dx[] = {0,0,-1,1}, dy[] = {-1,1,0,0}, n,m ;

void bfs(int x, int y){
	queue<pair<int,int>> q;
	q.push({x,y});
	p[x][y] = 0;
	vis[x][y] = 1;
	while(!q.empty()){
		int x1 =q.front().first, y1 = q.front().second;
		dbg(x1,y1);
		q.pop();
		for (int i=0;i<4;i++){
			int tx = x1+dx[i], ty = y1 + dy[i];
			if (tx>=0&&ty>=0&&tx<n&&ty<m&&maze[tx][ty] != '#'){
				if (!vis[tx][ty]){
					vis[tx][ty] = 1;
					p[tx][ty] = i+1;
					q.push({tx, ty});
				}
			}
		}
	}
}

void solve()
{
	memset(p, -1, sizeof(p));
	cin >> n >> m;
	int xa, ya, xb, yb;
	for (int i=0;i<n;i++){
		string s;
		cin >> s;
		for (int j=0;j<m;j++){
			maze[i][j] = s[j];
			if (s[j]=='A') xa = i, ya = j;
			if (s[j] == 'B') xb = i, yb = j;
		}
	}
	bfs(xa, ya);
	if (!vis[xb][yb]) cout << "NO\n";
	else{
		string ans ="";
		while(p[xb][yb]!=0){
			if (p[xb][yb] == 1){
				ans += 'L';
				yb++;
			}
			if (p[xb][yb] == 2){
				ans += 'R';
				yb--;
			}
			if (p[xb][yb] == 3){
				ans += 'U';
				xb++;
			}
			if (p[xb][yb] == 4){
				ans += 'D';
				xb--;
			}
		}
		reverse(all(ans));
		cout << "YES\n";
		cout << (int)ans.length()<<"\n";
		cout << ans << "\n";
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int testcase=1;
    //cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}