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
const int MOD = 998244353;
const int N = 1e6+100; // Only advised to use it under 1e7 (More Memory)
int lp[N + 1], f[N], g[N],h[N], d[N];
vector<int> pr, divisor;
void linsieve()
{
    for (int i = 2; i <= N; i++)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
        {
            lp[i * pr[j]] = pr[j];
        }
    }
}

inline ll add(ll a, ll b){
	return (a+b+MOD)%MOD;	
}

inline ll mult(ll a, ll b){
	return ((a%MOD)*(b%MOD))%MOD;
}


ll modpow(ll a, ll b){
	ll r = 1;
	while(b){
		if (b&1) r = mult(r, a);
		a = mult(a, a);
		b/=2;
	}
	return r;
}

inline ll divide(ll a, ll b){
	return ((a%MOD)*modpow(b, MOD-2))%MOD;
}

void conv(int x){
	if (x==1){
		divisor.pb(1);
		return;
	}
	vpi primes;
	while(x>1){
		int p = lp[x];
		int cnt = 0;
		while(x%p==0){cnt++;x/=p;}
		primes.pb({p, cnt});
	}
	divisor.pb(1);
	for (int i=0;i<sz(primes);++i){
		int s = sz(divisor);
		ll v = primes[i].fi;
		for (int k=1;k<=primes[i].se;++k){
			for(int j=0;j<s;++j){
				divisor.pb(divisor[j]*v);
			}
			v*=primes[i].fi;
		}
	}
}


void solve()
{
	for (int i=1;i<=1000000;++i){
		for (int j=i;j<=1000000;j+=i){
			d[j]++;
		}
	}
	int n;
	cin >> n;
	vl a(n);
	for (int i=0;i<n;++i) cin >> a[i];
	for (int i=0;i<n;++i){
		divisor.clear();
		conv(a[i]);
		for (int d:divisor){
			f[d] = add(f[d], a[i]);
			g[d] = add(g[d], a[i]*a[i]);
		}
	}
	ll ans = 0;
	for (int i=1;i<=1000000;++i){
		h[i] = add(mult(f[i], f[i]), -g[i]);
		h[i] = divide(h[i], 2);
	}
	for (int i=1000000;i>=1;--i){
		for (int j=2;j*i<=1000000;j++){
			h[i] = add(h[i], -h[j*i]);
		}
		ans = add(ans, divide(h[i], i));
	}
	
	cout << ans<<"\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    linsieve();
    solve();
}