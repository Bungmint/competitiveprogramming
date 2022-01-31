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
#define dbg(...) 42
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


const int N=2e5+10, sqrtN = 450;
vi g[N], regionList[25001], precalc[25001];
int region[N], tin[N], tout[N], timer = 0, ver[N];
int a[N];

void dfs(int v, int pv){
	tin[v] = timer++;
	ver[tin[v]] = v;
	for (int e:g[v]){
		if (e!=pv) dfs(e,v);
	}
	tout[v] = timer;
	dbg(tin[v], tout[v], v);
}

void solve()
{
	int n, r, q;
	cin >> n>>r >> q;
	FOR(i, 1, n+1){
		if (i==1){
			cin >> region[i];
		}else{
			int p;
			cin >> p>>region[i];
			g[p].pb(i), g[i].pb(p);
		}
		regionList[region[i]].pb(i);
	}
	dfs(1,0);
	FOR(i, 1, r+1){
		sort(all(regionList[i]), [&](int u, int v){
			return tin[u]<tin[v];
		});
		if (sz(regionList[i])>=sqrtN){
			precalc[i].resize(r+1);
			fill(a, a+n+1, 0);
			for (auto x:regionList[i]) a[tin[x]]++, a[tout[x]]--;
			FOR(j, 1, n)a[j] += a[j-1];
			F0R(j, n) precalc[i][region[ver[j]]]+= a[j];
		}
	}
	while(q--){
		int x, y;
		cin >> x >> y;
		if (sz(regionList[x])>=sqrtN){
			cout << precalc[x][y]<<endl;
		}else{
			int ans = 0;
			dbg(x, y,regionList[x], regionList[y]);
			for (auto v:regionList[x]){
				int l = 0, r = sz(regionList[y])-1, res = sz(regionList[y]);
				while(l<=r){
					int mid = l + (r-l)/2LL;
					if (tin[regionList[y][mid]]>=tin[v]) res = mid, r = mid-1;
					else l = mid+1;
				}
				ans -= res;
				l = 0, r = sz(regionList[y])-1, res = sz(regionList[y]);
				while(l<=r){
					int mid = l + (r-l)/2LL;
					if (tin[regionList[y][mid]]>=tout[v]) res = mid, r = mid-1;
					else l = mid+1;
				}
				ans += res;
				// int L = lb(all(regionList[y]), tin[v])-begin(regionList[y]);
				// int R = lb(all(regionList[y]), tout[v])-begin(regionList[y]);
				// ans += R-L;
			}
			cout << ans << endl;
		}
	}
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