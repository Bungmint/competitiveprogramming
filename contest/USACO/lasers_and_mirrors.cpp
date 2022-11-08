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

void setIO(string s) { // the argument is the filename without the extension
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}

void solve()
{
	int n, xL, yL, xB, yB;
	cin >> n >> xL >> yL >> xB >> yB;
	vpi mirror(n);
	vi orderX = {xL, xB}, orderY= {yL, yB};
	for (int i=0;i<n;++i){
		cin >> mirror[i].fi >> mirror[i].se;
		orderX.pb(mirror[i].fi), orderY.pb(mirror[i].se);
	}
	sort(all(orderX)), sort(all(orderY));
	orderX.resize(unique(all(orderX))-orderX.begin());
	orderY.resize(unique(all(orderY))-orderY.begin());
	int cnt1 = sz(orderX), cnt2 = sz(orderY);
	vector<vi> XtoY(cnt1+cnt2), YtoX(cnt2+cnt1);
	xL = lb(all(orderX), xL)-orderX.begin();
	xB = lb(all(orderX), xB)-orderX.begin();
	yL = lb(all(orderY), yL)-orderY.begin();
	yB = lb(all(orderY), yB)-orderY.begin();
	for (int i=0;i<n;++i){
		mirror[i].fi = lb(all(orderX), mirror[i].fi)-orderX.begin();
		mirror[i].se = lb(all(orderY), mirror[i].se)-orderY.begin();
		XtoY[mirror[i].fi].pb(mirror[i].se);
		YtoX[mirror[i].se].pb(mirror[i].fi);
	}
	dbg();
	vi dx(cnt1,INF), dy(cnt2, INF);
	queue<pi> q;
	dx[xL] = dy[yL] = 0;
	q.push({xL, 0});
	q.push({yL,1});
	while(!q.empty()){
		int line = q.front().fi, t = q.front().se;
		q.pop();
		if (t){
			for (int e:YtoX[line]){
				if (dx[e]>dy[line]+1){
					dx[e] = dy[line]+1;
					q.push({e, 0});
				}
			}
		}else{
			for (int e:XtoY[line]){
				if (dy[e]>dx[line]+1){
					dy[e] = dx[line]+1;
					q.push({e, 1});
				}
			}
		}
	}
	cout << (dx[xB]==INF&&dy[yB]==INF ? -1:min(dx[xB], dy[yB]))<<"\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    setIO("lasers");
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}