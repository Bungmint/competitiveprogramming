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
ar<pair<int,int>,7> nulll;

const int N = 1e6; // Only advised to use it under 1e7 (More Memory)
int lp[N + 1];
vector<int> pr;
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


void solve()
{
	int n;
	cin >> n;
	vector<int> v(n);
	vector<ar<pair<int,int>, 7>> vap(n);
	for (int i=0;i<n;i++) cin >> v[i];
	int q;
	cin>> q;
	int q1=0,even=0,odd=0,sq = 0;
	map<ar<pair<int,int>,7>, int> s1;
	set<ar<pair<int,int>, 7>> s2;
	for (int i=0;i<n;i++){
		ar<pair<int,int>,7> cur;
		int num = v[i];
		int cnt = 0;
		while(num>1){
			int p = lp[num];
			int t = 0;
			while(num%p==0){
				t++;
				num/=p;
			}
			if (t%2==0) continue;
			cur[cnt] = {p,t%2};
			cnt++;
		}
			vap[i] = cur;
			s1[cur]++;
		
		q1 = max(q1, s1[cur]);
	}
	for (int i=0;i<n;i++){
		if (vap[i]==nulll){
			sq++;
			continue;
		}
		if (s1[vap[i]]%2){
			odd = max(odd, s1[vap[i]]);
			continue;
		}
		if (s2.count(vap[i])) continue;
		s2.insert(vap[i]);
	
		even+=s1[vap[i]];
	}
	int q2 = max(even + sq, odd);
	while(q--){
		ll w;
		cin >> w;
		if (w==0)cout << q1<<"\n";
		if (w>=1) cout << q2 << "\n";
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    linsieve();
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}