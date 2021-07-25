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
using vpl = vector<pl>;
using ld = long double;

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
const int MOD = 1e9 + 7; //998244353;
ar<int,3> dp[1<<24];
int x[24], y[24], n, xs, ys;


inline int dist(int i){
	return (x[i]-xs)*(x[i]-xs) + (y[i]-ys)*(y[i]-ys);
}
inline int dist(int i, int j){
	return (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);
}

int dping(int mask){
	if (mask==(1<<n)-1){
		return 0;
	}
	if (dp[mask][0]!=-1) return dp[mask][0];
	int res = INF;
	int i2, f;
	for (int i=0;i<n;++i){
		if (!(mask&(1<<i))){
			f = i;
			break;
		}
	}
	for (int j=f+1;j<n;++j){
		if (!(mask&(1<<j))){
			int cur = dping((mask|(1<<f)|(1<<j)));
			int d1 = dist(f)+dist(j)+dist(f,j);
			int d2 = dist(f)*2+dist(j)*2;
			if (d1<d2&&cur+d1<res){
				i2 = j;
				res = cur+d1;
			}else if (d1>=d2&&cur+d2<res){
				i2 = -j;
				res = cur +d2;
			}
		}
	}
	dp[mask] = {res, f, i2};
	return res;
}


void solve()
{
	cin >> xs >> ys >> n;
	for (int i=0;i<(1<<n);++i) dp[i] = {-1, -1, -1};
	for (int i=0;i<n;++i) cin >> x[i] >> y[i];
	if (n&1){
		int ans = INF;
		int alone;
		for (int i=0;i<n;++i){
			int cur = 2*dist(i)+dping(1<<i);
			if (cur<ans){
				alone = i;
				ans = cur;;
			}
		}
		cout << ans << "\n";
		vpi res;
		cout << 0 << " "<< alone+1 << " "<< 0 << " ";
		int r = 1<<alone;
		while(r!=(1<<n)-1){
			int i = dp[r][1], j = dp[r][2];
			res.pb({i,j});
			r |= (1<<i);
			r|=(1<<abs(j));
		}
		for (pi x:res){
			if (x.se>0)cout << x.fi+1 << " "<< x.se+1 << " "<< 0<<" ";
			else cout << x.fi+1 << " "<< 0 << " "<< -x.se+1 << " "<< 0<<" ";
		} 
		cout << "\n";
	}else{
		cout << dping(0)<<"\n";
		vpi res;
		int r =0;
		while(r!=(1<<n)-1){
			int i = dp[r][1], j = dp[r][2];
			res.pb({i,j});
			r |= (1<<i);
			r|=(1<<abs(j));
		}
		cout << 0 << " ";
		for (pi x:res){
			if (x.se>0)cout << x.fi+1 << " "<< x.se+1 << " "<< 0<<" ";
			else cout << x.fi+1 << " "<< 0 << " "<< -x.se+1 << " "<< 0<<" ";
		}
		cout << "\n";
	} 
	
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}