#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=5e4+5;
const ll MXL=61;
char str[MXN];
ll n,rk;
ll pool[MXL][MXN],cnt[MXL],pre[MXL];
int main(){
	freopen("str.in","r",stdin);
	freopen("str.out","w",stdout);
	scanf("%s",str+1);n=strlen(str+1);
	for(int i=1;i<=n;i++){
		ll v=0;
		for(ll j=1;j<MXL && i+j-1<=n;j++){
			v=v<<1|(str[i+j-1]-'A');
			pool[j][++cnt[j]]=v;
		}
	}
	for(int i=1;i<MXL;i++){
		sort(pool[i]+1,pool[i]+1+cnt[i]);
		cnt[i]=unique(pool[i]+1,pool[i]+1+cnt[i])-pool[i]-1;
		pre[i]=pre[i-1]+(1ll<<i)-cnt[i];
	}
	scanf("%lld",&n);
	while(n--){
		scanf("%lld",&rk);
		ll l=1,r=MXL-1,mid;
		while(l<r){
			mid=(l+r)>>1;
			if(pre[mid]>=rk)r=mid;
			else l=mid+1;
		}
		ll dig=l;
		rk-=pre[dig-1];
		l=0,r=cnt[dig];
		//for(int i=1;i<=cnt[dig];i++)cout<<pool[dig][i]<<endl;
		while(l<r){
			mid=(l+r+1)>>1;
			if(pool[dig][mid]-mid+1<rk)l=mid;
			else r=mid-1;
		}
		rk+=l-1;
		for(ll i=dig-1;~i;i--)putchar('A'+((rk>>i)&1));
		putchar('\n');
	}
	return 0;
}
