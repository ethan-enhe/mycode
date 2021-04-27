#include<bits/stdc++.h>
using namespace std;
const int MXM=23;
const int HMXM=12;
int n,m,hm,k,half,full;
int e[MXM][MXM],dp[1<<MXM];
int cntfrom[2][1<<HMXM][MXM],cntto[2][MXM][1<<HMXM];
inline int getfrom(const int &x,const int &y){return cntfrom[0][x&half][y]+cntfrom[1][x>>hm][y];}
inline int getto(const int &x,const int &y){return cntto[0][x][y&half]+cntto[1][x][y>>hm];}


inline int lbt(const int &x){return x&(-x);}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	hm=m>>1;
	half=(1<<hm)-1;
	full=(1<<m)-1;
	for(int i=1,last=-1,tmp;i<=n;i++){
		scanf("%d",&tmp);--tmp;
		if(~last)e[last][tmp]++;
		last=tmp;
	}
	for(int i=0;i<m;i++)
		for(int j=1,tmp,tlog;j!=(1<<hm);j++){
			tmp=lbt(j);
			tlog=log2(tmp);
			cntfrom[0][j][i]=cntfrom[0][j^tmp][i]+e[tlog][i];
		}
	for(int i=0;i<m;i++)
		for(int j=1,tmp,tlog;j!=(1<<(m-hm));j++){
			tmp=lbt(j);
			tlog=log2(tmp);
			cntfrom[1][j][i]=cntfrom[1][j^tmp][i]+e[tlog+hm][i];
		}
	for(int i=0;i<m;i++)
		for(int j=1,tmp,tlog;j!=(1<<hm);j++){
			tmp=lbt(j);
			tlog=log2(tmp);
			cntto[0][i][j]=cntto[0][i][j^tmp]+e[i][tlog];
		}
	for(int i=0;i<m;i++)
		for(int j=1,tmp,tlog;j!=(1<<(m-hm));j++){
			tmp=lbt(j);
			tlog=log2(tmp);
			cntto[1][i][j]=cntto[1][i][j^tmp]+e[i][tlog+hm];
		}
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for(int i=0,nx;i!=(1<<m);i++){
		for(int j=0;j<m;j++){
			if((i>>j)&1)continue;
			nx=i^(1<<j);
			dp[nx]=min(dp[nx],dp[i]+__builtin_popcount(nx)*(getfrom(i,j)-getto(j,full^nx)
					+(getfrom(full^nx,j)+getto(j,i))*k));
		}
	}
	printf("%d",dp[full]);
	return 0;
}
