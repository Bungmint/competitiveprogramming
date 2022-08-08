// Problem: P4 - Walls
// Contest: DMOJ - IOI '00
// URL: https://dmoj.ca/problem/ioi00p4
// Memory Limit: 16 MB
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


void solve()
{
	int m, n, l;
	cin >> m >> n >> l;
	vi town(l);
	F0R(i, l) cin >> town[i], town[i]--;
	vector<vi> g(m), st(n), dist(l, vi(m, INF));
	map<pii, int> region;
	F0R(i, m){
		int k;
		cin >> k;
		{
			vi v(k);
			F0R(j, k){
				cin >> v[j];
				v[j]--;
				st[v[j]].pb(i);
			}
			F0R(j, k){
				int x = v[j], y = v[(j+1)%k];
				if (region.count({x,y})){
					int z = region[{x,y}];
					g[z].pb(i), g[i].pb(z);
				}else if (region.count({y,x})){
					int z = region[{y,x}];
					g[z].pb(i), g[i].pb(z);
				}else{
					region[{x,y}] = i;
				}
			}
		}
	}
	dbg();
	F0R(i, l){
		int s = town[i];
		dbg(s);
		queue<int> q;
		for (auto x:st[s]) dist[i][x] = 0, q.push(x);
		while(sz(q)){
			int v = q.front();
			dbg(s, v);
			q.pop();
			for (int e:g[v]){
				if (ckmin(dist[i][e], dist[i][v] + 1)){
					q.push(e);
				}
			}
		}
	}
	int sum = INF, ans = 0;
	F0R(i, m){
		int cur = 0;
		F0R(j, l){
			cur += dist[j][i];
		}
		if (ckmin(sum ,cur)) ans = i;
	}
	cout << sum << "\n"<< ans+1 << endl;
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