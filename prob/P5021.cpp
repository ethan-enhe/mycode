#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pi;
const int MXN=5e4+5;
int n,m;
vector<pi> g[MXN];
vector<int> len[MXN];
inline int match(vector<int> &arr,int lim,int bani=-1){
	int ind=0,res=0;
	for(int i=arr.size()-1;i>ind;i--)
		if(i!=bani){
			while(ind<i && (arr[ind]+arr[i]<lim || ind==bani))
				ind++;
			if(ind==i)
				return res;
			ind++,res++;
		}

	return res;
}
inline pi dfs(int p,int fa,int lim){
	pi res;
	len[p].clear();
	for(pi &nx:g[p])
		if(nx.fi!=fa){
			pi tmp=dfs(nx.fi,p,lim);
			tmp.se+=nx.se;
			if(tmp.se>=lim)tmp.fi++;
			else len[p].push_back(tmp.se);
			res.fi+=tmp.fi;
		}
	if(len[p].size()){
		sort(len[p].begin(),len[p].end());
		int l=0,r=len[p].size()-1,tmp=match(len[p],lim);
		while(l<r){
			int mid=(l+r+1)>>1;
			if(match(len[p],lim,mid)==tmp)l=mid;
			else r=mid-1;
		}
		res.fi+=tmp;
		if(match(len[p],lim,l)==tmp)res.se=len[p][l];
	}
	return res;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int ts,tt,tw;
		scanf("%d%d%d",&ts,&tt,&tw);
		g[ts].push_back({tt,tw});
		g[tt].push_back({ts,tw});
	}
	int l=0,r=1e9;
	while(l<r){
		int mid=(l+r+1)>>1;
		if(dfs(1,0,mid).fi>=m)l=mid;
		else r=mid-1;
	}
	printf("%d",l);
	return 0;
}
