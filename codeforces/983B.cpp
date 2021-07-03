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
const int N = 5001;
int cache1[N][N], cache2[N][N], v[N];

pi dp(int i, int j){
	if (i==j) return {v[i], v[i]};
	if (cache1[i][j]!= -1) return {cache1[i][j], cache2[i][j]};
	pi p1 = dp(i+1, j), p2 = dp(i, j-1);
	cache1[i][j] = p1.first^p2.first;
	cache2[i][j] = max(cache1[i][j], max(p1.second, p2.second));
	return {cache1[i][j], cache2[i][j]};
}

void solve()
{
	int n,q;
	cin >>n;
	for (int i=0;i<n;i++) cin >> v[i];
	memset(cache1, -1, sizeof(cache1));
	memset(cache2, -2, sizeof(cache2));
	for (int i=0;i<n;i++) for (int j=i;j<n;j++)
		dp(i, j);
	cin >> q;
	while(q--){
		int l, r;
		cin >> l >> r;
		l--;r--;
		cout << dp(l,r).second<<"\n";
	}
}

void solve1(){
	int n,q;
	cin >> n;
	for (int i=0;i<n;i++) cin >> v[i];
	for (int d=0;d<n;d++) for (int i=0;i+d<n;i++){
		cache1[i][i+d] = (d==0? v[i]:cache1[i+1][i+d]^cache1[i][i+d-1]);
		cache2[i][i+d] = (d==0? cache1[i][i+d]: max(cache1[i][i+d], max(cache2[i][i+d-1], cache2[i+1][i+d])));
	}
	cin >> q;
	while(q--){
		int l,r;
		cin >> l >> r;
		l--;r--;
		cout << cache2[l][r]<<"\n";
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    bool which = rng()%2;
    (which ? solve():solve1());
}