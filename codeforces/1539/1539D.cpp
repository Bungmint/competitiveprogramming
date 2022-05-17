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
const int N = 1e5+1;
int n;
multiset<pl> st;

void solve()
{
	cin >> n;
	ll asum = 0;
	for (int i=0;i<n;i++){
		ll a, b;
		cin >> a >>b;
		st.insert({b,a});
		asum += a;
	}
	ll bought = 0;
	ll ones = 0;
	while(!st.empty()){
		dbg(st, ones, bought);
		pl mi = *st.begin();
		if (mi.first<=bought){
			ones+=mi.second;
			bought += mi.second;
			st.erase(st.begin());
		}else{
			ll must = mi.first-bought;
			while(must&&st.size()>=2){
				pl large = *--st.end();
				if (large.second>must){
					bought += must;
					large.second-=must;
					must = 0;
					st.erase(--st.end());
					st.insert(large);
				}else{
					must-=large.second;
					bought += large.second;
					st.erase(--st.end());
				}
			}
			if (must<=mi.second){
				ones+=mi.second-must;
			}
			bought += mi.second;
			st.erase(st.begin());
		}
	}
	
	cout << ones + (asum-ones)*2 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}