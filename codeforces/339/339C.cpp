#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;
using pl = pair<ll, ll>;
using vl = vector<ll>;

#define all(v) (v).begin(), (v).end()
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound

template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v)
{
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}
void dbg_out()
{
    cerr << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353
const ar<int,3> nut = {-1,-1,-1};
ar<int,3> dp[30][11][1010];
vi weight;
int m;
string s;

void dping(int x, int used, int time){
	if (time==m+1) return;
	if (abs(x)>=10) return;
	for (int w:weight){
		if (w==used) continue;
		if (time&1){
			if (x<=0&&x+w<=0) continue;
			if (x>0) continue;
			if (dp[x+w+10][w][time+1] != nut)continue;
			dp[x+w+10][w][time+1] = {x, used, time};
			dping(x+w, w, time+1);
		}else{
			if (x<=0) continue;
			if (x>0&&x-w>=0) continue;
			if (dp[x-w+10][w][time+1] != nut) continue;
			dp[x-w+10][w][time+1] = {x, used, time};
			dping(x-w, w, time+1);
		}
	}
}

void solve()
{
	cin >> s>>m;
	for (int i=1;i<=10;++i){
		if (s[i-1]=='1'){
			weight.pb(i);
		}
	}
	if (sz(weight)==0){
		cout << "NO\n";
		return;
	}
	if (sz(weight)==1){
		if (m>1) cout << "NO\n";
		else cout << "YES\n" << weight[0]<<"\n";
		return;
	}
	for (int i=0;i<30;++i) for (int j=0;j<=10;++j) for (int k=0;k<=1009;++k) dp[i][j][k] = nut;
	dping(0,0,1);
	for (int i=-9;i<=9;++i) for (int j=1;j<=10;++j){
		if (dp[i+10][j][m+1] !=nut){
			cout << "YES\n";
			vi ans;
			ar<int,3> cur = dp[i+10][j][m+1];
			ans.pb(j);
			ar<int,3> meh = {0,0,1};
			dbg(ans);
			while(cur!=meh){
				ans.pb(cur[1]);
				cur = dp[cur[0]+10][cur[1]][cur[2]];
			}
			reverse(all(ans));
			for (int x:ans)cout << x << " ";
			return;
		}
	}
	cout << "NO\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}