// Problem: Mancunian and Twin Permutations
// Contest: HackerEarth - Data Structures - Advanced Data Structures - Fenwick (Binary Indexed) Trees
// URL: https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/mancunian-and-twin-permutations-d988930c/
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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
struct Query{
	int l1, r1, l2,r2, id;
};

// Uses zero index for the input
template<typename T>
struct BIT{
	int N, lg;
	vector<T> bit;
	BIT(int n){bit.resize(n+1);N = n;lg=log2(N);}
	void upd(int i, T v){ 
		for (++i;i<=N;i+=i&-i) bit[i]+=v;	
	}
	T query(int i){
		T res = 0;
		for (++i;i>0;i-=i&-i) res+=bit[i];
		return res;
	}
	int lower_bound(T v){
		T sum = 0, id = 0;
		R0F(i, lg+1){
			if (id+(1<<i)<=N&&sum+bit[id+(1<<i)]<v){
				sum += bit[id+(1<<i)];
				id += (1<<i);
			}
		}
		return id; // Zero index
		// return id+1; // One index
	}
};

void solve()
{
	int n;
	cin >> n;
	vector<vector<Query>> st(n), ft(n);
	vector<vi> Points(n);
	vi aPos(n), bPos(n);
	vector<bool> vis(n);
	F0R(i, n){
		int t;
		cin >> t;
		t--;
		aPos[t] = i;
	}
	F0R(i, n){
		int t;
		cin >> t;
		t--;
		bPos[t] = i;
	}
	F0R(i, n){
		Points[bPos[i]].pb(aPos[i]);
	}
	dbg(aPos, bPos, Points);
	int q;
	cin >> q;
	vi ans(q);
	F0R(i, q){
		Query qq;
		cin >> qq.l1>>qq.r1>>qq.l2>>qq.r2;
		qq.id = i;
		qq.l1--,qq.r1--,qq.l2--, qq.r2--;
		st[qq.l2].pb(qq), ft[qq.r2].pb(qq);
		ans[qq.id] = qq.r1-qq.l1+1;
	}
	BIT<ll> bit(n);
	F0R(i,n){
		for (auto qq:st[i]){
			ans[qq.id] += bit.query(qq.r1)-bit.query(qq.l1-1);
		}
		for (auto x:Points[i]){
			bit.upd(x, 1);
		}
		for (auto qq:ft[i]){
			ans[qq.id] -= bit.query(qq.r1)-bit.query(qq.l1-1);
		}
	}
	for (auto x:ans)cout << x << "\n";
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