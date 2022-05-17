#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back

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

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353
ll G[501][501], n, v[501], ans[501];

void solve()
{
	cin >> n;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			cin >> G[i][j];
	for (int i=0;i<n;i++) cin >> v[i],v[i]--;
	unordered_set<int, custom_hash> s1;
	for (int i=n-1;i>=0;i--){
		s1.insert(v[i]);
		for (int j=0;j<n;j++)
			for (int k=0;k<n;k++)
				G[j][k] = min(G[j][k], G[j][v[i]]+G[v[i]][k]);
		for (auto &j:s1){
			for (auto &k:s1){
				ans[i]+=G[j][k];
				dbg(v[i], j, k, G[j][k]);
			}
		}
	}
	for (int i=0;i<n;i++) cout << ans[i] << " ";
	cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t=1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
}