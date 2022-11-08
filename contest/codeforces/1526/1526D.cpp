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
unordered_map<char,int> m = {{'A',0}, {'N',1}, {'T', 2}, {'O', 3}};
unordered_map<int,char> rev = {{0, 'A'}, {1,'N'}, {2, 'T'}, {3, 'O'}};
int BIT[100001], n;

void upd(int i, int v){
	i++;
	for (;i<=n;i+=i&-i){
		BIT[i]+=v;
	}
}
int query(int i){
	int ans = 0;
	++i;
	for (;i>0;i-=i&-i){
		ans += BIT[i];
	}
	return ans;
}

void solve()
{
	string s;
	cin >> s;
	n = sz(s);
	vi cnt(4);
	for (int i=0;i<n;++i){
		cnt[m[s[i]]]++;
	}
	vi perm = {0,1,2,3}, res;
	ll ans = -1;
	for (int i=0;i<24;++i){
		for (int i=0;i<=n;++i) BIT[i] = 0;
		ll val = 0;
		vi track(4);
		for (int j=1;j<4;++j){
			track[perm[j]] = track[perm[j-1]]+cnt[perm[j-1]];
		}
		for (int j=0;j<n;++j){
			int cur = track[m[s[j]]];
			val += query(n-1)-query(cur);
			upd(cur, 1);
			track[m[s[j]]]++;
		}
		if (ans<val){
			res = perm;
			ans = val;
		}
		next_permutation(all(perm));
	}
	dbg(perm);
	for (int i=0;i<4;++i){
		for (int j=0;j<cnt[res[i]];++j ){
			cout << rev[res[i]];
		}
	}
	cout << "\n";
}

int main()
{
	memset(BIT, 0,sizeof(BIT));
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}