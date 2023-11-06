//P3387 【模板】缩点
#include<bits/stdc++.h>
using namespace std;
const int MXN=1e4+5;
vector<int> e[MXN],ne[MXN];
int n,m;
int dfn[MXN],low[MXN],dfsc;
bool instk[MXN];
stack<int> st;
vector<int> ans,cur;
inline void tj(int p){
	dfn[p]=low[p]=++dfsc;
	st.push(p),instk[p]=1;
	for(int nx:e[p]){
		if(!dfn[nx])tj(nx),low[p]=min(low[p],low[nx]);
		else if(instk[nx])low[p]=min(low[p],dfn[nx]);
	}

	if(dfn[p]==low[p]){
		int x;
		cur.clear();
		do{
			x=st.top();st.pop();
			cur.push_back(x);
			instk[x]=0;
		}while(x!=p);
		sort(cur.begin(),cur.end());
		if(cur.size()>ans.size())
			ans=cur;
		else if(cur.size()==ans.size() && cur<ans)
			ans=cur;
	}
}
bool hasdeg[MXN];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,ts,tt,tp;i<=m;i++){
		scanf("%d%d%d",&ts,&tt,&tp);
		e[ts].push_back(tt);
		if(tp==2)
			e[tt].push_back(ts);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tj(i);
	printf("%zu\n",ans.size());
	for(int i:ans)
		printf("%d ",i);
	return 0;
}
