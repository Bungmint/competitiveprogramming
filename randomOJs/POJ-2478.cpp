#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <iostream>
#include <vector>
using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
#define sz(x) (int)(x).size()
#define ll long long

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353
const int MAXN = 1e6+1;

vector<int> prime;
bool is_composite[MAXN];
ll f[MAXN];
int cnt[MAXN];

ll pw(ll a, int b){
	ll r = 1;
	while(b){
		if (b&1) r = (r*a);
		a*=a;
		b/=2;
	}
	return r;
}

void sieve () {
	std::fill (is_composite, is_composite + MAXN, false);
	for (int i = 2; i < MAXN; ++i) {
		if (!is_composite[i]){
			prime.push_back (i);
			f[i] = i-1;
			cnt[i] = 1;
		}
		for (int j = 0; j < prime.size () && i * prime[j] < MAXN; ++j) {
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0){
				ll pk = pw(prime[j], cnt[i]);
				f[i*prime[j]] = f[i]/f[pk] *pk*(prime[j]-1);
				cnt[i*prime[j]] = cnt[i]+1;
				break;
			}else{
				f[i*prime[j]] = f[i]*f[prime[j]];
				cnt[i*prime[j]] = 1;
			}
		}
	}
	for (int i=1;i<MAXN;i++){
		f[i] += f[i-1];	
	}
}

void solve()
{
	while(true){
		int n;
		cin >> n;
		if (!n) return;
		cout << f[n]<<"\n";
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    sieve();
    solve();
}