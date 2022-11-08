// Problem: Knight's Tour
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1689
// Memory Limit: 512 MB
// Time Limit: 1000 ms
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
#define ub upper_bound

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
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

const int N = 64;
int grid[8][8], dx[8] = {2, 2, 1, -1, -2, -2, 1, -1}, dy[8]={1,-1,-2,-2,1, -1, 2, 2};;

pi c(int x){
	return {x/8, x%8};
}
int c(int x, int y){
	return x*8+y;
}
bool valid(int x, int y){
	return x>=0&&y>=0&&x<8&&y<8;
}
int avail(int x,int y, bitset<N> &used){
	assert(valid(x,y));
	int cnt = 0;
	for (int i=0;i<8;++i){
		int nx = x+dx[i], ny = y+dy[i];
		if (valid(nx,ny)&&!used[c(nx,ny)])cnt++;
	}
	return cnt;
}
bool rec(int x, int y, bitset<N> &used){
	int k = used.count();
	if (k==64){
		return 1;
	}
	int mi = INF;
	for (int i=0;i<8;++i){
		int nx = x+dx[i], ny = y+dy[i];
		if (valid(nx,ny)&&!used[c(nx,ny)]&&mi>avail(nx,ny,used)){
			mi = avail(nx,ny,used);
		}
	}
	if (mi==INF)return 0;
	for (int i=0;i<8;++i){
		int nx = x+dx[i], ny = y+dy[i];
		if (valid(nx,ny)&&!used[c(nx,ny)]&&mi==avail(nx, ny, used)){
			used[c(nx,ny)] = 1;
			grid[nx][ny] = k+1;
			if (rec(nx, ny, used)) return 1;
			used[c(nx,ny)] = 0;
		}
	}
	return 0;
}

void solve()
{
	int x,y;
	cin >> x >> y;
	swap(x,y);
	x--;y--;
	bitset<N> empty;
	empty[c(x,y)]= 1;
	grid[x][y] = 1;
	rec(x,y, empty);
	for (int i=0;i<8;++i){
		for (int j=0;j<8;++j){
			cout << grid[i][j]<<" ";
		}
		cout << endl;
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