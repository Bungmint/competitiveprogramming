#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vii = vector<vector<int>>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;
using vll = vector<ll>;

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
	string s;
	cin >> s;
	unordered_set<int, custom_hash> st,st1, st2;
	for (int i=0;i<n;i++){
		st.insert(s[i]-'a'+1);
	}
	for (int i=1;i<=26;i++){
		if (st.count(i)==0){
			string ans = "";
			ans.PB('a'-1+i);
			cout << ans <<"\n";
			return;
		}
	}
	for (int i=0;i<n-1;i++){
		st1.insert(26*(s[i]-'a') + s[i+1]-'a');
	}
	for (int i=0;i<26*26;i++){
		if (st1.count(i)==0){
			string ans = "";
			ans.PB(i%26 + 'a');
			i/=26;
			ans.PB(i%26 + 'a');
			reverse(all(ans));
			cout << ans << "\n";
			return;
		}
	}
	for (int i=0;i<n-2;i++){
		st2.insert(26*26*(s[i]-'a')+ 26*(s[i+1]-'a') + s[i+2]-'a');
	}
	for (int i=0;i<26*26*26;i++){
		if (st2.count(i)==0){
			string ans = "";
			ans.PB(i%26 + 'a');
			i/=26;
			ans.PB(i%26 + 'a');
			i/=26;
			ans.PB(i%26 + 'a');
			reverse(all(ans));
			cout << ans << "\n";
			return;
		}
	}
	
	
	
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