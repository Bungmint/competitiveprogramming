// Problem: C. Permute Digits
// Contest: Codeforces - Educational Codeforces Round 36 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/915/C
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
ll f[1<<19][2];
ll power[19];
vi aDig, bDig;


ll dp(int mask, bool low){
	ll &res = f[mask][low];
	if (res!=-1) return res;
	if (mask==(1<<sz(aDig))-1) return res = 0LL;
	int cnt = __builtin_popcount(mask);
	int DMT = (low? 9:bDig[cnt]);
	res = -LINF*2;
	for (int i=0;i<sz(aDig);++i){
		if (mask&(1<<i)) continue;
		if (aDig[i]>DMT) continue;
		res = max(res, power[sz(aDig)-1-cnt]*aDig[i]+dp(mask+(1<<i), low|(aDig[i]<DMT)));
	}
	return res;
}

void solve()
{
	ll a, b;
	cin >> a >> b;
	while(a){
		aDig.pb(a%10);
		a/=10;
	}
	while(b){
		bDig.pb(b%10);
		b/=10;
	}
	reverse(all(aDig)), reverse(all(bDig));
	if (sz(aDig)>sz(bDig)){
		cout << 0 << endl;
		return;
	}
	if (sz(aDig)<sz(bDig)){
		sort(all(aDig), greater<int> ());
		for (int x:aDig) cout << x;
		cout << endl;
		return;
	}
	memset(f, -1, sizeof(f));
	ll res = 0;
	for (int i=0;i<sz(aDig);++i){
		if (aDig[i]&&aDig[i]<=bDig[0]){
			res = max(res, power[sz(aDig)-1]*aDig[i] + dp((1LL<<i), (aDig[i]<bDig[0])));
		}
	}
	cout << res << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    power[0] = 1LL;
    for (int i=1;i<19;++i){
    	power[i] = power[i-1]*10;
    }
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}