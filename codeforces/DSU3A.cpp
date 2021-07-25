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
const int N = 2e5+1;
int p[N], SZ[N];
vpi mem;
vi snap;
int cnt;

int get(int x){return (x==p[x]? x: get(p[x]));}

void merge(int x, int y){
	x = get(x), y = get(y);
	if (x==y) return;
	mem.pb({x, SZ[x]}); mem.pb({y, SZ[y]});
	if (SZ[x]>SZ[y]) swap(x,y);
	SZ[y]+=SZ[x];
	p[x] = y;
	cnt--;
}

void snapshot(){
	snap.pb(sz(mem));
}

void rollback(){
	int c = 0;
	int v = snap.back();
	snap.pop_back();
	while(sz(mem)!=v){
		pi x = mem.back();
		p[x.fi] = x.fi;
		SZ[x.se] = x.se;
		mem.pop_back();
		c++;
	}	
	c/=2;
	cnt +=c;
}


void solve()
{
	int n, m;
	cin >> n >> m;
	for (int i=1;i<=n;++i) SZ[i] = 1, p[i] = i;
	cnt = n;
	for (int i=0;i<m;++i){
		string s;
		cin >> s;
		if (s=="union"){
			int u,v;
			cin >> u >> v;
			merge(u,v);
			cout << cnt << "\n";
		}else if (s=="persist"){
			snapshot();
		}else{
			rollback();
			cout << cnt << "\n";
		} 
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}