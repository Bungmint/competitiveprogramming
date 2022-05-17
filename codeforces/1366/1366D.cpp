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

const int N = 1e7+100; // Only advised to use it under 1e7 (More Memory)
int lp[N + 1];
vector<int> pr;
void linsieve()
{
    for (int i = 2; i <= N; i++)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
        {
            lp[i * pr[j]] = pr[j];
        }
    }
}

void solve()
{
	int n;
	cin >> n;
	vi a(n);
	for (int i=0;i<n;++i){cin >> a[i];}
	vpi ans(n);
	for (int i=0;i<n;++i){
		if (lp[a[i]] == a[i]){
			ans[i] = {-1, -1};
			continue;
		}
		int x = a[i];
		vi prime, cart;
		while(x>1){
			int p = lp[x];
			int v = 1;
			while(x%p==0){v*=p;x/=p;}
			prime.pb(v);
		}
		if (sz(prime)<=1){
			ans[i] = {-1, -1};
			continue;
		}
		bool ok = 0;
		dbg(prime);
		for (int y:prime){
			int v = sz(cart);
			for (int i=0;i<v;++i){
				cart.pb(y*cart[i]);
			}
			cart.pb(y);	
		}
		for (int y:cart){
			for (int z:cart){
				if (gcd(y+z, a[i])==1){
					ans[i] = {y,z};
					ok = 1;
					break;
				}
			}
			if (ok) break;
		}
		
		
		
		if (ok) continue;
		else ans[i] = {-1,-1};
	}
	for (int i=0;i<n;++i) cout << ans[i].fi<<" ";
	cout << "\n";
	for (int j=0;j<n;++j) cout << ans[j].se << " ";
	cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    linsieve();
    solve();
}