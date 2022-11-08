// Problem: Sky Code
// Contest: POJ - Southeastern European Regional Programming Contest 2008
// URL: http://poj.org/problem?id=3904
// Memory Limit: 65 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// #pragma GCC optimize("O3")
// #pragma GCC target("sse4")
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

#define all(v) (v).begin(), (v).end()
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define REP(a) F0R(_, a)

const int MN = 100001;
int a[MN];
ll f[5], g[5];
int cnt[MN], exact[MN];
int MA;
ll mu[MN];
vi pr;


void linsieve(){
	fill(mu, mu+MN, 2);
	mu[1] = 1;
	FOR(i, 2, MN){
		if (mu[i]==2){
			mu[i] = -1;
			pr.pb(i);
		}
		for (int j=0;j<sz(pr)&&i*pr[j]<MN;++j){
			if (i%pr[j]==0){
				mu[i*pr[j]] = 0;
				break;
			}else mu[i*pr[j]] = mu[i]*mu[pr[j]];
		}
	}
}

void solve()
{
	int n;
	while(cin >> n){
		MA = 0;
		F0R(i, n) cin >> a[i], MA = max(MA, a[i]);
		memset(cnt, 0, (MA+1)*sizeof(int));
		memset(exact, 0, (MA+1)*sizeof(int));
		memset(f, 0LL, sizeof(f));memset(g, 0LL, sizeof(g));
		F0R(i, n){
			exact[a[i]]++;
		}
		ROF(i, 1, MA+1){
			for (int j=1;j*i<=MA;++j){
				cnt[i] += exact[j*i];
			}
		}
		FOR(i, 1, 5){
			FOR(d, 1, MA+1){
				ll v = 1;
				F0R(j, i) v *= cnt[d];
				f[i] += v*mu[d];
			}
		}
		g[1] = f[1];
		g[2] = f[2] - g[1];
		g[2]/=2LL;
		g[3] = f[3] - g[1] - 6*g[2];
		g[3]/=6LL;
		g[4] = f[4] - g[1] - g[2]*14 - g[3] * 36;
		g[4]/=24LL;
		cout << g[4]<<"\n";
	}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    linsieve();
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}