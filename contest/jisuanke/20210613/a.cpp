#include<bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef long long ull;
typedef pair<ull,ull> pi;
//{{{ def
const ull MXN=40;
const ull MXMID=20;
ull n,b,mid;
ull arr[MXN];
//}}}
//{{{ func
pi lva[(1<<MXMID)+1],rva[1<<MXMID];
inline void init(){
	for(ull i=1;i!=(1<<mid);i++){
		ull lbt=i&(-i);
		lva[i]=mp(lva[i^lbt].fi+arr[(ull)log2(lbt)],lva[i^lbt].se+1);
	}
	sort(lva,lva+(1<<mid));
	for(ull i=(1<<mid)-1;~i;i--)
		lva[i].se=(1ull<<(mid-lva[i].se))+lva[i+1].se;
}
inline void cal(){
	ull tmid=n-mid,mnc=(b+1)>>1,ans=0;
	for(ull i=0;i!=(1<<tmid);i++){
		if(i){
			ull lbt=i&(-i);
			rva[i]=mp(rva[i^lbt].fi+arr[(ull)log2(lbt)+mid],rva[i^lbt].se+1);
		}
		ull pos=0;
		for(ull j=1<<(mid-1);j;j>>=1)
			if(lva[pos+j].fi<mnc-rva[i].fi)
				pos+=j;
		if(lva[pos].fi<mnc-rva[i].fi)pos++;
		ans+=lva[pos].se<<(tmid-rva[i].se);
	}
	ull all=1;
	for(ull i=1;i<=n;i++)all*=3;
	printf("%llu",all-ans*3);
}
//}}}
int main(){
	freopen("move.in","r",stdin);
	freopen("move.out","w",stdout);
	scanf("%llu%llu",&n,&b),mid=n>>1;
	for(ull i=0;i<n;i++)scanf("%llu",arr+i),b+=arr[i];


	init();
	cal();
	
	return 0;
}
