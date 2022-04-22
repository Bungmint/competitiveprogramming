#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vpi = vector<pii>;
using vpl = vector<pll>;

#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define pb push_back
#define sz(x) (int)(x).size()


const int INF = 1e9;
const ll LINF = 1e18;


/*
	Cereals that are first choices of some cows (f type) are
	100% selected regardless of the permutation!!
	Now the question is how to increase the consumption of cereals that are
	nobody's first choice (s type).
	
	Cycle detection within a connected component
*/

const pii NT = {-1, -1};
void solve(){
	int n, m;
	cin >> n >> m;
	vpi cow(n);
	vector<vpi> g(m);
	vpi par(m), cycle;
	fill(all(par), NT);
	vi component, cowList;
	vector<bool> isF(m, 0), vis(m, 0), covered(m, 0), used(n, 0);
	for (int i=0;i<n;++i) {
		cin >> cow[i].fi >> cow[i].se, cow[i].fi--, cow[i].se--;
		isF[cow[i].fi] = 1;
	}
	for (int i=0;i<n;++i){
		g[cow[i].fi].pb({cow[i].se, i}), g[cow[i].se].pb({cow[i].fi, i});
	}
	function<bool(int)> dfs = [&](int u)->bool{
		vis[u] = 1;
		bool res = 0;
		component.pb(u);
		for (auto &[v, id]: g[u]){
			if (!vis[v]){
				par[v] = {u, id};
				res|= dfs(v);
			}else if (vis[v]&&!sz(cycle)&&!res&&par[u]!=make_pair(v,id)){
				// cerr << 1;
				res = 1;
				int cur = u;
				while(true){
					cycle.pb({cur, par[cur].se});
					if (cur==v) {cycle.back().se= id;break;}
					cur = par[cur].fi;
				}
			}
		}
		return res;
	};
	int eaten = 0;
	for (int i=0;i<m;++i){
		if (!vis[i]){
			cycle.clear(), component.clear();
			if (dfs(i)){
				int st = 0;
				queue<int> q;
				for (int j=0;j<sz(cycle);++j){
					auto &[en, id] = cycle[j];
					covered[en] = 1;
					q.push(en);
					used[id] = 1;
					if((cow[id].se==cow[cycle[(j+1)%sz(cycle)].se].se)){
						st = (j+1)%sz(cycle);
					}
				}
				for (int j=0;j<sz(cycle);++j){
					int id = cycle[(j+st)%sz(cycle)].se;
					cowList.pb(id);
				}
				while(sz(q)){
					int u = q.front(); q.pop();
					for (auto &[v, id]:g[u]){
						if (used[id]) continue;
						q.push(v);
						covered[v] = 1;
						used[id] = 1;
						cowList.pb(id);
					}
				}
				eaten += sz(component);
			}else if(sz(component)>=2){
				queue<int>q;
				int st = component[0];
				for(auto &e:component){
					if (sz(g[e])==1) st = e;
				}
				q.push(st);
				covered[st] = 1;
				while(sz(q)){
					int u = q.front(); q.pop();
					for (auto &[v, id]:g[u]){
						if (used[id]) continue;
						q.push(v);
						covered[v] = 1;
						assert(covered[u]);
						used[id] = 1;
						cowList.pb(id);
					}
				}
				eaten += sz(component)-1;
			}
		}
	}
	cout << n-eaten << "\n";
	for (auto moo:cowList) cout << moo+1 << "\n";	
}

int main(){
	cin.tie(0)->sync_with_stdio(0);
	solve();
	return 0;
}