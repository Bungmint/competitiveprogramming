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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353
int grid[500][500], dx[] = {0,0,-1,1}, dy[] = {-1,1,0,0},m,n;
bool vis[500][500];

void setIO(string s){
	freopen((s+".in").c_str(), "r", stdin);
	freopen((s+".out").c_str(), "w", stdout);
}

void dfs(int x, int y, int d){
	if (vis[x][y]) return;
	dbg(x, y, d);
	vis[x][y] = 1;
	for (int i=0;i<4;++i){
		int nx = x + dx[i], ny = y + dy[i];
		if (nx<0||nx>=m||ny<0||ny>=n){
			continue;
		}
		if (abs(grid[x][y]-grid[nx][ny])<=d){
			dfs(nx, ny, d);
		}
	}
}

void solve()
{
	cin >> m >> n;
	for (int i=0;i<m;++i){
		for (int j=0;j<n;++j){
			cin >> grid[i][j];
		}
	}
	vpi wp;
	for (int i=0;i<m;++i){
		for (int j=0;j<n;++j){
			int t;
			cin >> t;
			if (t) wp.pb({i,j});
		}
	}
	if (sz(wp)==0){
		cout << 0 << "\n";
		return;
	}
	int x = wp[0].fi, y = wp[0].se;
	int l=0, r = 1e9, ans = -1;
	while(l<=r){
		int d = l + (r-l)/2;
		memset(vis, 0, sizeof(vis));
		dfs(x, y, d);
		bool ok = 1;
		for (int i=0;i<sz(wp);++i){
			ok &= vis[wp[i].fi][wp[i].se];
		}
		if (ok){
			ans = d;
			r = d-1;
		}else l = d+1;
	}
	cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    setIO("ccski");
    solve();
}