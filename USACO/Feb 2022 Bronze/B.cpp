#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int,int>;

#define all(x) (int)(x).size()
#define fi first
#define se second

bool strong(vi& a, vi&b){
	int win =0, tied = 0, loss=0;
	for (int i=0;i<4;++i) for (int j=0;j<4;++j){
		if (a[i]>b[j]) win++;
		else if (a[i]==b[j]) tied++;
		else loss++;
	}
	// cerr << sum<<"\n";
	return win>loss;
}

void solve(){
	vi a(4), b(4);
	for (int i=0;i<4;++i) cin >> a[i];
	for (int i=0;i<4;++i) cin >> b[i];
	if (!strong(a, b)&&!strong(b, a)) {
		cout << "no"<<"\n";
		return;
	}
	vi aa = {1,4,8,9};
	// cerr << strong(aa, a);
	for (int c1 = 1;c1<=10;c1++)
		for (int c2=1;c2<=10;c2++)
			for (int c3=1;c3<=10;c3++)
				for (int c4=1;c4<=10;c4++){
					vi c = {c1,c2,c3,c4}; 
					if (strong(a, b)&&strong(b, c)&&strong(c,a)){
						cout << "yes"<<"\n";
						return;
					}
					if (strong(b,a)&&strong(c,b)&&strong(a,c)){
						cout << "yes"<<"\n";
						return;
					}
				}
	cout << "no"<<"\n";
}

int main(){
	cin.tie(0)->sync_with_stdio(0);
	int testcase;
	cin >> testcase;
	while(testcase--) solve();
	return 0;
}