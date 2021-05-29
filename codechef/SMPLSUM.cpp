#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

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

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353
const int N = 1e7;
int big[N+1];

inline void pre(){
	for (int i=1;i<=N;i++){big[i]=1;}
	for (int i=2;i<=N;i++){
		if (big[i]==1){
			for (int j=i;j<=N;j+=i) big[j] = i;
		}
	}
}
ll pow(ll a, ll b){
	if (b==1 ) return a;
	ll m = pow(a,b/2);
	if (b%2==0) return m*m;
	return m*m*a;
}

void solve()
{
	int n;
	cin >> n;
	ll ans = 1LL;
	while(n>1){
		ll prime = big[n];
		ll cnt = 0;
		while(n%prime==0){
			cnt++;
			n/=prime;
		}
		if (cnt==1){
			ans *= (pow(prime, 2)- prime+1);
			continue;
		}
		ans *= (pow(prime, 2*cnt+1)+1)/(prime+1);
	}
	cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    pre();
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}