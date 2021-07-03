#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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
	string s;
	cin >> s;
	vector<int> ones;
	for (int i=0;i<n;i++){
		if (s[i] == '1') ones.PB(i);
	}
	if (!sz(ones)){
		cout << s << "\n";
		return;
	}
	if (sz(ones)==1){
		for (int i=max(0, ones[0]-m);i<=min(n-1, ones[0]+m);i++) s[i] = '1';
		cout << s<< "\n";
		return;
	}
	for (int j = ones[0]-1;j>=max(0,ones[0]-m);j--) s[j]='1';
	for (int i=1;i<sz(ones);i++){
		int pr = ones[i-1], cur = ones[i];
		if (cur-pr<=2) continue;
		if ((cur-pr)%2){
			for (int j=pr+1;j<=min(pr+m, cur);j++) s[j] = '1';
			for (int j=cur-1;j>=max(pr,cur-m);j--) s[j] = '1';
		}else{
			for (int j=pr+1;j<=min(pr+m, pr + (cur-pr)/2 -1);j++) s[j]='1';
			for (int j=cur-1;j>=max(pr + (cur-pr)/2 + 1, cur-m);j--) s[j]='1';
		}
	}
	for (int j=ones[sz(ones)-1]+1;j<=min(n-1, ones[sz(ones)-1]+m);j++) s[j]='1';
	cout << s << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}