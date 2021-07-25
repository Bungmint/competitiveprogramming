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
const int N = 110;
int grid[N][N];
pi dp[N][N][14];

void solve()
{
	int n, m, K;
	cin >> n >> m >>K;
	K++;
	for (int i=n;i>=1;i--) {
		string s;
		cin >> s;
		for (int j=1;j<=m;++j) grid[i][j] = s[j-1]-'0';
	}
	for (int i=0;i<=n;++i){
		for (int j=0;j<=m;++j) 
			for (int k=0;k<=K;++k)
				dp[i][j][k] = {-1, -1};
	}
	for (int i=0;i<=m;++i)dp[0][i][0] = {0,0};
	
	//dp.se indicates which path the pawn took (0: Left, 1: Right)
	for (int i=1;i<=n;++i){
		for (int j=1;j<=m;++j){
			for (int k=0;k<K;++k){
				int mx = -1, id = -1;
				if (j>1){
					if (dp[i-1][j-1][k]!=make_pair(-1, -1)){
						mx = dp[i-1][j-1][k].fi;
						id = 0;
					}
				}
				if (j<m){
					if (dp[i-1][j+1][k]!=make_pair(-1,-1)&&mx<dp[i-1][j+1][k].fi){
						mx = dp[i-1][j+1][k].fi;
						id = 1;
					}
				}
				if (mx==-1) continue;
				dp[i][j][(k+grid[i][j])%K] = {mx+grid[i][j], id};
				
			}
		}
	}
	
	
	
	int res = -1;
	int en = -1;
	for (int i=1;i<=m;i++){
		if (dp[n][i][0].fi>res&&dp[n][i][0].se!=-1){
			res = dp[n][i][0].fi;
			en = i;
		}
	}
	
	
	if (res ==-1){
		cout <<-1 << "\n";
		return;
	}
	cout << res << "\n";
	string s = "";
	int row = n;
	int st=0;
	int val = 0;
	while(row!=0){
		if (row==1){
			st = en;
			break;
		}
		pi p = dp[row][en][val];
		dbg(p);
		s += (p.se == 0? 'R':'L');
		val-=grid[row][en];
		val%=K;
		val = (val+K)%K;
		row--;
		en = (p.se==0? en-1:en+1);
	}
	reverse(all(s));
	cout << st << "\n";
	
	cout << s << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}