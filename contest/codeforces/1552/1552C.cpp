// Problem: C. Maximize the Intersections
// Contest: Codeforces - Codeforces Global Round 15
// URL: https://codeforces.com/contest/1552/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

bool ok(int x, int y, int a){
	return (x<a&&a<y);
}

void solve()
{
	int n,k;
	cin >> n >> k;
	vector<pi> chords;
	vector<bool> used(2*n,false);
	int ans =0;
	for (int i=0;i<k;++i){
		pi p;
		cin >> p.fi >> p.se;
		p.fi--, p.se--;
		used[p.fi] = 1;
		used[p.se] = 1;
		if (p.fi > p.se) swap(p.fi, p.se);
		for (auto q:chords){
			if (ok(p.fi, p.se, q.fi)&&!ok(p.fi,p.se,q.se))ans++;
			else if (ok(p.fi,p.se, q.se)&&!ok(p.fi, p.se, q.fi)) ans++;
		}
		chords.pb(p);
		dbg(ans);
	}
	dbg(ans);
	for (int i=0;i<2*n;++i){
		if (!used[i]){
			int mx = -1;
			int id =0;
			for (int j=i+1;j<2*n;++j){
				if(!used[j]){
					int emptyL = 0, emptyR = 0;
					for (int k=0;k<2*n;++k){
						if (k==i||k==j) continue;
						if (!used[k]&&ok(i, j, k)) emptyL++;
						else if (!used[k]&&!ok(i,j,k)) emptyR++;
					}
	
					if (emptyR*emptyL>mx){
						id = j;
						mx = emptyR*emptyL;
					}
				}
			}
			used[i] = used[id] = 1;
			dbg(i,id);
			for (auto p:chords){
				if (ok(i, id, p.fi)&&!ok(i,id, p.se)) ans++;
				else if (ok(i, id, p.se)&&!ok(i, id, p.fi))ans++;
			}
			chords.pb({i, id});
		}
	}
	cout << ans << "\n";
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