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

void solve()
{
	int n,x;
	cin >>n>>x;
	vector<ll> v(n), cnt(n);
	for (int i=0;i<n;i++) cin >> v[i];
	ll idx=n-1, mi=INF;
	for (int i=0;i<n;i++){
		ll cur = v[i];
		while(cur%x==0){
			cnt[i]++;
			cur/=x;
		}
		if (mi>cnt[i]){
			idx = i;
			mi =cnt[i];
		}
	}
	ll ans = 0LL;
	for (int i=0;i<=idx;i++){
		ans+=v[i]*(min(mi+2, cnt[i]+1));
	}
	for (int i=idx+1;i<n;i++){
		ans += v[i]*(min(mi+1, cnt[i]+1));
	}
	cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}