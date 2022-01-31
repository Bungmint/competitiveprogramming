// Problem: Teleporters Path
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1693
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
const int N = 1e5+1;
vi ans;
multiset<int> g[N];
int in[N], out[N];

void find_tour(int v){
	while(sz(g[v])){
		int u = *g[v].begin();
		g[v].erase(g[v].begin());
		find_tour(u);
	}
	ans.pb(v);
}

void solve()
{
	int n,m;
	cin >> n >> m;
	for (int i=0;i<m;++i){
		int u,v;
		cin >> u >> v;
		g[u].insert(v);
		in[v]++, out[u]++;
	}
	for (int i=1;i<=n;++i){
		if (i==1){
			if (in[i]!=out[i]-1){
				cout << "IMPOSSIBLE"<<endl;
			}
		}else if (i==n){
			if (in[i]!=out[i]+1){
				cout << "IMPOSSIBLE"<<endl;
			}
		}else{
			if (in[i]!=out[i]){
				cout << "IMPOSSIBLE"<<endl;
				return;
			}
		}
	}
	g[n].insert(1);
	find_tour(1);
	reverse(all(ans));
	if (sz(ans)<m+2){
		cout << "IMPOSSIBLE"<<endl;
		return;
	}
	int lastOne = -1, lastN = -INF;
	dbg(ans);
	for (int i=0;i<sz(ans);++i){
		if (ans[i]==1&&lastN==i-1){
			break;
		}else if (ans[i]==1){
			lastOne = i;
		}else if (ans[i]==n){
			lastN = i;
		}
	}
	dbg(lastOne, lastN);
	for (int i=0;i<lastOne;++i) cout << ans[i]<<" ";
	for (int i=lastN+1;i<sz(ans);++i) cout << ans[i]<<" ";
	for (int i=lastOne+1;i<=lastN;++i) cout << ans[i]<<" ";
	
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