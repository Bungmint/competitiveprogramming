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

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<string> grid(n);
	vector<vi> cost1(n, vi(m,INF)), cost2(n, vi(m,INF));
	for (int i=0;i<n;++i){
		cin >> grid[i];
	}
	int stX, stY, enX, enY;
	for (int i=0;i<n;++i) for (int j=0;j<m;++j){
		if (grid[i][j]=='C'){
			stX = i, stY = j;
			grid[i][j] = '.';
		}else if (grid[i][j]=='D'){
			enX = i, enY = j;
			grid[i][j] = '.';
		}
	}
	deque<pair<int,pi>> q;
	cost1[stX][stY] = 0;
	q.pb({0, {stX, stY}});
	while(!q.empty()){
		int d = q.front().fi;
		auto [x,y] = q.front().se;
		dbg(x,y);
		q.pop_front();
		//Gravity
		if (d&1){
			while(x>0&&grid[x-1][y]=='.'){
				cost2[x-1][y] = cost2[x][y];
				x--;
			}
			if (x==0) continue;
			if (y+1<m&&cost2[x][y+1]>cost2[x][y]&&grid[x][y+1]=='.'){
				cost2[x][y+1] = cost2[x][y];
				q.push_front({d, {x,y+1}});
			}
			if (y-1>=0&&cost2[x][y-1]>cost2[x][y]&&grid[x][y-1]=='.'){
				cost2[x][y-1] = cost2[x][y];
				q.push_front({d, {x,y-1}});
			}
			int x1 = x;
			while(x1<n-1&&grid[x1+1][y]=='.'){
				x1++;
			}
			
			for (int i=x+1;i<x1;++i){
				cost1[i][y] = min(cost1[i][y], d+1);
			}
			if (x1==n-1){
				cost1[n-1][y] = min(cost1[n-1][y], d+1);
				continue;
			}
			if (cost1[x1][y]>d+1){
				cost1[x1][y] =d+1;
				q.pb({cost1[x1][y], {x1,y}});
			}
		}else{
			if (x==5&&y==3) dbg(d);
			while(x<n-1&&grid[x+1][y]=='.'){
				cost1[x+1][y] = cost1[x][y];
				x++;
		
			}
			
			if (x==n-1) continue;
			if (y+1<m&&cost1[x][y+1]>cost1[x][y]&&grid[x][y+1]=='.'){
				cost1[x][y+1] = cost1[x][y];
				q.push_front({d, {x,y+1}});
			}
			if (y-1>=0&&cost1[x][y-1]>cost1[x][y]&&grid[x][y-1]=='.'){
				cost1[x][y-1] = cost1[x][y];
				q.push_front({d, {x,y-1}});
			}
			int x1 = x;
			while(x1>0&&grid[x1-1][y]=='.'){
				x1--;
			}
			for (int i=x1+1;i<x;++i){
				cost2[i][y] = min(cost2[i][y], d+1);
			}
			if (x1==0){
				cost2[0][y] = min(cost2[0][y], d+1);
				continue;
			}
			if (cost2[x1][y]>d+1){
				cost2[x1][y] =d+1;
				q.pb({cost2[x1][y], {x1,y}});
			}
		}
	
	}
	cout <<(cost1[enX][enY] == INF&&cost2[enX][enY]==INF ? -1 : min(cost1[enX][enY], cost2[enX][enY]))<<endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    setIO("gravity");
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}