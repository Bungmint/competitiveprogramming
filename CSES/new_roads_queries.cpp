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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;

pi Edge[200000];

// From the USACO tutorial lol
struct DSU {
	vector<int> e;
	vector<int> mem;
	vector<pair<pi,pi>> ev;
	DSU(int N) { e = vector<int>(N, -1); }

	// get representive component (uses path compression)
	int get(int x) { return e[x] < 0 ? x : get(e[x]); }
	
	bool same_set(int a, int b) { return get(a) == get(b); }
	
	int size(int x) { return -e[get(x)]; }
	
	bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return false;
		if (e[x] > e[y]) swap(x, y);
		ev.pb({{x, e[x]}, {y,e[y]}});
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
			pair<pi,pi> p = ev.back();
			e[p.fi.fi] = p.fi.se;
			e[p.se.fi] = p.se.se;
			ev.pop_back();
		}
	}
};

void div_conq(int l, int r, vector<ar<int,3>> &Q,vi& ans, DSU& dsu){
	if (r-l==1){
		for (auto x:Q){
			ans[x[2]] = l;
		}
		return;
	}
	int m = (l+r)>>1;
	vector<ar<int,3>> past, future;
	dsu.snapshot();
	for (int j=l;j<m;++j){
		dsu.unite(Edge[j].fi, Edge[j].se);
	}
	for (auto x:Q){
		if (dsu.same_set(x[0],x[1])){
			past.pb(x);
		}else{
			future.pb(x);
		}
	}
	div_conq(m, r, future, ans, dsu);
	dsu.rollback();
	div_conq(l, m, past, ans, dsu);
}

void solve()
{
	int n, m, q;
	cin >> n >> m>>q;
	vector<ar<int,3>> Query(q);
	DSU dsu(n);
	for (int i=0;i<m;++i){
		cin >> Edge[i].fi >> Edge[i].se;
		Edge[i].fi--;
		Edge[i].se--;
	}
	for (int i=0;i<q;++i) cin >> Query[i][0]>>Query[i][1], Query[i][2] = i;
	vi ans(q);
	dsu.snapshot();
	for (int i=0;i<m;++i){
		dsu.unite(Edge[i].fi, Edge[i].se);
	}
	vector<ar<int,3>> Q;
	for (int i=0;i<q;++i){
		Query[i][0]--;
		Query[i][1]--;
		int a = Query[i][0], b = Query[i][1], id =Query[i][2];
		if (!dsu.same_set(a, b)){
			ans[id] = -2;
		}else if(a==b){
			ans[id] = -1;
		}else{
			Q.pb(Query[i]);
		}
	}
	dsu.rollback();
	div_conq(0, m, Q, ans, dsu);
	for (int x:ans)cout << x+1 << "\n";
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