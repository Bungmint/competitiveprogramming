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
const int MOD = 1e9 + 7; //998244353
const int N = 1e5+1;
ar<int,3> cow[N];

void setIO(string s) { // the argument is the filename without the extension
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}

void solve()
{
	int n;
	cin >> n;
	for (int i=0;i<n;++i){
		int a, t;
		cin >> a >> t;
		cow[i] = {a, i, t};
	}
	sort(cow,cow+n);
	int finish = 0;
	int ans = 0;
	set<ar<int,3>> st;
	int i = 0;
	while(i<n){
		int a = cow[i][0], num = cow[i][1], t = cow[i][2];
		if (finish>a) ans = max(ans, finish-a);
		while(i+1<n&&cow[i+1][0]<=max(a,finish)+t){
			st.insert({cow[i+1][1], cow[i+1][0], cow[i+1][2]});
			i++;
		}
		finish = max(finish, a) + t;
		while(!st.empty()){
			ar<int,3> cur = *st.begin();
			st.erase(cur);
			int a1 = cur[1], num1 = cur[0], t1 = cur[2];
			if (finish>a1) ans = max(ans, finish-a1);
			while(i+1<n&&cow[i+1][0]<=max(a1,finish)+t1){
				st.insert({cow[i+1][1], cow[i+1][0], cow[i+1][2]});
				i++;
			}
			finish = max(finish, a1) + t1;
		}
		++i;
	}
	cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    setIO("convention2");
    solve();
}