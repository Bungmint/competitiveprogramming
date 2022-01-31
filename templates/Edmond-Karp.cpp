const int MX = 1000; //change this
template<typename T, int N>
struct EdmondKarp{
	T cap[N][N];
	vi g[N];
	
	T bfs(int s, int t, vi &p){
		fill(all(p), -1);
		p[s]=-2;
		queue<pair<T,T>> q;
		q.push({s, LINF});
		while(sz(q)){
			auto [cur, flow] = q.front();
			q.pop();
			for (int e:g[cur]){
				if (p[e]==-1&&cap[cur][e]){
					p[e] = cur;
					T newflow = min(flow, cap[cur][e]);
					if (e==t){
						return newflow;
					}
					q.push({e, newflow});
				}
			}
		}
		return 0;
	}
	T maxFlow(int s, int t){
		T flow = 0;
		vi p(N+1);
		T newflow = 0;
		while((newflow=bfs(s,t,p))){
			flow += newflow;
			int cur = t;
			while(cur!=s){
				int prev = p[cur];
				cap[prev][cur]-=newflow;
				cap[cur][prev] += newflow;
				cur = prev;
			}
		}
		return flow;
	}
	void dfs(int v, vector<bool>& vis, vi &ans){
		vis[v] = 1;
		ans.pb(v);
		for (int e:g[v]){
			if (cap[v][e]&&!vis[e]) dfs(e, vis,ans);
		}
	}
	pair<T,vi> minCut(int s,int t){
		T x = maxFlow(s,t);
		vi ans;
		vector<bool> vis(N, false);
		dfs(s, vis, ans);
		return {x, ans};
	}
};