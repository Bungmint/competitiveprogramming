// Problem: Problem 3. Springboards
// Contest: USACO - USACO 2020 January Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=995
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
#define int long long
const int MX = 1e5+1;
int t[MX*8], ans[MX];
int n, k;
vi y_order;

void upd(int i, int v, int x, int lx, int rx){
	if (rx-lx==1){
		ckmin(t[x], v);
		return;
	}
	int mid = (lx+rx)>>1;
	if (i<mid) upd(i, v, 2*x+1, lx, mid);
	else upd(i, v, 2*x+2, mid, rx);
	t[x] = min(t[2*x+1], t[2*x+2]);
}
int query(int l, int r, int x, int lx, int rx){
	if (rx<=l||r<=lx){
		return 0;
	}else if (l<=lx&&rx<=r){
		return t[x];
	}
	int mid = (lx+rx)>>1;
	return min(query(l, r, 2*x+1, lx, mid), query(l,r,2*x+2, mid,rx));
}
void insert(int id, int v){upd(id, v, 0, 0, MX*2);}
int yIndex(int y){return lb(all(y_order), y)-y_order.begin();}
int queryMin(int id){return query(0, id+1, 0, 0, MX*2);}

void solve()
{
	cin >> n>>k;
	vector<pair<pii, pii>> points;
	F0R(i, k){
		int x1,y1, x2,y2;
		cin >> x1 >>y1 >> x2 >> y2;
		points.pb({{x1,y1}, {i, -1}});
		points.pb({{x2,y2}, {i, 1}});
		y_order.pb(y1), y_order.pb(y2);
	}
	sort(all(y_order)), y_order.resize(unique(all(y_order))-y_order.begin());
	sort(all(points));
	insert(0,0);
	for (auto &p:points){
		if (p.se.se==-1){
			ans[p.se.fi] = p.fi.fi + p.fi.se + queryMin(yIndex(p.fi.se));
		}else{
			insert(yIndex(p.fi.se), ans[p.se.fi]-p.fi.fi-p.fi.se);
		}
	}
	cout<< queryMin(MX*2-1)+2*n << endl;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef LOCAL
    	setIO("boards");
    #endif
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}