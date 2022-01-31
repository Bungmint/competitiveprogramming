// Problem: C. Complete the MST
// Contest: Codeforces - Codeforces Round #715 (Div. 1)
// URL: https://codeforces.com/contest/1508/problem/C
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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

struct Edge{
	int u, v, w;
	bool operator<(const Edge& other) const{
		return w<other.w;
	}
};

// From the USACO tutorial lol
struct DSU {
	vector<int> e;
	vector<int> mem;
	vector<pair<pii,pii>> ev;
	DSU(int N) { e = vector<int>(N, -1); }

	// get representive component (uses path compression)
	// To use rollback, disable path compression
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	
	bool same_set(int a, int b) { return get(a) == get(b); }
	
	int size(int x) { return -e[get(x)]; }
	
	bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return false;
		ev.pb({{x, e[x]}, {y,e[y]}});
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
		return true;
	}
	
	void snapshot(){
		mem.pb(sz(ev));
	}
	
	void rollback(){
		if (mem.empty())return;
		int SZ = mem.back();
		mem.pop_back();
		while(sz(ev)!=SZ){
			pair<pii,pii> p = ev.back();
			e[p.fi.fi] = p.fi.se;
			e[p.se.fi] = p.se.se;
			ev.pop_back();
		}
	}
};

void solve()
{
	ll n, m;
	cin >>n >> m;
	vector<Edge> used(m);
	vector<set<int>> g(n);
	vi toremove(n), toremoveID(n);
	int SZ = n;
	DSU dsu(n);
	iota(all(toremove), 0);
	iota(all(toremoveID), 0);
	int xum = 0;
	F0R(i, m){
		cin >> used[i].u >> used[i].v >> used[i].w;
		used[i].u--, used[i].v--;
		g[used[i].u].insert(used[i].v), g[used[i].v].insert(used[i].u);
		xum ^= used[i].w;
	}
	ll ans = 0;
	sort(all(used));
	if (m+n<=n*(n-1LL)/2LL){
		queue<int> q;
		F0R(i, n){
			if (toremoveID[i]<SZ){
				q.push(i);
				SZ--;
				int last = toremove[SZ];
				swap(toremove[SZ], toremove[toremoveID[i]]);
				swap(toremoveID[last], toremoveID[i]);
				while(sz(q)){
					int v = q.front();
					q.pop();
					stack<int> todo;
					F0R(j, SZ){
						if (!g[v].count(toremove[j])){
							todo.push(toremove[j]);
						}
					}
					while(sz(todo)){
						int x = todo.top();
						todo.pop();
						SZ--;
						int last = toremove[SZ];
						swap(toremove[SZ], toremove[toremoveID[x]]);
						swap(toremoveID[last], toremoveID[x]);
						q.push(x);
						dsu.unite(x, v);
					}
				}
			}
		}
		F0R(i, m){
			Edge &e = used[i];
			if (dsu.unite(e.u, e.v)){
				ans += e.w;
			}
		}
		cout << ans;
	}else{
		DSU dummy(n);
		bool ok = 0;
		F0R(i, n){
			FOR(j, i+1, n){
				if (!g[i].count(j)){
					dbg(i, j);
					dsu.unite(i,j);
				}
			}
		}
		ll mi = INT_MAX;
		ll ans = xum;
		F0R(i, m){
			Edge &e = used[i];
			if (!dummy.unite(e.u,e.v)) continue;
			else if (dsu.unite(e.u, e.v))ans+=e.w;
			else ckmin(mi, (ll)e.w);
		}
		cout << (mi<xum? ans-xum+mi: ans);
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