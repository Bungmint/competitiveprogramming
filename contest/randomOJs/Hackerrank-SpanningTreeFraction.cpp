// Problem: Spanning Tree Fraction
// Contest: HackerRank - Week of Code 31
// URL: https://www.hackerrank.com/contests/w31/challenges/spanning-tree-fraction/problem
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
const int N = 1e5+1;
int n, m;

struct Edge{
	int u, v, a, b;
};

namespace DSU{
	int sz[N],p[N];
	int cnt;
	void init(){
		fill(sz, sz+N, 1);
		iota(p, p+N, 0);
		cnt = n;
	}
	int get(int x){return (x==p[x]?x:p[x]=get(p[x]));}
	void unite(int x, int y){
		x = get(x), y = get(y);
		if (x!=y){
			if (sz[x]<sz[y]) swap(x,y);
			p[y] = x;
			sz[x] += sz[y];
			cnt--;
		}
	}
};
using namespace DSU;


const ld eps = 1e-9;
bool hi(ld a, ld b){return (a-b>eps);}
bool low(ld a, ld b){return (b-a>eps);}
ld mul(Edge& e, ld x){return (ld)((ld)e.a-(ld)e.b*(ld)x);}

void solve()
{
	cin >> n >> m;
	vector<Edge> edges(m);
	for (int i=0;i<m;++i){
		int u, v, a, b;
		cin >> u >> v >> a >> b;
		edges[i] = {u,v,a,b};
	}
	ld l = 0, r = 100, ans;
	for (int i=0;i<100;++i){
		ld mid = l + (r-l)/2;
		ld sum = 0;
		sort(all(edges), [&](Edge p, Edge q){
			return hi(mul(p, mid), mul(q, mid));
		});
		init();
		for (int i=0;i<m;++i){
			Edge e = edges[i];
			ld v = mul(e,mid);
			dbg(e.u, e.v);
			bool same = get(e.u)==get(e.v);
			if (hi(0, sum+v)&&!same) break;
			if (!same){
				sum += v;
				unite(e.u, e.v);
			}
		}
		if (cnt>1) r = mid;
		else l = mid, ans = mid;
	}
	int aSum=0, bSum=0;
	dbg(ans);
	sort(all(edges), [&](Edge p, Edge q){
		return hi(mul(p, ans), mul(q, ans));
	});
	init();
	for (int i=0;i<m;++i){
		Edge e = edges[i];
		dbg(e.u, e.v);
		bool same = get(e.u)==get(e.v);
		if (!same){
			unite(e.u, e.v);
			aSum += e.a, bSum += e.b;
		}
	}
	int g = gcd(aSum, bSum);
	cout << aSum/g<<"/"<<bSum/g << endl;
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