// Problem: D1. Gregor and the Odd Cows (Easy)
// Contest: Codeforces - Codeforces Round #736 (Div. 1)
// URL: https://codeforces.com/contest/1548/problem/D1
// Memory Limit: 256 MB
// Time Limit: 6000 ms
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

struct Point{
	int x, y;
};

bool good(Point& p, Point &q, int x, int y){
	int g1 = (p.x==q.x&&p.y==q.y? 0:2);
	int g2 = (p.x==x&&p.y==y? 0:2);
	int g3 = (q.x==x&&q.y==y? 0:2);
	return (g1+g2+g3)%4==0;
}

void solve()
{
	int n;
	cin >> n;
	vector<Point> a(n);
	vector<vi> cnt(4, vi(4));
	for (int i=0;i<n;++i){
		cin >> a[i].x >> a[i].y;
		a[i].x%=4, a[i].y%=4;
		cnt[a[i].x][a[i].y]++;
	}
	ll ans = 0;
	for (int i=0;i<n;++i) for (int j=i+1;j<n;++j){
		Point p = a[i], q = a[j];
		cnt[p.x][p.y]--, cnt[q.x][q.y]--;
		for (int k=0;k<4;++k){
			if (k&1) continue;
			for (int m=0;m<4;m++){
				if (m&1) continue;
				if (good(p,q,k, m)) ans += cnt[k][m]; 
			}
		}
		cnt[p.x][p.y]++, cnt[q.x][q.y]++;
	}
	cout << ans/3 << endl;
	
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