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
const int N = 3e5, LOG = 30;
int a[N];
int trie[6000000][2];
vi S[6000000];
ll dp[2][30];
const int root = 1;
int cur = 1;

void insert(int idx){
	int now = root;
	int x = a[idx];
	for (int i=29;i>=0;i--){
		int c = ((x>>i)&1);
		if (trie[now][c]==0){
			trie[now][c] = ++cur;
		}
		now = trie[now][c];
		S[now].pb(idx);
		dbg(now, S[now]);
	}
}

void go(int v, int pos = 29){
	int l = trie[v][0], r = trie[v][1];
	if (l) go(l, pos-1);
	if (r) go(r, pos-1);
	if (l==0||r==0) return;
	ll res = 0;
	int ptr = 0;
	for (int x:S[l]){
		while(ptr<sz(S[r])&&S[r][ptr]<x){
			ptr++;
		}
		res+=ptr;
	}
	dp[0][pos] += res;
	dp[1][pos] += sz(S[l])*1LL*sz(S[r]) - res;
}

void solve()
{
	int n;
	cin >> n;
	for (int i=0;i<n;++i){
		cin >> a[i];
		insert(i);
	}
	go(root);
	int ans = 0;
	ll res = 0;
	for (int i=29;i>=0;i--){
		if (!dp[0][i]) continue;
		if (dp[0][i]>dp[1][i]){
			ans^=(1<<i);
			res += dp[1][i];
		}else{
			res += dp[0][i];
		}
	}
	cout << res << " "<< ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}