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
const int N = 1e6+10;
ll fact[N], inv[N], inv_fact[N], kpow[N], kpref[N];
int n, k;

ll mod_pow(ll a, ll b){
	ll re = 1LL;
	while(b){
		if (b&1) re  = (re*a)%MOD;
		b/=2;
		a = (a*a)%MOD;
	}
	return re%MOD;
}
void precalc()
{
    for (ll i = 0; i < N; i++)
    {
        if (i == 0)
            fact[i] = 1LL;
        else
            fact[i] = (i * fact[i - 1]) % MOD;
    }
    inv[1] = 1;
    for (int i=2;i<N;i++)
    	inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
    for (int i=1;i<N;i++){
    	kpow[i] = mod_pow(i, k);
    }
    for (int i=1;i<N;i++){
    	kpref[i] = (kpref[i-1] + kpow[i])%MOD;
    }
    inv_fact[0] = inv_fact[1] = 1;
    for (int i=2;i<N;i++)
    	inv_fact[i] = (inv_fact[i-1] * inv[i])%MOD;
}
inline int norm(int n) {
	n %= MOD;
	(n < 0) && (n += MOD);
	return n;
}

inline ll mul(ll a, ll b){
	return ((a*b)%MOD+MOD)%MOD;
}
inline ll _div(ll a, ll b){
	return (a*mod_pow(b, MOD-2))%MOD;
}


ll nCk(ll n, ll k)
{
    if (n < k)
        return 0LL;
    return (((fact[n] * inv_fact[k]) % MOD) * inv_fact[n - k]) % MOD;
}

void solve()
{
	cin >> n >> k;
	precalc();
	if (n<k+2){
		cout << kpref[n] << "\n";
		return;
	}
	ll ans = 0LL, L = 1; 
	for (int i=1;i<=k+1;i++){
		L = mul(L, n-i);
		dbg(L);
		L = _div(L, norm(-i));
	}
	dbg(L);
	for (int i=0;i<=k+1;i++){
		ans = (ans + (L*kpref[i])%MOD)%MOD;
		dbg(L, kpref[i]);
		if (i+1>=k+2) break;
		L = mul(L, _div(norm(n - i), norm(n - (i + 1))));
		L = mul(L, _div(norm(i - (k+2 - 1)), norm(i + 1)));
		dbg(L);
	}
	cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}