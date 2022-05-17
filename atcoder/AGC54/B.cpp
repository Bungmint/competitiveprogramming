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
const int N = 101;
ll dp[N][N*1000];



ll mpow(ll a, ll b){
	ll r = 1;
	while(b){
		if (b&1) r = (r*a)%MOD;
		b/=2;
		a = (a*a)%MOD;
	}
	return r;
}

ll mult(ll a, ll b){
	return ((a%MOD)*(b%MOD))%MOD;
}

void solve()
{
	int n;
	cin >> n;
	vi w(n);
	int sum = 0, targ;
	for (int i=0;i<n;++i) cin >> w[i], sum += w[i];
	if (sum&1){
		cout << 0 << "\n";
		return;
	}
	targ = sum/2;
	dp[0][0] = 1;
	for (int i=0;i<n;++i){
		for (int k=n;k>=1;--k){
			for (int j=targ;j-w[i]>=0;j--){
				dp[k][j] += dp[k-1][j-w[i]];
				dp[k][j]%=MOD;
			}
		}
	}
	vl fact(n+1,1);
	for (int i=1;i<=n;++i){
		fact[i] = (fact[i-1]*i)%MOD;
	}
	
	
	ll ans = 0;
	for (int k=0;k<=n;++k){
		dbg(k, dp[k][targ]);
		ans += mult(fact[k], mult(fact[n-k], dp[k][targ]));
		ans%=MOD;
	}
	cout<<ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}