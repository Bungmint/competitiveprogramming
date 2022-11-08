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
const int N = 1e5+1;
ll cow[N], rent[N], ppp[N], pref[N], sum[N], milk[N];
pl store[N];

void setIO(string s) { // the argument is the filename without the extension
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}

void solve()
{
	int n, m, R;
	cin >> n>>m >>R;
	for (int i=0;i<n;i++) cin >> cow[i];
	for (int i=0;i<m;i++) cin >> store[i].second >> store[i].first;
	for (int i=0;i<R;i++) cin >> rent[i];
	sort(cow, cow+n, [](ll x, ll y){
		return x>y;
	});
	sort(store, store+m, [](pl p, pl q){
		return p.first > q.first;
	});
	sort(rent, rent+R, [](ll x, ll y){
		return x > y;
	});
	for (int i=0;i<n;i++){
		milk[i] = (i? milk[i-1]+cow[i]:cow[i]);
	}
	for (int i=0;i<m;i++){
		ppp[i] = (i? store[i].second + ppp[i-1]:store[i].second);
		sum[i] = (i? sum[i-1] + store[i].first*store[i].second: store[i].first*store[i].second);
	}
	for (int i=0;i<R;i++){
		pref[i] = (i? pref[i-1] + rent[i]: rent[i]);
	}
	ll ans = pref[min(R-1, n-1)];
	int j = 0;
	for (int i=0;i<n;i++){
		ll cur;
		for (;j<m;j++){
			if (ppp[j]>=milk[i]) break;
		}
		if (j==m){
			cur = sum[m-1];
		}else{
			cur = (j? sum[j-1] + (milk[i]-ppp[j-1])*store[j].first: milk[i]*store[j].first);
		}
		
		
		if (n>=i+2)ans = max(ans, cur + pref[min(R-1, n-i-2)]);
		else ans = max(ans, cur);
	}
	cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    setIO("rental");
    int testcase=1;
    //cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}