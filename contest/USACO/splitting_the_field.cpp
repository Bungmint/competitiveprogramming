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

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
#define sz(x) (int)(x).size()

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
const int MOD = 1e9 + 7; //998244353
pl cow[50000];


void setIO(string s) { // the argument is the filename without the extension
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}

void solve()
{
	int n;
	cin >>n;
	for (int i=0;i<n;i++) cin >> cow[i].first >> cow[i].second;
	sort(cow, cow+n, [](pi p1, pi p2){
		return p1.first<p2.first;
	});
	ll mx = cow[0].first;
	ll MAXy = -INF, MINy = INF;
	vl f(n, -1), g(n, -1);
	for (int i=0;i<n;i++){
		if (f[i]!=-1) continue;
		for (int j=i;j<n&&cow[j].first == cow[i].first;j++){
			MAXy = max(MAXy, cow[j].second);
			MINy = min(MINy, cow[j].second);
		}
		f[i] = (MAXy-MINy)*(cow[i].first-mx);
		for (int j=i;j<n&&cow[j].first==cow[i].first;j++) f[j] = f[i];
	}
	mx = cow[n-1].first;
	MAXy = -INF, MINy = INF;
	for (int i=n-1;i>=0;i--){
		if (g[i]!=-1) continue;
		for (int j=i;j>=0&&cow[j].first == cow[i].first;j--){
			MAXy = max(MAXy, cow[j].second);
			MINy = min(MINy, cow[j].second);
		}
		g[i] = (MAXy-MINy)*(mx-cow[i].first);
		for (int j=i;j>=0&&cow[j].first==cow[i].first;j--) g[j] = g[i];
	}
	assert(g[0]==f[n-1]);
	ll ans = f[n-1];
	for(int i=0;i<n;i++){
		while(i+1<n&&cow[i].first==cow[i+1].first) i++;
		if (i==n-1) continue;
		ans = min(ans, f[i] + g[i+1]);
	}
	
	
	
	
	sort(cow, cow+n, [](pi p1, pi p2){
		return p1.second<p2.second;
	});
	ll my = cow[0].second;
	ll MAXx = -INF, MINx = INF;
	f.assign(n, -1); g.assign(n,-1);
	for (int i=0;i<n;i++){
		if (f[i]!=-1) continue;
		for (int j=i;j<n&&cow[j].second == cow[i].second;j++){
			MAXx = max(MAXx, cow[j].first);
			MINx = min(MINx, cow[j].first);
		}
		f[i] = (MAXx-MINx)*(cow[i].second-my);
		for (int j=i;j<n&&cow[j].second==cow[i].second;j++) f[j] = f[i];
	}
	my = cow[n-1].second;
	MAXx = -INF, MINx = INF;
	for (int i=n-1;i>=0;i--){
		if (g[i]!=-1) continue;
		for (int j=i;j>=0&&cow[j].second == cow[i].second;j--){
			MAXx = max(MAXx, cow[j].first);
			MINx = min(MINx, cow[j].first);
		}
		g[i] = (MAXx-MINx)*(my-cow[i].second);
		for (int j=i;j>=0&&cow[j].second==cow[i].second;j--) g[j] = g[i];
	}
	assert(g[0]==f[n-1]);
	for(int i=0;i<n;i++){
		while(i+1<n&&cow[i].second==cow[i+1].second) i++;
		if (i==n-1) continue;
		ans = min(ans, f[i] + g[i+1]);
	}
	cout << f[n-1]-ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    setIO("split");
    int testcase=1;
    //cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}