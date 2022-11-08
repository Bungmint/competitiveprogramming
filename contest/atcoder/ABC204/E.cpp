#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vii = vector<vector<int>>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;
using vll = vector<ll>;

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
const int N = 1e5+10;
vector<ar<ll,3>> G[N];
ll t[N], n,m;
bool vis[N];

ll go(ll d, ll time){
	ll base = d/(time+1);
	ll x = sqrt(d) - time - 1;
	if (x<0) return base;
	ll res = x + d/(time+x+1);
	if(x>0) res = min(res, x-1 + d/(time+x));
	res = min(res, x+1+d/(time+x+2));
	return res;
}

void dijkstra(){
	pqg<pair<ll,ll>> pq;
	fill(t, t+N, LINF);
	t[1] = 0;
	pq.push({t[1], 1});
	while(!pq.empty()){
		ll dist = pq.top().first, v = pq.top().second;
		dbg(dist, v);
		pq.pop();
		if (t[v]<dist) continue;
		for (ar<ll,3> a: G[v]){
			if (dist+a[1]+ go(a[2], dist) < t[a[0]]){
				t[a[0]] = dist +a[1]+ go(a[2],dist);
				pq.push({t[a[0]], a[0]});
			}
		}
	}
}

void solve()
{
	cin >> n >> m;
	for (int i=0;i<m;i++){
		int u, v, c, d;
		cin >> u  >> v >> c >> d;
		G[u].PB({v, c,d});
		G[v].PB({u, c,d});
	}
	dijkstra();
	if (t[n]==LINF) cout << -1 << "\n";
	else cout << t[n]<<"\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int testcase=1;
    //cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}