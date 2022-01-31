// Problem: D. Returning Home
// Contest: Codeforces - Codeforces Round #675 (Div. 2)
// URL: https://codeforces.com/contest/1422/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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
	int n, m;
	cin >> n >> m;
	int sx, sy, fx, fy; cin >> sx >> sy >> fx >> fy;
	vpi Point(m+1);
	vi orderX, orderY;
	F0R(i, m){
		cin >> Point[i].fi >> Point[i].se;
		orderX.pb(Point[i].fi), orderY.pb(Point[i].se);
	}
	Point[m] = {sx, sy};orderX.pb(Point[m].fi), orderY.pb(Point[m].se);
	sort(all(orderX)), sort(all(orderY));
	orderX.resize(unique(all(orderX))-begin(orderX)), orderY.resize(unique(all(orderY))-begin(orderY));
	ll ans = abs(sx-fx) + abs(sy-fy);
	vl distRow(m+1, INF*2), distCol(m+1, INF*2);
	vector<vi> row(m+1), col(m+1);
	F0R(i, m+1){
		Point[i].fi = lb(all(orderX), Point[i].fi)-begin(orderX);
		Point[i].se = lb(all(orderY), Point[i].se)-begin(orderY);
		row[Point[i].fi].pb(i), col[Point[i].se].pb(i);
	}
	pqg<ar<ll,3>> pq;
	distRow[Point[m].fi] = distCol[Point[m].se] = 0;
	pq.push({0LL, Point[m].fi, 1LL});
	pq.push({0LL, Point[m].se, -1LL});
	while(sz(pq)){
		auto [d, v, t] = pq.top(); pq.pop();
		if (t==1){
			if (d>distRow[v]) continue;
			//Up & down
			if (v+1<sz(orderX)&&ckmin(distRow[v+1],d+orderX[v+1]-orderX[v])){
				pq.push({distRow[v+1], v+1, 1});
			}
			if (v&&ckmin(distRow[v-1],d+orderX[v]-orderX[v-1])){
				pq.push({distRow[v-1], v-1, 1});
			}
			F0R(i, sz(row[v])){
				auto [x, y] = Point[row[v][i]];
				if (ckmin(distCol[y], d)) pq.push({distCol[y], y, -1});
			}
		}else{
			if (d>distCol[v]) continue;
			if (v+1<sz(orderY)&&ckmin(distCol[v+1],d+orderY[v+1]-orderY[v])){
				pq.push({distCol[v+1], v+1, -1});
			}
			if (v&&ckmin(distCol[v-1],d+orderY[v]-orderY[v-1])){
				pq.push({distCol[v-1], v-1, -1});
			}
			F0R(i, sz(col[v])){
				auto [x, y] = Point[col[v][i]];
				if (ckmin(distRow[x], d)) pq.push({distRow[x], x, 1});
			}
		}
	}
	F0R(i, m+1){
		auto [x,y]= Point[i];
		ckmin(ans, min(distRow[x], distCol[y])+abs(fx-orderX[x])+abs(fy-orderY[y]));
	}
	cout << ans << "\n";
	
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