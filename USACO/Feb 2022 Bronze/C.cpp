#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int,int>;

#define all(x) (int)(x).size()
#define fi first
#define se second


void solve(){
	int n;
	cin >> n;
	vi a(n);
	for (int i=0;i<n;++i){
		cin >> a[i];
	}
	if (n==1){
		cout << 0 << "\n";
		return;
	}
	if (a[0]>a[1]||a[n-2]<a[n-1]){
		cout <<-1 << "\n";
		return;
	}
	ll sum = 0;
	for (int i=0;i<n;i+=2){
		if (i+1<n){
			if (a[i]>a[i+1]) {cout << -1 << "\n";return;}
			else if (a[i]<a[i+1]){
				if (i+2<n){
					if(a[i+2]<a[i+1]-a[i]){
						cout <<-1 << "\n";return;
					}
					sum += 2LL*(a[i+1]-a[i]);
					a[i+2] -= (a[i+1]-a[i]);
					a[i+1] -= (a[i+1]-a[i]);
				}else{
					cout << -1 << "\n"; return;
				}
			}
		}
	}
	cerr << sum << "\n";
	for (int i=0;i<n;++i){
		sum += 1LL * a[i];
	}
	cerr << sum << "\n";
	sum -= 1LL*(*min_element(a.begin(), a.end()))*n;
	cout << sum << "\n";
	
}

int main(){
	cin.tie(0)->sync_with_stdio(0);
	int testcase;
	cin >> testcase;
	while(testcase--) solve();
	return 0;
}