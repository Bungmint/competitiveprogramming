// Problem: D. Say No to Palindromes
// Contest: Codeforces - Educational Codeforces Round 112 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1555/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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
#define ub upper_bound

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

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

struct chash
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

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

int pref[3][3][200101];

void solve()
{
	int n, m;
	cin >> n >> m;
	string s;
	cin >> s;
	for (int i=1;i<=n;++i){
		for(int j=0;j<3;++j) for (int k=0;k<3;++k) pref[j][k][i] = pref[j][k][i-1];
		pref[s[i-1]-'a'][i%3][i]++;
	}
	for (int i=0;i<m;++i){
		int l, r;
		cin >> l >> r;
		int x = l%3, y = (l+1)%3, z = (l+2)%3;
		int res = INF;
		// 6 possibilities
		// a, b, c
		int k = pref[0][x][r]-pref[0][x][l-1] + pref[1][y][r]-pref[1][y][l-1] + pref[2][z][r]-pref[2][z][l-1]; 
		res = min(res, r-l+1-k);
		k = pref[0][x][r]-pref[0][x][l-1] + pref[2][y][r]-pref[2][y][l-1] + pref[1][z][r]-pref[1][z][l-1]; 
		res = min(res, r-l+1-k);
		k = pref[1][x][r]-pref[1][x][l-1] + pref[0][y][r]-pref[0][y][l-1] + pref[2][z][r]-pref[2][z][l-1]; 
		res = min(res, r-l+1-k);
		k = pref[1][x][r]-pref[1][x][l-1] + pref[2][y][r]-pref[2][y][l-1] + pref[0][z][r]-pref[0][z][l-1]; 
		res = min(res, r-l+1-k);
		k = pref[2][x][r]-pref[2][x][l-1] + pref[0][y][r]-pref[0][y][l-1] + pref[1][z][r]-pref[1][z][l-1]; 
		res = min(res, r-l+1-k);
		k = pref[2][x][r]-pref[2][x][l-1] + pref[1][y][r]-pref[1][y][l-1] + pref[0][z][r]-pref[0][z][l-1]; 
		res = min(res, r-l+1-k);
		cout << res << "\n";
	}
	
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}