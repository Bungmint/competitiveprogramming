// Problem: C. Bottom-Tier Reversals
// Contest: Codeforces - Codeforces Round #740 (Div. 1, based on VK Cup 2021 - Final (Engine))
// URL: https://codeforces.com/contest/1558/problem/C
// Memory Limit: 512 MB
// Time Limit: 2000 ms
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
vi flip(vi& a, int id){//including id
	vi res;
	dbg(a);
	ROF(i, 0, id+1) res.pb(a[i]);
	FOR(i, id+1, sz(a)) res.pb(a[i]);
	dbg(res, id);
	return res;
}

void solve()
{
	int n;
	cin >> n;
	vi a(n);
	F0R(i, n) cin>> a[i];
	// n = odd, n<=2021
	//Check if possible
	bool ok = 1;
	F0R(i, n) if ((i&1)&&(a[i]&1)) ok = 0;
	if (!ok){
		cout << -1 << "\n";
		return;
	}
	vi steps;
	int curSZ = n;
	vi b = a;
	while(curSZ>1){
		int t1 = curSZ-1, t2 = curSZ;
		int id1=-1, id2=-1;
		F0R(i, curSZ){
			if (b[i]==t1) id1 = i;
			if (b[i] == t2) id2 = i;
		}
		assert(id1>=0&&id2>=0);
		assert(id1%2==1&&id2%2==0);
		if (id1==curSZ-2&&id2==curSZ-1){
			
		}else if (id1>id2){
			b = flip(b, id2);
			steps.pb(id2);
			b = flip(b, id1-1);
			steps.pb(id1-1);
			b = flip(b, curSZ-1);
			steps.pb(curSZ-1);
			b= flip(b, curSZ-id1);
			steps.pb(curSZ-id1);
			b = flip(b, curSZ-1);
			steps.pb(curSZ-1);
		}else{
			b = flip(b, id2);
			steps.pb(id2);
			b = flip(b, id2-id1-1);
			steps.pb(id2-id1-1);
			b = flip(b, curSZ-1);
			steps.pb(curSZ-1);
			b= flip(b, curSZ-id2+id1);
			steps.pb(curSZ-id2+id1);
			b = flip(b, curSZ-1);
			steps.pb(curSZ-1);
		}
		dbg(b);
		assert(b[curSZ-1]==t2&&b[curSZ-2]==t1);
		curSZ -= 2;
		b.pop_back();
		b.pop_back();
	}
	if (sz(steps)>(5*n/2))cout << -1 << "\n";
	else{
		cout << sz(steps)<<"\n";
		for (auto x:steps)cout << x+1 << " ";
		if (sz(steps))cout << "\n";
	}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}