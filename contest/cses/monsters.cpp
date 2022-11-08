#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;

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
const int N = 1001;
char maze[N][N];
int n, m, dx[] = {0,0,-1,1}, dy[] = {-1,1,0,0};
int dist[N][N], p[N][N];
bool is_me[N][N];

inline bool ok(int x, int y){
	return (x>=0&&x<n&&y>=0&&y<m&&maze[x][y]!='#');
}


void solve()
{
	cin >> n >> m;
	for (int i=0;i<N;i++) for (int j=0;j<N;j++) dist[i][j]=INF;
	int mx = 0, my = 0;
	queue<pair<bool, pi>> q;
	for (int i=0;i<n;i++){
		string s;
		cin >> s;
		for (int j=0;j<m;j++){
			maze[i][j] = s[j];
			if (s[j]=='A'){
				mx = i, my = j;
			}
			if (s[j]=='M')q.push({false, {i, j}}), dist[i][j] = 0;
		}
	}
	q.push({true, {mx,my}});
	dist[mx][my] = 0;
	is_me[mx][my] = true;
	while(!q.empty()){
		int x = q.front().second.first, y = q.front().second.second;
		bool me = q.front().first;
		q.pop();
		for (int i=0;i<4;i++){
			int nx = x+dx[i], ny = y +dy[i];
			if (ok(nx, ny)&&dist[nx][ny]>dist[x][y]+1){
				dist[nx][ny] = dist[x][y] + 1;
				is_me[nx][ny] = me;
				p[nx][ny] = i;
				q.push({me, {nx, ny}});
			}
		}
	}
	for (int i=0;i<n;i++) for (int j=0;j<m;j++){
		if (ok(i,j)&&dist[i][j]!=INF&&is_me[i][j]&&((i==0||j==0)||(i==n-1||j==m-1))){
			string ans;
			while(dist[i][j]){
				if (p[i][j]==0){
					ans.PB('L');
					j++;
				}else if (p[i][j]==1){
					ans.PB('R');
					j--;
				}else if (p[i][j]==2){
					ans.PB('U');
					i++;
				}else{
					ans.PB('D');
					i--;
				}
			}
			reverse(all(ans));
			cout << "YES\n";
			cout << (int)ans.length()<<"\n";
			cout << ans << "\n";
			return;
		}
	}
	cout << "NO\n";
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