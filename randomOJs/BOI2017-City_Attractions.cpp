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


int a[300001], nxt[2][300001];
pair<int, int> dp[300001], pdp[300001];
vector<int> graph[300001];

void dfs1(int node = 1, int parent = 0) {
	dp[node] = {INT_MAX / 2, 0};
	for (int i : graph[node]) if (i != parent) {
		dfs1(i, node);
		dp[node] = min({dp[node], {dp[i].first + 1, dp[i].second}, {1 - a[i], i}});
	}
}

void dfs2(int node = 1, int parent = 0) {
	dp[node] = min(dp[node], pdp[node]);
	pair<int, int> tmp = {pdp[node].first + 1, pdp[node].second};
	tmp = min(tmp, {1 - a[node], node});
	for (int i : graph[node]) if (i != parent) {
		pdp[i] = min(pdp[i], tmp);
		tmp = min({tmp, {dp[i].first + 2, dp[i].second}, {2 - a[i], i}});
	}
	reverse(graph[node].begin(), graph[node].end());
	tmp = {pdp[node].first + 1, pdp[node].second};
	tmp = min(tmp, {1 - a[node], node});
	for (int i : graph[node]) if (i != parent) {
		pdp[i] = min(pdp[i], tmp);
		tmp = min({tmp, {dp[i].first + 2, dp[i].second}, {2 - a[i], i}});
	}
	for (int i : graph[node]) if (i != parent) dfs2(i, node);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	ll k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		pdp[i] = {INT_MAX / 2, 0};
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	dfs1();
	dfs2();

	for (int i = 1; i <= n; i++) nxt[0][i] = dp[i].second;
	int curr = (k & 1 ? nxt[0][1] : 1);
	for (int i = 1; i < 63; i++) {
		for (int j = 1; j <= n; j++) nxt[i & 1][j] = nxt[i - 1 & 1][nxt[i - 1 & 1][j]];
		if (k & (1ll << i)) curr = nxt[i & 1][curr];
	}
	cout << curr << '\n';
	return 0;
}