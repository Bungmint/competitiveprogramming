// Problem: E. Fib-tree
// Contest: Codeforces - Codeforces Global Round 13
// URL: https://codeforces.com/problemset/problem/1491/E
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
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
using ld = long double;

#define all(v) (v).begin(), (v).end()
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define REP(a) F0R(_, a)

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
    size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

const int N = 2e5+1;
int fib[31];
int sub[N];
vector<pair<int,bool>> g[N];

void dfs(int v, int pv){
	sub[v] = 1;
	for (auto [e, fl]: g[v]){
		if (fl||e==pv) continue;
		dfs(e, v);
		sub[v] += sub[e];
	}
}
void findEdge(int v, int pv, int k, int &u, int &pu){
	for (auto [e, fl]:g[v]){
		if (e!=pv&&!fl){
			if (u) return;
			if (sub[e]==fib[k-1]||sub[e]==fib[k-2]){
				u = e, pu = v;
				break;
			}
			findEdge(e, v, k, u, pu);
		}
	}
}

bool cut(int root, int id){
	if (id<=1) return true;
	dfs(root, 0);
	int u=0, pu=0;
	findEdge(root, 0, id, u, pu);
	if (!u) return false;
	for (auto &[e, fl]:g[u]) if (e==pu) fl = 1;
	for (auto &[e, fl]:g[pu]) if (e==u) fl = 1;
	int x =(sub[u] == fib[id-1]? id-1:id-2);
	int y = (x==id-1? id-2:id-1);
	return (cut(u, x)&&cut(pu, y));
}

void solve()
{
	fib[0] = fib[1] = 1;
	FOR(i, 2, 31) fib[i] = fib[i-1] + fib[i-2];
	int n;
	cin >> n;
	REP(n-1){
		int u, v;
		cin >> u >> v;
		g[u].pb({v, 0}), g[v].pb({u, 0});
	}
	int k = -1;
	F0R(i, 31){
		if (n==fib[i]){
			k = i;
			break;
		}
	}
	if (k==-1){
		cout << "NO\n";
		return;
	}
	cout << (cut(1, k)? "YES":"NO")<<"\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}