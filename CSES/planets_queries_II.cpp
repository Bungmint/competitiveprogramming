// Problem: Planets Queries II
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1160
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

const int MX = 2e5+1, LOG = 20;

int succ[MX], up[MX][LOG], n, Q, comp[MX];
int dist[MX], cycSZ[MX];
bool cyc[MX];
int indeg[MX];

pi calc(int v){
	int k = 0;
	for (int i=LOG-1;i>=0;i--){
		if (!cyc[up[v][i]]) v = up[v][i], k += (1<<i);
	}
	return {k+1, up[v][0]};
}

void solve()
{
	cin >> n >> Q;
	memset(cyc,1, sizeof(cyc));
	for (int i=1;i<=n;++i) cin >> succ[i], up[i][0] = succ[i], indeg[succ[i]]++;
	for (int j=1;j<LOG;++j) for (int i=1;i<=n;++i) up[i][j] = up[up[i][j-1]][j-1];
	queue<int> q;
	for (int i=1;i<=n;++i){
		if (indeg[i]==0) q.push(i);
	}
	while(sz(q)){
		int v = q.front();
		q.pop();
		cyc[v] = 0;
		indeg[succ[v]]--;
		if (indeg[succ[v]]==0) q.push(succ[v]);
	}
	int cur = 0;
	for (int i=1;i<=n;++i){
		if (cyc[i]&&!cycSZ[i]){
			cycSZ[i] = 1;
			comp[i] = cur++;
			if (i!=succ[i]) dist[succ[i]] = 1;
			for (int x = succ[i];x!=i;x = succ[x]){
				cycSZ[i]++;
				comp[x] = comp[i];
				if (succ[x]!=i)dist[succ[x]] = dist[x]+1; 
			}
			for (int x = succ[i];x!=i;x = succ[x]){
				cycSZ[x] = cycSZ[i];
			}
		}
	}
	for (int i=0;i<Q;++i){
		int a, b;
		cin >> a>>b;
		if (cyc[a]&&cyc[b]){
			if (comp[a]==comp[b]){
				cout << (dist[b]-dist[a]+cycSZ[a])%cycSZ[a]<<"\n";
			}else cout << -1 << "\n";
		}else if (cyc[a]){
			cout << -1 << "\n";
		}else if (cyc[b]){
			auto [k, x] = calc(a);
			if (comp[x]==comp[b]){
				cout << k+(dist[b]-dist[x]+cycSZ[x])%cycSZ[x]<<"\n";
			}else cout << -1 << "\n";
		}else{
			auto [k1, x] =calc(a);
			auto [k2, y] = calc(b);
			 if (comp[x]==comp[y]&&k1>=k2){
				int d = k1-k2;
				for (int i=LOG-1;i>=0;i--){
					if (d&(1<<i)) a = up[a][i];
				}
				if (a==b){
					cout << d<<"\n";
				}else cout << -1 << "\n";
			}else cout << -1 << "\n";
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