#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pi = pair<int,int>;
using ll = long long;
using vpi = vector<pi>;
using pl = pair<ll,ll>;
using vpl = vector<pl>;

#define all(v) (v).begin(), (v).end()
#define sz(x) (int)(x).size();
#define ar array
#define pb push_back
#define fi first
#define se second
#define lb lower_bound
#define dbg(x) cerr << #x << ": "<< x<<"\n"

const int N = 1e5+10, LOG = 20;
vi G[N];
int t[N], timer = 0, st[N], en[N], n, m, a[2*N], ID[2*N];
vpi query[2*N];
bool vis[N];
int cowCnt[N], up[N][LOG], depth[N];

void setIO(string s){
	freopen((s+".in").c_str(), "r", stdin);
	freopen((s+".out").c_str(),"w", stdout);
}

void dfs(int V, int pV){
	st[V] = timer++;
	a[st[V]] = V;
	ID[st[V]] = V;
	for (int e:G[V]){
		if (e!=pV){
			depth[e] = depth[V]+1;
			up[e][0] = V;
			for (int i=1;i<LOG;i++) up[e][i] = up[up[e][i-1]][i-1];
			dfs(e,V);
		}
	}
	en[V] = timer++;
	a[en[V]] = V;
	ID[en[V]] = V;
}

int lca(int a, int b){
	if (depth[a]<depth[b]) swap(a,b);
	int d = depth[a]-depth[b];
	for (int i=LOG-1;i>=0;i--) if (d&(1<<i)) a = up[a][i];
	if (a==b) return a;
	for (int i=LOG-1;i>=0;i--) if (up[a][i]!=up[b][i]) a = up[a][i], b = up[b][i];
	return up[a][0];
}

void check(int x){
	if (vis[a[x]]) cowCnt[t[a[x]]]--;
	else cowCnt[t[a[x]]]++;
	vis[a[x]]^=1;
}
int get_answer(int cow){
	return !!(cowCnt[cow]);
}
const int block=320; //Dont forget to set

struct Query {
    int l, r, idx, cow, lc;
	inline pair<int, int> toPair() const {
		return make_pair(l / block, ((l / block) & 1) ? -r : +r);
	}
};
inline bool operator<(const Query &a, const Query &b) {
	return a.toPair() < b.toPair();
}

using vq = vector<Query>;


vi mo(vq queries) {
   	vi answers(queries.size());
    sort(queries.begin(), queries.end());

    int cur_l = 0;
    int cur_r = -1;
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            check(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            check(cur_r);
        }
        while (cur_l < q.l) {
            check(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            check(cur_r);
            cur_r--;
        }
        answers[q.idx] =(q.lc!=ID[q.l]&&q.lc!=ID[q.r]? (get_answer(q.cow)||t[q.lc]==q.cow) : get_answer(q.cow));
    }
    return answers;
}



int main(){
	cin.tie(0)->sync_with_stdio(0);
	setIO("milkvisits");
	cin >> n >> m;
	for (int i=1;i<=n;++i){
		cin >>t[i];
	}
	for (int i=0;i<n-1;++i){
		int u,v;
		cin >> u >> v;
		G[u].pb(v);
		G[v].pb(u);
	}
	dfs(1,0);
	vq Q(m);
	for (int i=0;i<m;++i){
		int u,v, C;
		cin >> u >> v>>C;
		int x = lca(u,v);
		if (st[u]>st[v]) swap(u,v);
		if (en[u]>=en[v]){
			Q[i] = {st[u], st[v], i,C,x};
		}else{
			Q[i] = {en[u], st[v], i,C, x};
		} 
	}
	vi ans = mo(Q);
	for (int x:ans) cout << x;
	cout << endl;
}


