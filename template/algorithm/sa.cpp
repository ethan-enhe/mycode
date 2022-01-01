#include <bits/stdc++.h>
using namespace std;
const int MXN=2e5+5,LG=31-__builtin_clz(MXN);
int t,n,tot;
char str[MXN];

namespace SA{
	typedef int arrn[MXN];
	arrn sa,rk,tmp,ork,cnt;
	int h[LG+1][MXN];
	inline bool cmp(int x,int y,int w){return ork[x]==ork[y] && ork[x+w]==ork[y+w];}
	template <typename T>
	inline void init(int n,int m,T *arr){
		for(int i=1;i<=m;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)cnt[rk[i]=arr[i]]++;
		for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i;i--)sa[cnt[rk[i]]--]=i;
		for(int w=1;w<=n;w<<=1){
			int ind=0;
			for(int i=n-w+1;i<=n;i++)tmp[++ind]=i;
			for(int i=1;i<=n;i++)if(sa[i]>w)tmp[++ind]=sa[i]-w;
			for(int i=1;i<=m;i++)cnt[i]=0;
			for(int i=1;i<=n;i++)cnt[rk[i]]++;
			for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
			for(int i=n;i;i--)sa[cnt[rk[tmp[i]]]--]=tmp[i],ork[i]=rk[i];
			m=0;
			for(int i=1;i<=n;i++)rk[sa[i]]=cmp(sa[i],sa[i-1],w)?m:++m;
			if(m==n)break;
		}

		arr[n+1]=-1;
		for(int i=1,lcp=0;i<=n;i++){
			lcp-=!!lcp;
			while(arr[i+lcp]==arr[sa[rk[i]-1]+lcp])
				++lcp;
			h[0][rk[i]]=lcp;
		}
		for(int i=1;i<=LG;i++)
			for(int w=1<<(i-1),j=n-(1<<i)+1;j>0;j--)
				h[i][j]=min(h[i-1][j],h[i-1][j+w]);
	}
	inline int lcp(int x,int y){
		x=rk[x],y=rk[y];
		assert(x!=y);
		if(x>y)swap(x,y);
		++x;int lg=31-__builtin_clz(y-x+1);
		return min(h[lg][x],h[lg][y-(1<<lg)+1]);
	}
}

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		tot=n*2+2;
		for(int i=1;i<=n;i++){
			char x;
			do x=getchar();while(x!='a' && x!='b');
			str[i]=str[tot-i]=x;
		}
		str[n+1]='#';
		str[tot]=0;
		SA::init(tot-1, 130, str);
		int ans=0;
		for(int i=1;i<=n;i++)
			for(int j=i<<1;j<=n;j+=i)
				ans=max(ans,(SA::lcp(tot-j,tot-j+i)+SA::lcp(j,j-i)+i-1)/i);
		printf("%d\n",ans);
	}
	return 0;
}
