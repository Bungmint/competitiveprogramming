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
ll dp[1001][1001];
int fx[1001], fy[1001];
int cx[1001], cy[1001];

inline int cost(int a, int b){
	return (fx[a]-cx[b])*(fx[a]-cx[b])+(fy[a]-cy[b])*(fy[a]-cy[b]);
}

void setIO(string s) { // the argument is the filename without the extension
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}

void solve()
{
	for (int i=0;i<=1000;i++) for (int j=0;j<=1000;j++) dp[i][j] = LINF;
	int n, m;
	cin >> n >> m;
	cin >> fx[0] >> fy[0] >> cx[0] >> cy[0];
	string s, t;
	cin >> s >> t;
	for (int i=1;i<=n;i++){
		fx[i] = fx[i-1], fy[i] = fy[i-1];
		if (s[i-1]=='N'){
			fy[i]++;
		}else if (s[i-1]=='E'){
			fx[i]++;
		}else if (s[i-1] == 'S'){
			fy[i]--;
		}else fx[i]--;
	}
	for (int i=1;i<=m;i++){
		cx[i] = cx[i-1], cy[i] = cy[i-1];
		if (t[i-1]=='N'){
			cy[i]++;
		}else if (t[i-1]=='E'){
			cx[i]++;
		}else if (t[i-1] == 'S'){
			cy[i]--;
		}else cx[i]--;
	}
	for (int i=0;i<=n;i++){
		for (int j=0;j<=m;j++){
			if (i==0&&j==0){
				dp[i][j] = 0;
			}else if (i==0){
				dp[i][j] = dp[i][j-1] + cost(i,j);
			}else if (j==0){
				dp[i][j] = dp[i-1][j] + cost(i,j);
			}else{
				dp[i][j] = dp[i-1][j] + cost(i,j);
				dp[i][j] = min(dp[i][j], dp[i][j-1]+cost(i,j));
				dp[i][j] = min(dp[i][j], dp[i-1][j-1]+cost(i,j));
			}
		}
	}
	cout << dp[n][m]<<"\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    setIO("radio");
    solve();
}