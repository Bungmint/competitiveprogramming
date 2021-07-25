// Problem: E. Permutation Shift
// Contest: Codeforces - Harbour.Space Scholarship Contest 2021-2022 (open for everyone, rated, Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1553/problem/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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
int n,m;

void dfs(int v, int &cnt, vi &g, vector<bool> &vis){
	vis[v] = 1;
	cnt++;
	if (!vis[g[v]]) dfs(g[v], cnt, g, vis);
}

int calc(vi &a, vi& perm, vi&pos){
	vi g(n);
	vector<bool> vis(n, false);
	int res = 0;
	for (int i=0;i<n;++i){
		g[pos[perm[i]]] = (i);
	}
	for (int i=0;i<n;++i){
		if (!vis[i]){
			dfs(i, res, g, vis);
			res--;
		}
	}
	dbg(g, perm);
	return res;
}

void solve()
{
	cin >> n >> m;
	vi a(n), cnt(n), pos(n);
	for (int i=0;i<n;++i){
		cin >> a[i];
		a[i]--;
		pos[a[i]] = i;
		cnt[(i-a[i]+n)%n]++;
	}
	vi ans;
	for (int i=0;i<n;++i){
		if (cnt[i]<n/3) continue;
		vi perm(n);
		for (int j=0;j<n;++j){
			perm[j] = (j-i+n)%n;
		}
		int v = calc(a, perm, pos);
		if (v<=m) ans.pb(i);
	}
	cout << sz(ans)<<" ";
	for (int x:ans) cout << x <<  " ";
	cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}