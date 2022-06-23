#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct Node{
	int u,v,nt;
	long double w,t;
}pl[2000005];
int hd[2000005];
int n,U,cnt=1;
long double k[25],_ans;
int vis[25];
int q[2000005],ql,qr;
int d[2000005],nw[2000005];
inline void add(int u,int v,long double w)
{
	pl[++cnt].nt=hd[u];
	pl[cnt].u=u;
	pl[cnt].v=v;
	pl[cnt].t=w;
	hd[u]=cnt;
}
inline bool bfs()
{
	q[ql=qr=0]=0;
	for(int i=0;i<=U+n+1;i++)
		d[i]=0,nw[i]=hd[i];
	d[0]=1;
	while(ql<=qr)
	{
		int u=q[ql++];
		for(int i=hd[u];i;i=pl[i].nt)
		{
			int v=pl[i].v;
			long double w=pl[i].w;
			if(w>=1e-12&&!d[v])
			{
				d[v]=d[u]+1;
				q[++qr]=v;
			}
		}
	}
	return d[U+n+1];
}
inline long double dinic(int u,long double lim)
{
	if(u==U+n+1||!lim)
		return lim;
	long double sum=0;
	for(int i=nw[u];i;i=pl[i].nt)
	{
		nw[u]=i;
		int v=pl[i].v;
		long double w=pl[i].w;
		if(w<1e-12||d[v]!=d[u]+1)
			continue;
		long double tp;
		if(lim-sum<w)
			tp=dinic(v,lim-sum);
		else
			tp=dinic(v,w);
		pl[i].w-=tp;
		pl[i^1].w+=tp;
		sum+=tp;
		if(lim-sum<1e-12)
			break;
	}
	if(lim-sum>=1e-12)
		d[u]=0;
	return sum;
}
int main()
{
    freopen("test.in","r",stdin);
    freopen("fyq.out","w",stdout);
	scanf("%d",&n);
	U=1<<n;
	for(int i=0;i<U;i++)
	{
		long double p;
		scanf("%Lf",&p);
		add(0,i+1,p);
		add(i+1,0,0);
		for(int j=1;j<=n;j++)
		{
			if(i>>(j-1)&1)
			{
				k[j]+=p;
				add(i+1,U+j,p);
				add(U+j,i+1,0);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		add(U+i,U+n+1,0);
		vis[i]=cnt;
		add(U+n+1,U+i,0);
	}
	long double l=0,r=1.0;
	int _=25;
	while(_--)
	{
		long double mid=(l+r)/2,sum=0,ans=0;
		for(int i=1;i<=cnt;i++)
			pl[i].w=pl[i].t;
		for(int i=1;i<=n;i++)
		{
			pl[vis[i]].w=k[i]*mid;
			sum+=k[i]*mid;
		}
		while(bfs())
			ans+=dinic(0,1e9);
		if(sum-ans<1e-12)
		{
			_ans=mid;
			l=mid;
		}
		else
		{
			r=mid;
		}
	}
	printf("%.10Lf",_ans);
	return 0;
}
