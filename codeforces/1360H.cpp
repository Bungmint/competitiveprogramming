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
using vpl = vector<pl>;
using ld = long double;

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
const int MOD = 1e9 + 7; //998244353;

void solve()
{
	ll n, m;
	cin >> n >> m;
	set<ll> st;
	for (int i=0;i<n;++i){
		string s;
		cin >>s;
		reverse(all(s));
		ll cur=0;
		for (int j=0;j<m;++j){
			if (s[j]=='1') cur += (1LL<<j);
		}
		st.insert(cur);
	}
	ll k = (1LL<<m)-n;
	ll targ = (ll)(k-1)/(ll)2 +(ll)1;
	ll ans = 0;
	set<ll> tmp;
	for (int pos=m-1;pos>=0;pos--){
		ll mid = ans + (1LL<<pos);
		dbg(mid);
		ll below =(1LL<<pos);
		dbg(below);
		for (ll x:st){
			if (x<mid) below--;
		}
		dbg(below, targ);
		if (below>=targ){
			for (ll x:st){
				if (x>=mid) tmp.insert(x);
			}
			cout << 0;
		}else{
			targ-=below;
			ans += (1LL<<pos);
			for (ll x:st){
				if (x<mid) tmp.insert(x);
			}
			cout << 1;
		}
		for (ll x:tmp){
			st.erase(x);
		}
	}
	cout <<"\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
	while(t--){
		solve();
	}
}