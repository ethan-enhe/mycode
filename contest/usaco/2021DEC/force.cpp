#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int MXN=5005,INF=1e9;
int t,tot,n[2],k;
struct cow{int x,w;}arr[2][MXN];
namespace T1 {
	int dp[MXN][MXN];
	void umn(int &x,int y){
		x=min(x,y);
	}
	void main(){
		memset(dp,0x3f,sizeof(dp));
		dp[0][0]=0;
		for(int i=0;i<=n[0];i++)
			for(int j=0;j<=n[1];j++){
				if(i && j && abs(arr[0][i].x-arr[1][j].x)<=k)
					umn(dp[i][j],dp[i-1][j-1]);
				if(i)umn(dp[i][j],dp[i-1][j]+arr[0][i].w);
				if(j)umn(dp[i][j],dp[i][j-1]+arr[1][j].w);
			}
		printf("%d\n",dp[n[0]][n[1]]);
	}
}
namespace T2{
	int pre[2][MXN],f[2][MXN][MXN],g[2][MXN][MXN];
	void umx(int &x,int y){
		x=max(x,y);
	}
	void main(){
		memset(f,~0x3f,sizeof(f));
		memset(g,~0x3f,sizeof(g));
		for(int i=0;i<2;i++){
			for(int j=1;j<=n[i];j++){
				pre[i][j]=-1;
				for(int l=n[!i];l;l--)
					if(arr[!i][l].x<arr[i][j].x-k){
						pre[i][j]=l;
						break;
					}
				//cerr<<pre[i][j]<<" ";
			}
			//cerr<<endl;
		}

		f[0][0][0]=f[1][0][0]=0;
		for(int i=0;i<=n[0];i++)
			for(int j=0;j<=n[1];j++){
				int l;
				//0
				if(i)
					umx(f[0][i][j],g[0][i-1][j]+arr[0][i].w);
				l=min(j,pre[0][i]);
				if(~l && i-1-j+l>=0)
					umx(f[0][i][j],g[1][i-1-j+l][l]+arr[0][i].w);
				g[0][i][j]=f[0][i][j];
				if(i && j && abs(arr[0][i].x-arr[1][j].x)<=k)
					umx(g[0][i][j],g[0][i-1][j-1]);
				//1

				if(j)
					umx(f[1][i][j],g[1][i][j-1]+arr[1][j].w);
				l=min(i,pre[1][j]);
				if(~l && j-1-i+l>=0)
					umx(f[1][i][j],g[0][l][j-1-i+l]+arr[1][j].w);
				g[1][i][j]=f[1][i][j];
				if(i && j && abs(arr[0][i].x-arr[1][j].x)<=k)
					umx(g[1][i][j],g[1][i-1][j-1]);
			}
		printf("%d",max(g[0][n[0]][n[1]],g[1][n[0]][n[1]]));
	}

}


int main(){
	scanf("%d%d%d",&t,&tot,&k);
	//if(t==2 && tot==5 && k==4)
	//	return puts("16"),0;
	//else if(t==2 && tot==10 && k==76)
	//	return puts("1893"),0;

	while(tot--){
		char ct;cow cur;
		scanf(" %c%d%d",&ct,&cur.x,&cur.w);
		bool f=(ct=='H');
		arr[f][++n[f]]=cur;
	}
	if(t==1)T1::main();
	else T2::main();

	return 0;
}
