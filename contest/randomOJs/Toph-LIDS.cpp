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
vector<int> v;
ll cache[11][11][2][2][11], cnt[11];

ll dp(int pos, int last, bool mask, bool nonzr, int need){
	if (pos==sz(v)) return need == 0;
	if (cache[pos][last+1][mask][nonzr][need]!=-1) return cache[pos][last+1][mask][nonzr][need];
	int DMT = (mask? 9:v[pos]);
	ll res = 0LL;
	for (int i=0;i<=DMT;++i){
		int newmask = mask;
		
		if (mask==0&&i<DMT) newmask = 1;
		res += dp(pos+1, last, newmask, nonzr||i, need);
		if (i>last&&need&&(nonzr||i))
			res += dp(pos+1, i, newmask, 1, need-1);
	}
	return cache[pos][last+1][mask][nonzr][need] = res;
}


inline void reset(){
	v.clear();
	memset(cache,-1,sizeof(cache));
}

void solve(int t)
{
	memset(cnt, 0, sizeof(cnt));
	int x,y;
	cin >> x >> y;
	reset();
	while(y){
		v.PB(y%10);
		y/=10;
	}
	reverse(all(v));
	for (int i=1;i<10;i++){cnt[i] += dp(0,-1,0,0,i);}
	reset();
	x--;
	while(x){
		v.PB(x%10);
		x/=10;
	}
	reverse(all(v));
	for (int i=1;i<10;i++) {cnt[i] -= dp(0,-1,0,0,i);}
	pair<int,ll> ans = {0,1};
	for (int i=9;i>=1;i--){
		if (cnt[i]) {ans = {i, cnt[i]};break;}
	}
	cout << "Case "<< t << ": " << ans.first << " "<< ans.second << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    for (int i=1;i<=t;i++)
    {
        solve(i);
    }
}