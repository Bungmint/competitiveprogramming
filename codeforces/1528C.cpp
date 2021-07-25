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
const int N = 3e5+1;
vi G1[N], G2[N];
set<pi> s;
int st[N], en[N];
int ans = 0, timer = 0;

void dfsG1(int V,int pV){
	int u=-1;
	if (s.empty()){
		s.insert({st[V], V});
	}else{
		auto it1 = s.lb({st[V], -INF});
		bool ok = 1;
		if (it1!=s.end()){
			int u = it1->se;
			if (en[u]<=en[V]) ok = 0;
		}
		if (ok){
			auto it2 = s.lb({st[V], -INF});
			if (it2!=s.begin()){
				it2--;
				u = it2->se;
				if (en[u]>=en[V]){
					s.erase(it2);
				}
			}
			s.insert({st[V], V});
		}
	}
	ans = max(ans, sz(s));
	for (int e:G1[V]){
		if (e!=pV){
			dfsG1(e,V);
		}
	}
	
	if (s.count({st[V], V})) s.erase({st[V], V});
	if (u!=-1) s.insert({st[u], u});
}

void dfsG2(int V,int pV){
	st[V] = timer++;
	for (int e:G2[V]){
		if (e!=pV){
			dfsG2(e,V);
		}
	}
	en[V] = timer;
}


void solve()
{
	int n;
	cin >>n;
	for (int i=0;i<=n;++i) G1[i].clear(), G2[i].clear();
	for (int i=2;i<=n;++i){
		int t;
		cin >> t;
		G1[t].pb(i); G1[i].pb(t);
	}
	for (int i=2;i<=n;++i){
		int t;
		cin >> t;
		G2[t].pb(i); G2[i].pb(t);
	}
	timer = 0;
	ans = 0;
	dfsG2(1,0);
	dfsG1(1,0);
	cout << ans << "\n";
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