#include<bits/stdc++.h>
using namespace std;
const int MXN=3e5+5;
const int INF=1e9;
char arr[MXN];
int n,m,cnt[MXN],st[MXN][2];

inline int id(int x,int y){return x+(y?m:0);}
bool chs[MXN<<1];
int fa[MXN<<1],sz[MXN<<1];
int find(int x){
	if(fa[x]==x)return fa[x];
	sz[fa[x]]+=sz[x];sz[x]=0;
	return fa[x]=find(fa[x]);
}
inline void merge(int x,int y){fa[find(y)]=find(x);}
inline int del(int x){return chs[x]?sz[x]:0;}

int main(){
	scanf("%d%d %s",&n,&m,arr+1);
	for(int i=1,tsz,tind;i<=m;i++){
		sz[id(i,1)]=1;
		fa[id(i,0)]=id(i,0);
		fa[id(i,1)]=id(i,1);
		scanf("%d",&tsz);
		while(tsz--){
			scanf("%d",&tind);
			st[tind][++cnt[tind]]=i;
		}
	}
	for(int i=1,ans=0;i<=n;i++){
		bool dig=arr[i]-'0';

		ans-=del(find(id(st[i][0],0)))+del(find(id(st[i][0],1)));
		if(cnt[i]==1)
			sz[find(id(st[i][0],dig))]=INF;
		else{
			merge(id(st[i][0],0),id(st[i][1],dig^1));
			merge(id(st[i][0],1),id(st[i][1],dig));
		}
		if(sz[find(id(st[i][0],0))]>sz[find(id(st[i][0],1))]){
			ans+=sz[find(id(st[i][0],1))];
			chs[find(id(st[i][0],1))]=1;
		}
		else{
			ans+=sz[find(id(st[i][0],1))];
			chs[find(id(st[i][0],1))]=1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
