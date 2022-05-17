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

void solve()
{
	int n;
	cin >> n;
	vector<ar<int,3>> v(n);
	vector<ar<int,2>> min_w(n);
	vi ans(n);
	for (int i=0;i<n;i++){
		int h, w;
		cin >> h >> w;
		if (h>w) swap(h, w);
		v[i] = {h, w, i+1};
	}
	sort(all(v), [](ar<int,3> a, ar<int,3> b){
		return a[0] > b[0];
	});
	for (int i=n-1;i>=0;--i){
		if (i==n-1) min_w[i] = {v[i][1], v[i][2]};
		else{
			min_w[i] = min_w[i+1];
			if (min_w[i+1][0]>v[i][1]){
				min_w[i] = {v[i][1], v[i][2]};
			}
		}
	}
	dbg(v, min_w);
	for (int i=0;i<n;++i){
		int curh = v[i][0], w = v[i][1], id = v[i][2];
		int l = i+1, r = n-1, t=-1;
		while(l<=r){
			int m = l + (r-l)/2;
			dbg(curh, v[m][0], m);
			if (v[m][0]<curh){
				r = m-1;
				t = m;
			}else l = m+1;
		}
		dbg(t);
		if (t==-1) ans[id-1] = t;
		else{
			if (min_w[t][0]>= w) ans[id-1] = -1;
			else ans[id-1] = min_w[t][1];
		}
	}
	for (int x:ans) cout << x << " ";
	cout << "\n";
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