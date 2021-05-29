#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
#define sz(x) (int)x.size()
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
const int N = 1e5;
int v[N];

void solve()
{
	int n;
	cin >> n;
	for (int i=0;i<n;i++) cin >> v[i];
	sort(v,v+n);
	if (n==1){
		cout << -1 << "\n";
		return;
	}
	if (n==2){
		if (v[0]!=v[1]){
			int d = v[1]-v[0];
			if (d%2){
				cout << 2 << "\n";
				cout << v[0]-d << " "<< v[1]+d << "\n";
				
			}else{
				cout << 3 << "\n";
				cout << v[0]-d << " "<< v[0]+d/2 << " "<<v[1]+d << "\n";
			}
		}else{
			cout << 1 << "\n";
			cout << v[0]<<"\n";
		}
		return;
	}
	unordered_map<int,int,custom_hash> s1;
	for (int i=1;i<n;i++){
		s1[v[i]-v[i-1]]++;
	}
	int s = sz(s1);
	if(s==1){
		int d = s1.begin()->first;
		if (d==0){
			cout << 1 << "\n";
			cout << v[0]<<"\n";
			return;
		}
		cout << 2 << "\n";
		cout << v[0]-d<< " "<< v[n-1] + d << "\n";
	}else if(s==2){
		auto it = s1.begin();
		int d1 = it->first, n1 = it->second;
		it++;
		int d2 = it->first, n2 = it->second;
		if ((n1!=1&&n2!=1)||(d1!=2*d2&&d2!=2*d1)||(n1>=2&&d1>d2)||(n2>=2&&d2>d1)){
			cout << 0 << "\n";
			return;
		}
		cout << 1 << "\n";
		if (d1>d2){
			for (int i=1;i<n;i++){
				if (v[i]-v[i-1]==d1){
					cout << v[i-1] + d2 << "\n";
					return;
				}
			}
		}
		for (int i=1;i<n;i++){
				if (v[i]-v[i-1]==d2){
					cout << v[i-1] + d1 << "\n";
					return;
				}
			}
	}else{
		cout << 0 << "\n";
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t=1;
    while (t--)
    {
        solve();
    }
}