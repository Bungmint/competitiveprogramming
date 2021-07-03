#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 2e5+1;
ll BIT[N], val[N], a[N], n, q;

void upd(int i, int v){
	ll m = (i&1? i*v:-i*v);
	v = (i&1? v:-v);
	for (;i<=n;i+=i&-i){
		BIT[i] += v;
		val[i] += m;
	}
	
}

ll query(int i){
	ll ans = 0;
	for (int j=i;j>0;j-=j&-j){
		ans += val[j];
	}
	return ans;
}

ll query(int l, int r){
	ll v =  query(r)-query(l-1);
	ll sum = 0;
	for (int i=r;i>0;i-=i&-i){
		sum += BIT[i];
	}
	for (int i=l-1;i>0;i-=i&-i){
		sum -= BIT[i];
	}
	return (l&1? v - sum*(l-1): -v+sum*(l-1));
}

void solve(){
	cin >> n >> q;
	for (int i=0;i<=n;++i) a[i] = BIT[i] = val[i] = 0;
	ll ans = 0LL;
	for (int i=1;i<=n;++i){
		cin >> a[i];
		upd(i, a[i]);
	}
	while(q--){
		char op;
		cin >> op;
		if (op=='U'){
			int x, v;
			cin >> x >> v;
			upd(x,v-a[x]);
			a[x] = v;
		}else{
			int l, r;
			cin >> l >> r;
			ans += query(l,r);
		}
	}
	cout << ans << "\n";
	
}

int main(){
	int t;
	cin >> t;
	for (int i=1;i<=t;++i){
		cout << "Case #"<<i << ": ";
		solve();
	}
}