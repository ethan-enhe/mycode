#include<bits/stdc++.h>
using namespace std;
const int MXN=2e6+5;
int n;
char arr[MXN];
int sa[MXN],rk[MXN],h[MXN];
int tmp[MXN],ork[MXN],cnt[MXN];
inline bool cmp(int x,int y,int w){return ork[x]==ork[y] && ork[x+w]==ork[y+w];}
inline void csa(){
	int m=128;
	for(int i=1;i<=n;i++)cnt[rk[i]=arr[i]]++;
	for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
	for(int i=n;i;i--)sa[cnt[rk[i]]--]=i;
	for(int w=1;w<n;w<<=1){
		int ind=0;
		for(int i=n-w+1;i<=n;i++)tmp[++ind]=i;
		for(int i=1;i<=n;i++)if(sa[i]>w)tmp[++ind]=sa[i]-w;

		for(int i=1;i<=m;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)cnt[rk[i]]++;
		for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i;i--)sa[cnt[rk[tmp[i]]]--]=tmp[i],ork[i]=rk[i];
		rk[sa[1]]=m=1;
		for(int i=2;i<=n;i++)rk[sa[i]]=cmp(sa[i],sa[i-1],w)?m:++m;
        if(m==n)break;
	}
}
inline void ch(){
	for(int i=1,lcp=0;i<=n;i++){
		if(lcp)lcp--;
        int j=sa[rk[i]-1];
		while(i+lcp<=n && j+lcp<=n && arr[i+lcp]==arr[j+lcp])
            lcp++;
		h[rk[i]]=lcp;
	}
}
int main(){
	scanf("%s",arr+1);n=strlen(arr+1);
	csa();//ch();
	for(int i=1;i<=n;i++)printf("%d ",sa[i]);
	return 0;
}
