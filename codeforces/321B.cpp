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
	int n, m;
	cin >> n >> m;
	vi me(m);
	multiset<int> att, def, att1, def1;
	for (int i=0;i<n;i++){
		string s;
		int t;
		cin >> s>>t;
		if (s=="ATK") att.insert(t);
		else def.insert(t);
	}
	for (int i=0;i<m;i++) cin >> me[i];
	sort(all(me));
	def1 = def, att1 = att;
	for (int i=0;i<m;i++){
		if (!def1.empty()&&*def1.begin()<me[i]){
			def1.erase(def1.begin());
			continue;
		}
		if (!att1.empty()&&*att1.begin()<=me[i]){
			att1.erase(att1.begin());
		}
	}
	if (sz(att1)||sz(def1)){
		int ans = 0LL;
		for (int i=1;i<=m;i++){
			att1 = att;
			int cur = 0;
			bool ok = 1;
			for (int j=0;j<i;j++){
				if (att1.empty()||*att1.begin()>me[m-i+j]){ok=0; break;}
				cur += me[m-i+j]-*att1.begin();
				att1.erase(att1.begin());
			}
			if (!ok) break;
			ans = max(ans, cur);
		}
		
		
		cout << ans << "\n";
		return;
	}
	
	
	
	int saved = 0;
	int ans =0;
	for (int i=1;i<=m;i++){
		att1 = att;
		int cur = 0;
		bool ok = 1;
		
		for (int j=0;j<i;j++){
			dbg(att1, me, ans);
			if (att1.empty()||*att1.begin()>me[m-i+j]){ok=0; break;}
			cur += me[m-i+j]-*att1.begin();
			att1.erase(att1.begin());
		}
		if (!ok) break;
		ans = max(ans, cur);
	}
	dbg(ans);
	int cur = 0;
	for (int i=0;i<m;i++){
		dbg(def, att);
		if (!def.empty()&&*def.begin()<me[i]){
			def.erase(def.begin());
		}
		else if (!att.empty()&&*att.begin()<=me[i]){
			cur += me[i]-*att.begin();
			att.erase(att.begin());
		}else{
			saved+=me[i];
		}
	}
	cout << max(cur + saved, ans) << "\n";
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