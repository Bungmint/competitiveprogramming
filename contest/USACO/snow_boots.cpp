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
const int N = 1e5;
ar<int,3> boots[N];
int d[N], ans[N], m1[N], n, b;

void setIO(string s) { // the argument is the filename without the extension
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}



void solve()
{
	cin >> n >> b;
	set<int> index1;
	multiset<int> st;
	for (int i=0;i<n;++i){
		cin >> d[i];
		m1[i] = i;
	}
	sort(m1, m1+n,[&](int x, int y){
		return d[x]<d[y];
	});
	for (int i=0;i<b;i++){
		cin >> boots[i][0]>>boots[i][1];
		boots[i][2] = i;
	}
	if (n==1){
		cout << 1 << "\n";
		return;
	}
	sort(boots, boots+b);
	index1.insert(0);
	index1.insert(n-1);
	st.insert(n-1);
	int j = 0;
	for (int i=0;i<b;i++){
		while(j<n&&d[m1[j]]<=boots[i][0]){
			int id = m1[j];
			if (id==0||id==n-1){
				j++;
				continue;
			}
			auto it = index1.upper_bound(id);
			int a = *prev(it), b = *it;
			st.erase(st.find(b-a));
			st.insert(id-a); st.insert(b-id);
			index1.insert(id);
			j++;
		}
		if (*--st.end()>boots[i][1]) ans[boots[i][2]] = 0;
		else ans[boots[i][2]] = 1;
	}
	for (int i=0;i<b;i++) cout << ans[i] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    setIO("snowboots");
    int testcase = 1;
    //cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}