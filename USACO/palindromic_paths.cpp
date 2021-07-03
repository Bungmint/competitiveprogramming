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
const int N = 501;
char grid[N][N];
int n;
ll dp[N][N], nxt[N][N];

void setIO(string s) { // the argument is the filename without the extension
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}

void solve()
{
	cin >> n;
	for (int i=0;i<n;++i){
		string s;
		cin >> s;
		for (int j=0;j<n;j++){
			grid[i][j] = s[j];
		}
	}	
	for (int i=0;i<n;++i){
		dp[i][i] = 1;
	}
	for (int i=n-1;i>=1;--i){
		memset(nxt,0, sizeof(nxt));
		for (int a=0;a<n;a++){
			int rowA = a;
			int colA = i-1-a;
			if (colA<0) continue;
			for (int b=0;b<n;b++){
				int rowB = b;
				int colB = 2*n-i-rowB-1;
				if (colB>=n) continue;
				if (grid[rowA][colA]!=grid[rowB][colB]) continue;
				nxt[rowA][rowB] += dp[rowA][rowB];
				if (rowA+1<n) nxt[rowA][rowB] += dp[rowA+1][rowB];
				if (rowB-1>=0) nxt[rowA][rowB] += dp[rowA][rowB-1];
				if (rowA+1<n&&rowB-1>=0) nxt[rowA][rowB] += dp[rowA+1][rowB-1];
				nxt[rowA][rowB]%=MOD;
			}
		}
		for (int i=0;i<n;++i) for (int j=0;j<n;++j) dp[i][j] = nxt[i][j];
	}
	cout << dp[0][n-1] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    setIO("palpath");
    solve();
}