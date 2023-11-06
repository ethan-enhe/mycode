#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int inf=1e9;
int T,q,len[maxn],n,m,sa[maxn],x[maxn],y[maxn],c[maxn],rnk[maxn],h[maxn],col[maxn];
int lg[maxn],st1[11][maxn][20],st2[11][maxn][20],l,r,mid,nww,lst,ans;
char s[maxn],ss[11][maxn];
int rmqmin(int x,int l,int r)
{
	int k=lg[r-l+1];
	return min(st1[x][l][k],st1[x][r-(1<<k)+1][k]);
}
int rmqmax(int x,int l,int r)
{
	int k=lg[r-l+1];
	return max(st2[x][l][k],st2[x][r-(1<<k)+1][k]);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		ans=0;n=0;
		scanf("%d",&q);
		for(int i=1;i<=q;i++)
		{
			scanf("%s",ss[i]+1);
			len[i]=strlen(ss[i]+1);
			for(int j=1;j<=len[i];j++)s[++n]=ss[i][j],col[n]=i;
			s[++n]='#';
		}
		//printf("%s\n",s+1);
		m=128;
		for(int i=1;i<=n;i++)x[i]=s[i];
		for(int i=0;i<=m;i++)c[i]=0;
		for(int i=1;i<=n;i++)c[x[i]]++;
		for(int i=1;i<=m;i++)c[i]+=c[i-1];
		for(int i=n;i>=1;i--)sa[c[x[i]]--]=i;
		for(int k=1,cur;k<=n;k<<=1)
		{
			cur=0;
			for(int i=n;i>n-k;i--)y[++cur]=i;
			for(int i=1;i<=n;i++)if(sa[i]>k)y[++cur]=sa[i]-k;
			for(int i=0;i<=m;i++)c[i]=0;
			for(int i=1;i<=n;i++)c[x[i]]++;
			for(int i=1;i<=m;i++)c[i]+=c[i-1];
			for(int i=n;i>=1;i--)sa[c[x[y[i]]]--]=y[i];
			cur=y[sa[1]]=1;
			for(int i=2;i<=n;i++)
			{
				int a,b;
				a=sa[i]+k>n?-1:x[sa[i]+k];
				b=sa[i-1]+k>n?-1:x[sa[i-1]+k];
				y[sa[i]]=(x[sa[i]]==x[sa[i-1]])&&(a==b)?cur:(++cur);
			}
			swap(x,y);
			if(cur>=n)break;
			m=cur;
		}
		for(int i=1;i<=n;i++)rnk[sa[i]]=i;
		int nww=0;
		for(int i=1;i<=n;i++)
		{
			if(rnk[i]==1)continue;
			if(nww)nww--;
			while(i+nww<=n&&sa[rnk[i]-1]+nww<=n&&s[i+nww]==s[sa[rnk[i]-1]+nww])nww++;
			h[rnk[i]]=nww;
		}
		for(int i=2;i<=n+1;i++)lg[i]=lg[i/2]+1;
		for(int i=1;i<=n;i++)
		{
			st1[col[sa[i]]][i][0]=sa[i];
			st2[col[sa[i]]][i][0]=sa[i];
			for(int j=1;j<=q;j++)if(col[sa[i]]!=j)
			{
				st1[j][i][0]=inf;
				st2[j][i][0]=-inf;
			}
		}
		for(int t=1;t<=q;t++)for(int i=1;i<=lg[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)
		st1[t][j][i]=min(st1[t][j][i-1],st1[t][j+(1<<(i-1))][i-1]),
		st2[t][j][i]=max(st2[t][j][i-1],st2[t][j+(1<<(i-1))][i-1]);
		l=0;r=n+1;
		while(l+1<r)
		{
			mid=(l+r)>>1;
			lst=1;nww=0;
			for(int i=2;i<=n;i++)
			{
				if(h[i]<mid)
				{
					//[lst,i-1]
					int minn=inf;
					for(int t=1;t<=q;t++)minn=min(minn,rmqmax(t,lst,i-1)-rmqmin(t,lst,i-1));
					nww=max(nww,minn);
					lst=i;
				}
			}
			int minn=inf;
			for(int t=1;t<=q;t++)minn=min(minn,rmqmax(t,lst,n)-rmqmin(t,lst,n));
			nww=max(nww,minn);
			if(nww>=mid)ans=mid,l=mid;
			else r=mid;
		}
		printf("%d\n",ans);
	}
	return 0;
}
