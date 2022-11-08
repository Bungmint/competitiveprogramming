#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vpl = vector<pll>;

#define all(x) (int)(x).size()
#define fi first
#define se second
#define pb push_back

const ll LINF = 1e18;


void solve(){
	ll p, q;
	cin >> p >> q;
	ll cur = p, cost = 0;
	vpl layers = {{p, cost}};
	while(cur>1){
		if (cur&1){
			layers.pb({(cur+1)/2, cost+2});
			cost += 2;
		}else{
			layers.pb({cur/2, cost+1});
			cost++;
		}
		cur = (cur+1)/2;
	}
	ll ans = LINF*2;
	for (auto [x, c]:layers){
		ll pp = 0;
		for(ll y = x; y<=q;y*=2){
			ll val = c + pp;
			ll dif = q-y;
			for (ll i=pp;i>=0;i--){
				val += dif/(1LL<<i);
				dif -= (1LL<<i)*(dif/(1LL<<i));
			}
			ans = min(ans, val);
			pp++;
		}
	}
	cout << ans << "\n";
}

int main(){
	cin.tie(0)->sync_with_stdio(0);
	int testcase;
	cin >> testcase;
	while(testcase--) solve();
	return 0;
}