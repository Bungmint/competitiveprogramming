#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
typedef vector<int> vi;
typedef pair<int, int> pi;

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
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

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353

void solve()
{
	int n,k,p;
	cin >> n >>k >>p;
	vi v(n);
	int odd =0, even = 0;
	for (int i=0;i<n;i++){
		cin >>v[i];
		if (v[i]%2) odd++;
		else even++;
	}	
	if (odd<k-p){
		cout << "NO\n";
		return;
	}
	odd-=(k-p);
	if (odd%2){
		cout << "NO\n";
		return;
	}
	if (even+odd/2<p){
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	vector<vi> ans(k);
	vi o, e;
	for (int i=0;i<n;i++){
		if (v[i]%2) o.PB(v[i]);
		else e.PB(v[i]);
	}
	for (int i=0;i<k-p;i++){
		ans[k-1-i].PB(o[i]);
	}
	int cnt = p-1;
	for (int i=k-p;i<(int)o.size();i++){
		if (cnt<0){ans[0].PB(o[i]);continue;}
		ans[cnt].PB(o[i]);
		if ((i-k+p)%2){
			cnt--;
		}
	}
	for (int i=0;i<(int)e.size();i++){
		if (i<p) ans[i].PB(e[i]);
		else ans[0].PB(e[i]);
	}
	for (auto x:ans){
		cout << (int)x.size()<<" ";
		for (auto y:x) cout << y << " ";
		cout << "\n";
	}
	
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}