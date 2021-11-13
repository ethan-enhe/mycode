#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
const int MXN=3e5+5;
int n,m1,m2;
int fa[MXN];
int r1[MXN],r2[MXN];
map<int,int> cnt[MXN];
inline int find(int p){return fa[p]==p?p:fa[p]=find(fa[p]);}
inline void solve(int m,int *res){
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=m;i++){
		int ts,tt;
		scanf("%d%d",&ts,&tt);
		fa[find(ts)]=find(tt);
	}
	for(int i=1;i<=n;i++)
		res[i]=find(i);
}
int main(){
	scanf("%d%d%d",&n,&m1,&m2);
	solve(m1,r1);
	solve(m2,r2);
	for(int i=1;i<=n;i++)
		cnt[r1[i]][r2[i]]++;
	for(int i=1;i<=n;i++)
		printf("%d ",cnt[r1[i]][r2[i]]);

	return 0;
}
