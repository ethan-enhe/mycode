#include <bits/stdc++.h>
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
using std::min;
template <class T>
void read(T &x)
{
	x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
}
double C[51][51],f[1<<10][51],g[1<<10][51];
int yuu[1<<10],dew[1<<10],n,m;
int main()
{
	read(n),read(m);
	for(int u,v,i=1;i<=m;i++)
	{
		read(u),read(v);
		++dew[(1<<u-1)|(1<<v-1)];
	}
	for(int s=1;s<1<<n;s++)
		for(int t=s;t;t=t-1&s)
			yuu[s]+=dew[t];
	C[0][0]=1;
	for(int i=1;i<=m;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	for(int s=1;s<1<<n;s++)
	{
	    for(int i=0;i<=yuu[s];i++)
		{
			for(int t=s-1&s;t;t=t-1&s)
                if(t&(s&-s))
                    for(int j=0;j<=min(i,yuu[t]);j++)
                        f[s][i]+=g[t][j]*C[yuu[s^t]][i-j];
			g[s][i]=C[yuu[s]][i]-f[s][i];
		}
	}
	double ans=0;
	for(int i=0;i<=m;i++) ans+=f[(1<<n)-1][i]/C[m][i],cerr<<f[(1<<n)-1][i]<<endl;
	ans/=m+1.0;
	printf("%.6f %.6f\n",f[(1<<n)-1][m],ans);
	return 0;
}

