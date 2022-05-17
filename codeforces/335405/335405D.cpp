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
int cnt[26];

bool good(){
	for (int i=0;i<26;++i) if (cnt[i]>1) return 0;
	return 1;
}

void solve()
{
	string s;
	cin >> s;
	int n = sz(s);
	if (n<26){
		cout << -1 <<"\n";
		return;
	}
	for (int i=0;i<26;++i){
		if (s[i]!='?'){
			cnt[s[i]-'A']++;
		}
	}
	int r = 26;
	if (good()){
		for (int l=0;l<=25;++l){
			if (s[l]=='?'){
				for (int j=0;j<26;++j){
					if (!cnt[j]){
						s[l] = 'A'+j;
						cnt[j]=1;
						break;
					}
				}
			}
		}
		for (int i=0;i<n;++i){
			if (s[i]=='?') s[i] = 'A';
		}
		cout << s << "\n";
		return;
	}
	for (;r<n;++r){
		if (s[r]!='?'){
			cnt[s[r]-'A']++;
		}
		if (s[r-26]!='?'){
			cnt[s[r-26]-'A']--;
		}
		if (good()){
			for (int l=r-25;l<=r;++l){
				if (s[l]=='?'){
					for (int j=0;j<26;++j){
						if (!cnt[j]){
							s[l] = 'A'+j;
							cnt[j]=1;
							break;
						}
					}
				}
			}
			for (int i=0;i<n;++i){
				if (s[i]=='?') s[i] = 'A';
			}
			cout << s << "\n";
			return;
		}
	}
	
	cout << -1 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}