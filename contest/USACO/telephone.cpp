// Problem: Problem 2. Telephone
// Contest: USACO - USACO 2021 January Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=1090
// Memory Limit: 256 MB
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
int cow[50010];
int adj[51][51];
int cost[51][50001];
int n, k;

void solve()
{
	cin >> n >> k;
	for (int i=1;i<=n;++i) cin >> cow[i];
	char c;
	for (int i=1;i<=k;++i){
		for (int j=1;j<=k;++j){
			cin >> c;
			adj[i][j] = (c=='1');
		}
		adj[i][0] = adj[i][cow[n]];
	}
	cow[n] = 0;
	memset(cost, -1, sizeof(cost));
	deque<pi> q;
	cost[cow[1]][1] = 0;
	q.pb({cow[1], 1});
	while(sz(q)){
		auto [b,loc] = q.front();
		dbg(b, loc);
		q.pop_front();
		if (loc-1>=1&&cost[b][loc-1]==-1){
			cost[b][loc-1] = cost[b][loc] +1;
			q.pb({b, loc-1});
		}
		if (loc+1<=n&&cost[b][loc+1]==-1){
			cost[b][loc+1] = cost[b][loc] +1;
			q.pb({b, loc+1});
		}
		if (adj[b][cow[loc]]&&cost[cow[loc]][loc]==-1){
			cost[cow[loc]][loc] = cost[b][loc];
			q.push_front({cow[loc], loc});
		}
	}
	cout << cost[0][n]<<endl;
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