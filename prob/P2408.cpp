#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MXN=2e5+5;
int n;
char str[MXN];
typedef int arrn[MXN];
arrn sa,tmp,ork,rk,cnt,h;
bool eq(int x,int y,int w){return ork[x]==ork[y] && ork[x+w]==ork[y+w];}
void sufixsort(){ 
	int m=130;
	for(int i=1;i<=n;i++)cnt[rk[i]=str[i]]++;
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
		for(int i=1;i<=n;i++)rk[sa[i]]=eq(sa[i],sa[i-1],w)?m:++m;
		if(m==n)break;
	}
	int lcp=0;
	for(int i=1;i<=n;i++){
		lcp-=!!lcp;
		while(str[i+lcp]==str[sa[rk[i]-1]+lcp])
			++lcp;
		h[rk[i]]=lcp;
	}
}
int main(){
	scanf("%d%s",&n,str+1);
	sufixsort();
	ll ans=(ll)n*(n+1)>>1;
	for(int i=1;i<=n;i++)
		ans-=h[i];
	printf("%lld",ans);

	return 0;
}
