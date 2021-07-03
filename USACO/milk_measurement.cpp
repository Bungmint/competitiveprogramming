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
ar<int,3> days[100000];

void setIO(string s) { // the argument is the filename without the extension
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}

void solve()
{
	int n, g;
	cin >> n >> g;
	map<int,int> m1;
	unordered_map<int,int,custom_hash> cow;
	m1[g] = INF;
	int mx = g, cnt = INF;
	
	for (int i=0;i<n;i++) cin >> days[i][0] >> days[i][1] >> days[i][2];
	sort(days, days+n);
	int ans = 0LL;
	for (int i=0;i<n;i++){
		int last = -1, nxt = -2*INF;
		bool is_mx = false, same = true;
		int change = 0;
		for (int j = i;j<n&&days[j][0]==days[i][0];++j){
			if (!cow.count(days[j][1])){
				m1[g]--;
				if (m1[g]==0) m1.erase(g);
				cow[days[j][1]] = g+days[j][2];
			}else{
				m1[cow[days[j][1]]]--;
				if (!m1[cow[days[j][1]]]) m1.erase(cow[days[j][1]]);
				if (cow[days[j][1]]==mx&&nxt==-2*INF) is_mx = 1, nxt = days[j][2], change++;
				else if (cow[days[j][1]]==mx) is_mx = 1, same &= (nxt==days[j][2]), change++;
				cow[days[j][1]] +=days[j][2];
			}
			m1[cow[days[j][1]]]++;
			last = j;
		}
		
		pi p = *--m1.end();
		
		if (p.second!=cnt){
			ans++;
		}else if (!is_mx&&p.first!=mx){
			ans++;
		}else if (is_mx){
			if (change!=cnt||!same||mx+nxt!=p.first) ans++;
		}
		i = last;
		mx = p.first, cnt = p.second;
	}
	cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    setIO("measurement");
    int testcase=1;
    //cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}