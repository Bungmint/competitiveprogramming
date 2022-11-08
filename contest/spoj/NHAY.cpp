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
const int MOD = 1e9 + 7, P2 = 1e9+9, BASE = 137; //998244353
const int N = 2e6+100;
ll pow1[N], inv[N];
ll hsh[N], pref[N];

ll mpow(ll a, ll b){
	ll r = 1;
	while(b){
		if (b&1) r = (r*a)%MOD;
		b/=2;
		a = (a*a)%MOD;
	}
	return r;
}

void pre(){
	pow1[0] = 1; inv[0] = 1;
	int wack = mpow(BASE, MOD-2);
	for (int i=1;i<N;i++) {
		pow1[i] = (pow1[i-1]*BASE) %MOD;
		inv[i] = (inv[i-1]*wack) %MOD;
	}
}

void solve()
{
	while(true){
	string p,s;
	int n, leng;
	if (!(cin >> n)) break;
	cin >> p>>s;
	ll targ = 0LL;
	for (int i=0;i<n;i++){
		dbg(p[i]);
		targ = (targ + ((ll)p[i]-'a'+1LL)*pow1[i])%MOD;
	}
	leng = s.length();
	for (int i=0;i<leng;i++){
		hsh[i] = (s[i]-'a'+1) * pow1[i] %MOD;
		if (i==0) pref[i] = hsh[i];
		else pref[i] = (pref[i-1]+hsh[i]) %MOD;
	}
	vector<int> ans;
	for (int i=0;i<leng-n+1;i++){
		ll val = (pref[i+n-1]-((i==0)?0:pref[i-1]))*inv[i] %MOD;
		val = (val+MOD)%MOD;
		if (targ==val) ans.PB(i);
	}
	for (int x:ans) cout << x <<"\n";
	cout << "\n";
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    pre();
    solve();
}