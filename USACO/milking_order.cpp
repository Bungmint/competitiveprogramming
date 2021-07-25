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
const int N = 1e5+1;
vi G[N], revG[N], order;
int in[N], out[N];
bool vis[N];

void dfs(int v){
	vis[v] = 1;
	for (int e:G[v]) if (!vis[e]) dfs(e);
	order.pb(v);
}

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<vi> observations(m);
	for (int i=0;i<m;++i){
		int k, prev;
		cin >> k;
		for (int j=0;j<k;++j){
			int t;
			cin >> t;
			observations[i].pb(t);
		}
	}
	int l = 1, r = m;
	vi ans(n);
	iota(all(ans), 1);
	while(l<=r){
		int m = l + (r-l)/2;
		for (int i=1;i<=n;++i){
			in[i] = out[i] = 0;
			G[i].clear();revG[i].clear();
			vis[i]=0;
		}
		order.clear();
		for (int i=0;i<m;++i){
			int prev = -1;
			for (int x:observations[i]){
				if(prev==-1){
					prev= x;
				}else{
					G[prev].pb(x);
					revG[x].pb(prev);
					in[x]++;
					out[prev]++;
					prev = x;
				}
			}
		}
		for (int i=1;i<=n;++i){
			if (!vis[i]) dfs(i);
		}
		reverse(all(order));
		vi p(n+1);
		for (int i=0;i<n;++i){
			p[order[i]] = i;
		}
	
		bool ok = 1;
		for (int x:order){
			for (int e:G[x]){
				
				if (p[x]>p[e]){
					ok =0;
				}
			}
		}
		if (ok){
			pqg<int> pq;
			for (int i=1;i<=n;++i){
				if (!in[i]) pq.push(i);
			}
			ans.clear();
			while(!pq.empty()){
				int v = pq.top();
				pq.pop();
				ans.pb(v);
				for (int e:G[v]){
					in[e]--;
					if (!in[e]) pq.push(e);
				}
			}
			l = m+1;
		}else r = m-1;
	}
	for (int i=0;i<n;++i){
		if (i<n-1) cout << ans[i]<< " ";
		else cout << ans[i];
	}
	
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    setIO("milkorder");
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}
