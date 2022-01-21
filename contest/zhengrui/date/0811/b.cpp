#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=205;
char str[MXN];ll n,ans;
struct seg{ll l,v,nv;};
vector<seg> e[MXN];

ll d[MXN];
inline void mod(ll x,ll y){for(;x;x^=x&(-x))d[x]+=y;}
inline ll suf(ll x){
	ll res=0;
	for(;x<=n;x+=x&(-x))
		res+=d[x];
	return res;
}

int main(){
	scanf("%s",str+1);
	n=strlen(str+1);
	for(ll i=1;i<=n;i++)
		for(ll j=i;j<=n;j++){
			bool f=1;
			for(ll k=i;k<=(i+j)>>1;k++)
				if(str[k]!=str[i+j-k]){
					f=0;
					break;
				}
			if(f){
				e[j].push_back({i,1,0});
				ans++;
			}
		}
	ll last=0;
	while(last!=ans){
		last=ans;
		memset(d,0,sizeof(d));
		for(ll i=1;i<=n;i++){
			for(seg &j:e[i])
				ans+=(j.nv=suf(j.l+1));
			for(seg &j:e[i]){
				mod(j.l,j.v);
				j.v=j.nv;
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
