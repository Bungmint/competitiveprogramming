#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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
int cnt = 1, ans = 0LL, id = -1;
int mdv = -1, md = -1;
vector<int> G[250000];
ar<int,4> vals[250000];


void dfs(int V, int pV, ar<int,3> p, int dep){
	if (p[0]>=vals[V][0]||p[1]>=vals[V][1])return;
	bool ok = true;
	for (int &e:G[V]){
		if (e!=pV) dfs(e,V, p, dep+1);
		if (vals[e][0]>=p[0]&&vals[e][1]>=p[1]) ok = false;
	}
	if (!ok) return;
	dbg(dep);
	if (md<dep){
		mdv=V;
		md = dep;
	}
}
void depdfs(int V, int pV, int t){
	t++;
	if (ans < t){
		ans = t;
		id = V;
	}
	for (int &e:G[V]){
		if (e!=pV) depdfs(e,V,t);
	}
}

void solve()
{
	int n, w, h;
	cin >> n>> w >> h;
	vector<ar<int,3>> env;
	for (int i=0;i<n;i++){
		int w1, h1;
		cin >> w1 >> h1;
		if (w1<=w||h1<=h) continue;
		env.PB({w1, h1,i});
	}
	if (sz(env)==0){
		cout << 0<<"\n";
		return;
	}
	sort(all(env), greater<ar<int,3>>());
	vals[0] = {INF,INF, INF};
	for (int i=0;i<sz(env);i++){
		mdv = -1, md = -1;
		dfs(0,-1,env[i], 0);
		if (mdv==-1) continue;
		vals[cnt] = {env[i][0], env[i][1], env[i][2], mdv};
		G[mdv].PB(cnt);
		cnt++;
	}
	depdfs(0,-1,0);
	cout << --ans<<"\n";
	while(id!=0){
		cout << vals[id][2]+1 << " ";
		id = vals[id][3];
	}
	cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}