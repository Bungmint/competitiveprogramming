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

void solve()
{
	int n, m, q;
	cin >> n >> m >> q;
	vi a(n), b(m);
	for (int &e:a) cin >> e;
	for (int &e:b) cin >> e;
	set<ll> c;
	ll sum = 0;
	for (int i=0;i<n;i++) sum += (i&1? -b[i]:b[i]);
	c.insert(sum);
	for (int i=n;i<m;i++) sum = -sum + b[i-n] +(n&1? b[i]:-b[i]), c.insert(sum);
	dbg(c);
	sum = 0;
	for (int i=0;i<n;i++) sum += (i&1? -a[i]:a[i]);
	dbg(sum);
	auto it = c.lower_bound(sum);
	ll res = LINF;
	if (it!=c.end()){
		res = min(res, llabs(*it-sum));
	}
	if (it!=c.begin()){
		it--;
		res = min(res, llabs(*it-sum));
	}
	cout << res << "\n";
	while(q--){
		ll l, r, x;
		cin >> l >> r >> x;
		if (l%2==r%2){
			sum += (l&1? x:-x);
		}
		auto it = c.lower_bound(sum);
	ll res = LINF;
	if (it!=c.end()){
		res = min(res, llabs(*it-sum));
	}
	if (it!=c.begin()){
		it--;
		res = min(res, llabs(*it-sum));
	}
	cout << res << "\n";
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int testcase=1;
    //cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}