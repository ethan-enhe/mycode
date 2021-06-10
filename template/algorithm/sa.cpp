#include<bits/stdc++.h>
using namespace std;
const int MXN=2e6+5;
int n;
int arr[MXN];
int cnt[MXN],tmp[MXN],ork[MXN];
int sa[MXN],rk[MXN],h[MXN];
inline bool cmp(const int &x,const int &y,const int &w){return ork[x]==ork[y] && ork[x+w]==ork[y+w];}
inline void calSA(){
	int m=1e6;
	for(int i=1;i<=n;i++)cnt[rk[i]=arr[i]]++;
	for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
	for(int i=n;i;i--)sa[cnt[rk[i]]--]=i;
	
	for(int w=1,ind=0;w<n;w<<=1,ind=0){
		for(int j=n-w+1;j<=n;j++)tmp[++ind]=j;
		for(int j=1;j<=n;j++)if(sa[j]>w)tmp[++ind]=sa[j]-w;

		for(int j=1;j<=m;j++)cnt[j]=0;
		for(int j=1;j<=n;j++)cnt[rk[j]]++;
		for(int j=1;j<=m;j++)cnt[j]+=cnt[j-1];
		for(int j=n;j;j--)sa[cnt[rk[tmp[j]]]--]=tmp[j];

		for(int j=1;j<=n;j++)ork[j]=rk[j];
		rk[sa[1]]=m=1;
		for(int i=2;i<=n;i++)rk[sa[i]]=cmp(sa[i],sa[i-1],w)?m:++m;
	}
}
inline void calH(){
	for(int i=1,lcp=0;i<=n;i++){
		if(lcp)lcp--;
		while(i+lcp<=n && sa[rk[i]-1]+lcp<=n && 
				arr[i+lcp]==arr[sa[rk[i]-1]+lcp])
			lcp++;
		h[rk[i]]=lcp;
	}
}

int main(){
	calSA();
	calH();
	return 0;
}
