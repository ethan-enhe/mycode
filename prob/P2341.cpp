//P3387 【模板】缩点
#include<bits/stdc++.h>
using namespace std;
const int MXN=1e4+5;
vector<int> e[MXN],ne[MXN];
int n,m;
int col[MXN],sz[MXN],colc;
int dfn[MXN],low[MXN],dfsc;
bool instk[MXN];
stack<int> st;
inline void tj(int p){
	dfn[p]=low[p]=++dfsc;
	st.push(p),instk[p]=1;
	for(int nx:e[p]){
		if(!dfn[nx])tj(nx),low[p]=min(low[p],low[nx]);
		else if(instk[nx])low[p]=min(low[p],dfn[nx]);
	}

	if(dfn[p]==low[p]){
		int x;++colc;
		do{
			x=st.top();st.pop();
			col[x]=colc,instk[x]=0;
			sz[colc]++;
		}while(x!=p);
	}
}
bool hasdeg[MXN];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,ts,tt;i<=m;i++){
		scanf("%d%d",&ts,&tt);
		e[ts].push_back(tt);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tj(i);
	for(int i=1;i<=n;i++)
		for(int nx:e[i])
            if (col[nx] != col[i]) hasdeg[col[i]] = 1;
    int res=0;
	for(int i=1;i<=colc;i++)
        if (!hasdeg[i]) {
            if(res){
				puts("0");
				return 0;
			}
			else res=sz[i];
        }
    printf("%d",res);
	return 0;
}
