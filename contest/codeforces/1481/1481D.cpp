#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;

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

void solve()
{
	int n, m;
	string s;
	cin >> n>>m;
	vvi G(n+1, vi(n+1));
	for (int i=1;i<=n;i++){
		cin >> s;
		for (int j=1;j<=n;j++){
			if (i==j) G[i][j]=-1;
			int k = !!(s[j-1]=='b');
			G[i][j] = k;
		}
	}
	if (m&1){
		cout << "YES\n";
		for (int i=0;i<=m;i++) cout << (i&1? 2:1)<<" ";
		cout << "\n";
		return;
	}
	int u = -1, v= -1, w=-1;
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++)
		if (i!=j&&G[i][j]==G[j][i]) u = i, v = j;
	if (u!=-1){
		cout << "YES\n";
		for (int i=0;i<=m;i++) cout << (i&1? v:u)<<" ";
		cout << "\n";
		return;
	}
	if (n==2){
		cout << "NO\n";
		return;
	}
	u=-1, v=-1;
	for (int i=1;i<=n;i++){
		int o = 0, z = 0;
		for (int j=1;j<=n;j++){
			if (i==j) continue;
			if (G[i][j]==0) z++, v = j;
			else o++, w = j;
		}
		if (o&&z){
			u = i;
			cout << "YES\n";
			if (m%4==2){
				cout << v<<" ";
				for (int j=1;j<m;j++){
					if (j&1) cout << u << " ";
					else if (j&2) cout << v << " ";
					else cout << w << " ";
				}	
				cout << w << "\n";
				return;
			}
			else{
				for (int j=0;j<=m;j++){
					if (j%2==0) cout << u << " ";
					else if (j%4==3) cout << w << " ";
					else cout << v << " "; 
				}
				return;
			}
		}
	}
	cout << "NO\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}