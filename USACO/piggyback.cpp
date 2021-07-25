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

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;

void bfs(int source, vl&d, vector<vi>&g){
	fill(all(d), LINF);
	queue<int> q;
	d[source] = 0;
	q.push(source);
	while(sz(q)){
		int v = q.front();
		q.pop();
		for (int e:g[v]){
			if (d[e]>d[v]+1){
				d[e] = d[v]+1;
				q.push(e);
			}
		}
	}
}

void solve()
{
	ll bessie, elsie, together, n, m;
	cin >> bessie>>elsie>>together>> n>>m;
	ll comb = min(bessie+elsie, together);
	vector<vi> g(n+1);
	vl fromBarn(n+1), fromBessie(n+1), fromElsie(n+1);
	for (int i=0;i<m;++i){
		int u,v;
		cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	bfs(1, fromBessie, g), bfs(2, fromElsie, g), bfs(n, fromBarn, g);
	ll ans = LINF;
	for (int i=1;i<=n;++i){
		if (fromBessie[i]==LINF) continue;
		ans = min(ans, fromBessie[i]*bessie+fromElsie[i]*elsie+comb*fromBarn[i]);
	}
	cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    setIO("piggyback");
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}