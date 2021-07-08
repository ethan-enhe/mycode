#include<bits/stdc++.h>
using namespace std;
const int GO[2][8]={
	{1,1,1,0,0,-1,-1,-1},
	{1,0,-1,1,-1,1,0,-1}
};
const int MXSZ=2e4+5;
bool *mp[MXSZ];
int *col[MXSZ];
int n,m,c;
inline void mark(int x,int y,int v){
}
int main(){
	scanf("%d%d%d",&n,&m,&c);
	for(int i=0;i<=n+1;i++){
		mp[i]=(bool*)calloc(m+2,sizeof(bool));
		col[i]=(int*)calloc(m+2,sizeof(int));
		mp[i][0]=mp[i][m+1]=1;
	}
	for(int i=1;i<=m;i++)mp[0][i]=mp[n+1][i]=1;
	while(c--){
		int tx,ty;
		scanf("%d%d",&tx,&ty);
		mp[tx][ty]=1;
	}
	for(int i=0;i<=n+1;i++){
		free(mp[i]);
		free(col[i]);
	}


	return 0;
}
