// Problem: F - Greedy Takahashi
// Contest: AtCoder - AtCoder Beginner Contest 212
// URL: https://atcoder.jp/contests/abc212/tasks/abc212_f
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
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

vector<ar<int,3>> succ[100011];

vector<ar<int,3>> up[100011][20];

void solve()
{
	int n, m, q;
	cin >> n >> m >> q;
	vector<vector<ar<int,3>>> v(n+1); 
	for (int i=0;i<m;++i){
		int a, b, s, t;
		cin >> a >> b >> s >> t;
		v[a].pb({s, t, b});
	}
	for (int i=1;i<=n;++i)sort(all(v[i]));
	for (int i=1;i<=n;++i){
		for (auto [s, t, b]: v[i]){
			ar<int,3> targ = {t, -INF, -INF};
			int k = lb(all(v[b]), targ)-v[b].begin();
			succ[i].pb({b, k, t});
		}
		succ[i].pb({i, sz(v[i]), INT_MAX});
		for (int j=0;j<=19;++j) up[i][j].resize(sz(succ[i]));
		for (int j=0;j<=sz(v[i]);++j){
			up[i][0][j] = succ[i][j];
		}
	}
	for (int i=1;i<=19;++i){
		for (int j=1;j<=n;++j){
			for (int k=0;k<=sz(v[j]);++k){
				auto [x,y,z] = up[j][i-1][k];
				up[j][i][k] = up[x][i-1][y];
			}
		}
	}
	
	
	for (int i=0;i<q;++i){
		int x, y, z;
		cin >> x >> y >> z;
		ar<int,3> targ = {x, -INF, -INF};
		int k = lb(all(v[y]), targ)-v[y].begin();
		int u = y;
		for (int j=19;j>=0;j--){
			auto [a,b, c] = up[u][j][k];
			if (c<z){
				u = a, k= b; 
			}
		}
		if (up[u][0][k][0]==u){
			cout << u << "\n";
		}else{
			int start = v[u][k][0];
			if (start<z){
				cout << u<<" "<< v[u][k][2]<<"\n";
			}else cout << u << "\n";
		}
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