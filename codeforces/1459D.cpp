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
#define PB push_back
#define sz(x) (int)(x).size()

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
int dp[101][10100], nxt[101][10100];
vi a, b;

inline void reset(){
	for (int j=0;j<=100;j++) for (int k=0;k<10100;k++)
			nxt[j][k] = -1;
	nxt[0][0] = 0;
}

void solve()
{
	int n;
	cin >>n;
	a.resize(n), b.resize(n);
	ll B = 0LL;
	int mx = 0LL;
	for (int i=0;i<n;i++){
		cin >> a[i] >>b[i];
		B += b[i];
		mx = max(mx,a[i]);
	}
	cout <<fixed<< setprecision(10);
	memset(dp, -1, sizeof(dp));
	dp[0][0] = 0;
	for (int i=1;i<=n;i++){
		reset();
		for (int j=1;j<=i;j++){
			for (int k=n*mx;k>=0;k--){
				nxt[j][k] = dp[j][k];
				if (k-a[i-1]>=0&&dp[j-1][k-a[i-1]]!=-1) nxt[j][k] = max(nxt[j][k], dp[j-1][k-a[i-1]]+b[i-1]);
			}
		}
		for (int j=0;j<=100;++j) for (int k=10000;k>=0;k--) dp[j][k] = nxt[j][k];
		
	}
	for (int i=1;i<=n;i++){
		double ans = 0;
		for (int k=0;k<=n*mx;k++){
			dbg(k, dp[i][k]);
			if (dp[i][k]==-1) continue;
			ans = max(ans, min((double)k, (double)dp[i][k]/2+(double)B/2));
		}
		cout << ans << " ";
	}
	cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}