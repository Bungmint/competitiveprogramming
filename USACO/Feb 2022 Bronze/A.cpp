#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int,int>;

#define all(x) (int)(x).size()
#define fi first
#define se second


void solve(){
	vector<string> ans(3), guess(3);
	vi ansCnt(26);
	int g = 0, y = 0;
	for (int i=0;i<3;++i) cin >> ans[i];
	for (int i=0;i<3;++i) cin >> guess[i];
	for (int i=0;i<3;++i) for (int j=0;j<3;++j){
		if (ans[i][j]==guess[i][j]) g++;
		else ansCnt[ans[i][j]-'A']++;
	}
	for (int i=0;i<3;++i) for (int j=0;j<3;++j){
		if (ans[i][j]!=guess[i][j]&&ansCnt[guess[i][j]-'A']) ansCnt[guess[i][j]-'A']--, y++;
	}
	cout << g << "\n"<< y << "\n";
}

int main(){
	cin.tie(0)->sync_with_stdio(0);
	solve();
	return 0;
}