#include"opt.h"
#include<bits/stdc++.h>
#define re register
using namespace std;
typedef long long ll;
typedef long double ld;
const ll MXN=1e10;
const ll LG=max(1.,log(MXN)-2);
const ll PROG=(1ll<<24)-1;
bitset<MXN> isc;
ll *pri,cnt;
ld mn=1e9;ll s,m;


inline ld lfabs(const ld &x){return x>0?x:-x;}
inline ld err(const ll &i,const ll &j){return lfabs(M_PI*pri[j]-i);}
int main(){
	ll start=clock();
	pri=new ll[MXN/LG];
	printf("Malloc done\n");
	re ll ind=1;
	for(re ll i=2;i<MXN;i++){
		if(!(i&PROG))printf("%lld\n",i);
		if(!isc[i]){
			pri[++cnt]=i;
			re ld tmp=err(i,ind),nx=err(i,ind+1);
			while(ind<cnt && nx<=tmp)
				tmp=nx,nx=err(i,(++ind)+1);
			if(tmp<=1e-5 && lfabs(M_PI-(ld)i/pri[ind])<mn){
				mn=lfabs(M_PI-(ld)i/pri[ind]);
				s=i,m=pri[ind];
			}
		}
		for(re ll j=1;i*pri[j]<MXN;j++){
			isc[i*pri[j]]=1;
			if(!(i%pri[j]))break;
		}
	}
	printf("%lld %lld %.18Lf %.18Lf\n",s,m,(ld)s/m,mn);
	printf("Time: %.3Lf",ld(clock()-start)/CLOCKS_PER_SEC);

	return 0;
}
