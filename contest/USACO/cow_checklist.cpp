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
ll dp[1001][1001][2];

void setIO(string s) { // the argument is the filename without the extension
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}

ll sq(ll a){
	return a * a;
}

void solve()
{
	for (int i=0;i<=1000;i++) for (int j=0;j<=1000;j++) for (int k=0;k<2;k++) dp[i][j][k] = LINF;
	dp[1][0][0] = 0;
	int h, g;
	cin >> h >> g;
	vl hx(h+1), hy(h+1), gx(g+1), gy(g+1);
	for (int i=1;i<=h;i++) cin >> hx[i] >> hy[i];
	for (int i=1;i<=g;i++) cin >> gx[i] >> gy[i];
	for (int i=1;i<=h;i++){
		for (int j=0;j<=g;j++){
			for (int k=0;k<2;k++){
				if (i>1&&k==0){
					dp[i][j][k] = dp[i-1][j][0] + sq(hx[i]-hx[i-1]) + sq(hy[i]-hy[i-1]);
					if (j) dp[i][j][k] = min(dp[i][j][k], dp[i-1][j][1]+sq(hx[i]-gx[j]) + sq(hy[i]-gy[j]));
					
				}
				if (j&&k==1){
					dp[i][j][k] = dp[i][j-1][0] + sq(gx[j]-hx[i])+sq(gy[j]-hy[i]);
					if (j>1) dp[i][j][k] = min(dp[i][j][k], dp[i][j-1][1] + sq(gx[j]-gx[j-1])+sq(gy[j]-gy[j-1]));
				}
			}
			dbg(i,j, dp[i][j][0], dp[i][j][1]);
		}
	}
	cout << (dp[h][g][0]!=LINF? dp[h][g][0]:dp[h][g][1]+ sq(hx[h]-gx[g])+sq(hy[h]-gy[g]))<<"\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    setIO("checklist");
    int testcase=1;
    //cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}