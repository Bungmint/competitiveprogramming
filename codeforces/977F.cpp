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

void solve()
{
	set<pi> st;
	int n;
	cin >> n;
	vi v(n);
	int mx = 0, fv = 0;
	for (int i=0;i<n;i++){
		int t;
		cin >> t;
		v[i] = t;
		auto it2 = st.lower_bound({t-1, -INF});
		if (it2==st.end()||it2->first!=t-1){
			auto it1 = st.lower_bound({t, -INF});
			if (it1==st.end()||it1->first!=t){
				st.insert({t,1});
				if (!mx) fv = t, mx = 1;
			}
		}else{
			int cnt = it2->second +1;
			auto it1 = st.lower_bound({t,-INF});
			if (it1==st.end()||it1->first!=t){
				st.insert({t, cnt});
				if(mx<cnt) mx = cnt, fv = t;
			}else{
				if (it1->second<cnt){
					st.erase(it1);
					st.insert({t,cnt});
					if(mx<cnt) mx = cnt, fv = t;
				}
			}
		}
	}
	int start=fv-mx+1;
	cout << mx << "\n";
	for (int i=0;i<n;i++){
		if (v[i]==start) start++, cout << i+1 << " ";
	}
	cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}