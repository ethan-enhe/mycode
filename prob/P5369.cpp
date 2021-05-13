#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=20;
const ll P=998244353;
/*
 * pre_neg所有前缀都<0
 * pre_pos所有前缀都>=0
 */
ll n,tot,arr[MXN];
ll sum[1<<MXN],pre_neg[1<<MXN],pre_pos[1<<MXN];
int main(){
	scanf("%lld",&n);tot=1<<n;
	for(ll i=0;i<n;i++)scanf("%lld",arr+i);
	pre_neg[0]=pre_pos[0]=1;
	for(ll i=0,tmp;i!=tot;i++){
		if(i){
			tmp=i&(-i);
			sum[i]=sum[i^tmp]+arr[(ll)log2(tmp)];
		}
		for(ll j=0;j<n;j++){
			if((i>>j)&1)continue;
			tmp=i|(1<<j);
			if(sum[i]+arr[j]<0)pre_neg[tmp]=(pre_neg[tmp]+pre_neg[i])%P;
			else pre_pos[tmp]=(pre_pos[tmp]+pre_pos[i])%P;
		}
	}
	ll res=0;
	for(int i=0;i<n;i++)
		for(int j=0;j!=tot;j++){
			if((j>>i)&1)continue;
			res=(res+pre_pos[j]*pre_neg[(tot-1)^j^(1<<i)]%P*sum[j^(1<<i)])%P;
		}
	printf("%lld",(res+P)%P);
	return 0;
}
