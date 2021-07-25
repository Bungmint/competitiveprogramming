// Problem: D. Fill The Bag
// Contest: Codeforces - Educational Codeforces Round 82 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1303/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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


int brute_force(vi &a, int lim, int pos, ll n){
	if (n==0) return 0;
	if (pos==-1) return -1;
	if (!((1LL<<pos)&n)) return brute_force(a, lim, pos-1, n);
	if (a[pos]){
		a[pos]--;
		int v= brute_force(a, lim, pos-1, n-(1LL<<pos));
		a[pos]++;
		return v;
	}
	
	
	int bigger = -1;
	int res = -1;
	for (int j=pos+1;j<=lim;++j) if (a[j]){bigger = j;break;}
	// Not using the big boi
	vi b = a;
	ll sum = 0;
	for (int j=pos-1;j>=0;j--){
		ll k= min((ll)a[j], ((1LL<<pos)-sum)/(1LL<<j));
		sum += k*(1LL<<j);
		b[j]-=k;
	}
	dbg(lim, pos, n, sum);
	if (sum==(1LL<<pos)){
		int v =  brute_force(b, pos, pos-1, n-(1LL<<pos));
		if (v>=0){
			res = v;
		}
	}
	dbg(res);
	// using it
	if (bigger!=-1){
		a[bigger]--;
		for (int j=bigger-1;j>=pos;j--) a[j]++;
		int k = bigger-pos;
		int v = brute_force(a, pos, pos-1, n-(1LL<<pos));
		if (v>=0){
			v+=k;
			res = (res<0? v:min(res,v));
		}
	}
	
	dbg(n, pos, res);
	return res;
}

void solve()
{
	ll n;
	int m;
	cin >> n>> m;
	vi a(m);
	for (int i=0;i<m;++i) cin >> a[i];
	if (n>=(ll)1e14){puts("-1");return;}
	vi cnt(48);
	for (int i=0;i<m;++i){
		int lg = log2(a[i]);
		cnt[lg]++;
	}
	int lg = log2(n);
	cout << brute_force(cnt, 30, lg, n)<< "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}