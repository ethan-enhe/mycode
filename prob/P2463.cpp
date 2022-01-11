#include <bits/stdc++.h>
#define log(fmt...) fprintf
using namespace std;
const int MXM=1005,MXN=MXM*MXM,LG=31-__builtin_clz(MXN);
//asdaadd

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

int n,tot;
int arr[MXN],id[MXN];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int tmp;
		scanf("%d",&tmp);
		while(tmp--){
			id[++tot]=i;
			scanf("%d",arr+tot);
		}
		arr[++tot]=MXM;
	}
	--tot;
	for(int i=1;i<=tot;i++)
		log("%d ",arr[i]);
	SA::init(tot, MXM, arr);
	for(int i=1;i<=tot;i++)
		log("%d ",SA::sa[i]);
	return 0;
}

