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
const ll MAXN = 1510, P1 = 1e9+7, P2 = 1e9+9, BASE = 137;
ll pow1[MAXN], pow2[MAXN], inv1[MAXN], inv2[MAXN], n, k, cnt = 0, INV_BASE1, INV_BASE2, c1[MAXN], c2[MAXN];
ll pref1[MAXN], pref2[MAXN];
bool g[26];
string s, mask;

ll mpow(ll a, ll b, ll m){
	ll res = 1LL;
	while(b){
		if (b&1) res = (res*a)%m;
		b/=2;
		a = (a*a)%m;
	}
	return res;
}

void pre(){
	pow1[0] = pow2[0] =1;
	inv1[0] = inv2[0] = 1;
	INV_BASE1 = inv1[1] = mpow(BASE, P1-2, P1);
	INV_BASE2 = inv2[1] = mpow(BASE, P2-2, P2);
	for (int i=1;i<MAXN;i++){
		pow1[i] = (pow1[i-1]*BASE)%P1;
		pow2[i] = (pow2[i-1]*BASE)%P2;
		inv1[i] = (inv1[i-1]*INV_BASE1)%P1;
		inv2[i] = (inv2[i-1]*INV_BASE2)%P2;
	}
}
void hasher(){
	for (int i=0;i<n;i++){
		c1[i] = ((s[i]-'a'+1LL)*pow1[i]) %P1;
		c2[i] = ((s[i]-'a'+1LL)*pow2[i]) %P2;
		if (i==0) pref1[i] = c1[i], pref2[i] = c2[i];
		else pref1[i] += pref1[i-1] + c1[i], pref2[i] += pref2[i-1] +c2[i];
		pref1[i]%=P1;
		pref2[i]%=P2;
	}
}

ll hashing1(int le, int ri){
	ll val = pref1[ri];
	if (le>0) val-= pref1[le-1];
	val = (val+P1)%P1;
	return (val*inv1[le])%P1;
}
ll hashing2(int le, int ri){
	ll val = pref2[ri];
	if (le>0) val-= pref2[le-1];
	val = (val+P2)%P2;
	return (val*inv2[le])%P2;
}




void solve()
{
	cin >> s >>mask >> k;
	for (int i=0;i<26;i++)
		if (mask[i]=='1') g[i] = 1;
	int l = 0;
	n = (int)s.length();
	hasher();
	set<pair<int,int>> hashes;
	for (int r=0;r<n;r++){
		if (!g[s[r]-'a']) cnt++;
		while(cnt>k&&l<n){
			if (!g[s[l]-'a']) cnt--;
			l++;
		}
		
		for (int i=l;i<=r;i++){
			int hash1 = hashing1(i,r), hash2 = hashing2(i,r);
			hashes.insert({hash1, hash2});
		}
	}
	cout << sz(hashes) << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    pre();
    solve();
    
}