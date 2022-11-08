// Problem: E. Cheap Dinner
// Contest: Codeforces - Educational Codeforces Round 104 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1487/E
// Memory Limit: 512 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

void solve()
{
	int n1, n2, n3, n4;
	int m1, m2, m3;
	cin >> n1 >> n2 >> n3 >> n4;
	vi a(n1), b(n2), c(n3), d(n4);
	vi minA(n1, INF), minB(n2,INF), minC(n3, INF);
	for (int i=0;i<n1;++i){
		cin >> a[i];
	}
	for (int i=0;i<n2;++i){
		cin >> b[i];
	}
	for (int i=0;i<n3;++i){
		cin >> c[i];
	}
	for (int i=0;i<n4;++i){
		cin >> d[i];
	}
	vector<vi> forbAB(n1), forbBC(n2), forbCD(n3);
	cin >> m1;
	for (int i=0;i<m1;++i){
		int x,y;
		cin >> x >> y;
		x--,y--;
		forbAB[x].pb(y);
	}
	cin >> m2;
	for (int i=0;i<m2;++i){
		int x,y;
		cin >> x >> y;
		x--,y--;
		forbBC[x].pb(y);
	}
	cin >> m3;
	for (int i=0;i<m3;++i){
		int x,y;
		cin >> x >> y;
		x--,y--;
		forbCD[x].pb(y);
	}
	//CD
	map<int,int> deez;
	for (int i=0;i<n4;++i){
		deez[d[i]]++;
	}
	for (int i=0;i<n3;++i){
		for (int x:forbCD[i]){
			deez[d[x]]--;
			if (deez[d[x]]==0) deez.erase(d[x]);
		}
		minC[i] = (deez.empty()? INF: c[i]+deez.begin()->fi);
		for (int x:forbCD[i]){
			deez[d[x]]++;
		}
	}
	deez.clear();
	for (int i=0;i<n3;++i){
		deez[minC[i]]++;
	}
	for (int i=0;i<n2;++i){
		for (int x:forbBC[i]){
			deez[minC[x]]--;
			if (deez[minC[x]]==0) deez.erase(minC[x]);
		}
		minB[i] = (deez.empty()? INF: min(INF,b[i]+deez.begin()->fi));
		for (int x:forbBC[i]){
			deez[minC[x]]++;
		}
		dbg(minB[i]);
	}
	deez.clear();
	for (int i=0;i<n2;++i){
		deez[minB[i]]++;
	}
	for (int i=0;i<n1;++i){
		for (int x:forbAB[i]){
			deez[minB[x]]--;
			if (deez[minB[x]]==0) deez.erase(minB[x]);
		}
		minA[i] = (deez.empty()? INF: min(INF,a[i]+deez.begin()->fi));
		for (int x:forbAB[i]){
			deez[minB[x]]++;
		}
	}
	int res = INF;
	for (int i=0;i<n1;++i) res = min(res, minA[i]);
	cout << (res==INF? -1:res)<<endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}