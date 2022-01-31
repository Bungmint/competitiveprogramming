struct SuffixArray{
	vi p, c, c_new, p_new, cnt, pos, lcp;
	int n;
	vector<pair<char,int>> a;
	
	void count_sort(){
		for (int i=0;i<n;++i) cnt[i] = 0;
		for (int i=0;i<n;++i){
			cnt[c[i]]++;
		}
		pos[0] = 0;
		for (int i=1;i<n;++i) pos[i] = pos[i-1]+cnt[i-1];
		for (int i=0;i<n;++i){
			int x = c[p[i]];
			p_new[pos[x]] = p[i];
			pos[x]++;
		}
		for (int i=0;i<n;++i) p[i] = p_new[i];
	}
	
	SuffixArray(string &s)
	{
		s+='$';
		n = sz(s);
		p.resize(n), c.resize(n), c_new.resize(n);
		p_new.resize(n), cnt.resize(n), pos.resize(n);
		lcp.resize(n), a.resize(n);
		for (int i=0;i<n;++i) a[i] = {s[i], i};
		sort(a.begin(), a.begin()+n);
		for (int i=0;i<n;++i) p[i] = a[i].second;
		c[p[0]] = 0;
		for (int i=1;i<n;++i){
			if (a[i].first==a[i-1].first){
				c[p[i]] = c[p[i-1]];
			}else{
				c[p[i]] = c[p[i-1]] + 1;
			}
		}
		int k=0;
		while((1<<k)<n){
			for (int i=0;i<n;++i) p[i] = (p[i]-(1<<k)+n)%n;
			count_sort();
			c_new[p[0]] = 0;
			for (int i=1;i<n;++i){
				pii prev = {c[p[i-1]], c[(p[i-1]+(1<<k))%n]};
				pii cur = {c[p[i]], c[(p[i]+(1<<k))%n]};
				if (prev==cur){
					c_new[p[i]] = c_new[p[i-1]];
				}else c_new[p[i]] = c_new[p[i-1]]+1;
			}
			
			for (int i=0;i<n;++i) c[i] = c_new[i];
			k++;
		}
		k = 0;
		for (int i=0;i<n-1;++i){
			int posi = c[i];
			int j = p[posi-1];
			while(s[i+k]==s[j+k])k++;
			lcp[posi-1] = k;
			k = max(0, k-1);
		}
	}
};