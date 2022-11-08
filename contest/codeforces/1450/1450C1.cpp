// Problem: C1. Errich-Tac-Toe (Easy Version)
// Contest: Codeforces - Codeforces Global Round 12
// URL: https://codeforces.com/problemset/problem/1450/C1
// Memory Limit: 256 MB
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
int n;
pair<pi,pi> t[6] = {{{1,0}, {2,0}}, {{-1,0}, {1,0}},{{-2,0}, {-1,0}},{{0,1}, {0,2}},{{0,-1}, {0,1}},{{0,-2}, {0,-1}}};
pi nei[8] = {{1,0}, {2,0}, {-1,0}, {-2,0}, {0,1}, {0,2}, {0,-1},{0,-2}};
inline bool good(pi p){
	return p.fi>=0&&p.fi<n&&p.se>=0&&p.se<n;
}
bool good(pi p, pi q, pi r, vector<string> &grid){
	bool res = good(p)&&good(q)&&good(r);
	if (!res) return res;
	return grid[p.fi][p.se]==grid[q.fi][q.se]&&grid[q.fi][q.se]==grid[r.fi][r.se]&&grid[p.fi][p.se]=='X';
}

void solve()
{
	cin >> n;
	vector<string> grid(n);
	int cnt[3]={0,0,0}, counter=0;
	for (int i=0;i<n;++i) cin >> grid[i];
	
	for (int i=0;i<n;++i){
		for (int j=0;j<n;++j){
			if (grid[i][j]=='X'){
				counter++;
				cnt[(i+j)%3]++;
			}
		}
	}
	int ch = 0;
	for (int i=0;i<3;++i){
		if (cnt[i]*3<=counter) ch = i;
	}
	for (int i=0;i<n;++i) for (int j=0;j<n;++j){
		if (grid[i][j]=='X'&&(i+j)%3==ch) grid[i][j]='O';
	}
	
	for (string s:grid){
		for (char x:s) cout << x;
		cout << "\n";
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}