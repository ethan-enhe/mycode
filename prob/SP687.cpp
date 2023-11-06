#include<bits/stdc++.h>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int MXN=2e5+5;
int n,str[MXN];
//{{{ SA
template<const int N>
struct SA{
	static const int LG=32-__builtin_clz(N);
	int tmp[N],ork[N],cnt[N],rk[N],sa[N],st[N][LG+1];
	bool eq(int x,int y,int w){return ork[x]==ork[y] && ork[x+w]==ork[y+w];}
#define rsort(x) {\
	for(int i=1;i<=m;i++)cnt[i]=0;\
	for(int i=1;i<=n;i++)cnt[rk[i]]++;\
	for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];\
	for(int i=n;i;i--)sa[cnt[rk[x]]--]=x,ork[i]=rk[i];\
}
    void init(int *arr, int m = N - 1) {
        for(int i=1;i<=n;i++)rk[i]=arr[i];
		rsort(i);
		for(int w=1;w<=n;w<<=1){
			int ind=0,i;
			for(i=n-w+1;i<=n;i++)tmp[++ind]=i;
			for(i=1;i<=n;i++)if(sa[i]>w)tmp[++ind]=sa[i]-w;
			rsort(tmp[i]);
			for(m=0,i=1;i<=n;i++)rk[sa[i]]=eq(sa[i],sa[i-1],w)?m:++m;
			if(m==n)break;
		}
		int lcp=0;
		for(int i=1;i<=n;i++){
			lcp-=!!lcp;
			while(arr[i+lcp]==arr[sa[rk[i]-1]+lcp])++lcp;
			st[0][rk[i]]=lcp;
		}
		for(int i=1;i<=LG;i++)
			for(int j=n-(1<<i)+1;j>0;j--)
				st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
    }
#undef rsort
};
//}}}
SA<MXN> pre,suf;
int main(){
	freopen("test.in", "r", stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		char x;
		scanf(" %c",&x);
		str[i]=x;
		putchar(x);
	}
    pre.init(str);
    reverse(str+1, str+1+n);
    suf.init(str);

    return 0;
}
