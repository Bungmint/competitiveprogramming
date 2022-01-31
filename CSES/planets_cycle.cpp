// Problem: Planets Cycles
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1751
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
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

int succ[200000][20], indeg[200000];
int cycSZ[200000];

void solve()
{
	int n;
	cin >> n;
	for (int i=0;i<n;++i) cin >> succ[i][0], succ[i][0]--, indeg[succ[i][0]]++;
	for (int j=1;j<20;j++) for (int i=0;i<n;++i){
		succ[i][j] = succ[succ[i][j-1]][j-1];
	}
	queue<int> q;
	for (int i=0;i<n;++i){
		if (indeg[i]==0) q.push(i);
	}
	while(sz(q)){

		int v = q.front();
		q.pop();
		indeg[succ[v][0]]--;
		if (indeg[succ[v][0]]==0)q.push(succ[v][0]);
	}
	for (int i=0;i<n;++i){
		if (indeg[i]&&cycSZ[i]==0){
			int len = 1;
			for (int y = succ[i][0];;y = succ[y][0]){
				dbg(y, i);
				if (y==i) break;
				len++;
			}
			cycSZ[i] = len;
			for (int y=succ[i][0];y!=i;y=succ[y][0]){
				cycSZ[y] = len;
			}
			dbg(i);
		}
	}
	for (int i=0;i<n;++i){
		if (!cycSZ[i]){
			int x = i;
			int k = 0;
			for (int j=19;j>=0;j--){
				if (cycSZ[succ[x][j]]==0) x = succ[x][j], k+=(1<<j);
			}
			dbg(i, x);
			cycSZ[i] = cycSZ[succ[x][0]]+k+1;
		}
	}
	for (int i=0;i<n;++i) cout << cycSZ[i]<<" ";
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