// Problem: R - Walk
// Contest: AtCoder - Educational DP Contest
// URL: https://atcoder.jp/contests/dp/tasks/dp_r
// Memory Limit: 1024 MB
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

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
int n;
void add(ll &a, ll b){a+=b;a%=MOD;}

ll mul(ll a, ll b){
	return (a*b)%MOD;
}

struct Matrix{
	ll x[50][50];
	Matrix(){
		memset(x, 0, sizeof(x));
	}
	Matrix operator*(const Matrix& other){
		Matrix res = Matrix();
		for (int i=0;i<50;++i){
			for (int j=0;j<50;++j){
				for (int k=0;k<50;++k){
					
					add(res.x[i][j], mul(x[i][k], other.x[k][j]));

				}
			}
		}
		return res;
	}
};

ostream& operator<<(ostream& os, Matrix& mat){
	os << "\n";
	for (int i=0;i<n;++i){
		for (int j=0;j<n;++j) os << mat.x[i][j];
		os<<"\n";
	}
	return os;
}

Matrix bin_pow(Matrix a, ll k){
	if (k==1) return a;
	Matrix m = bin_pow(a, k/2);

	return ((k&1)? m*m*a:m*m);
}




void solve()
{
	ll k;
	cin >> n>>k;
	Matrix adj = Matrix();
	for (int i=0;i<n;++i) for (int j=0;j<n;++j)cin >> adj.x[i][j];
	adj = bin_pow(adj, k);
	ll ans = 0;
	for (int i=0;i<n;++i) for (int j=0;j<n;++j) add(ans, adj.x[i][j]);
	cout << ans;
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