//{{{ optimize
#pragma GCC optimize(3)
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
//}}}

#include<bits/stdc++.h>
#define re register
using namespace std;
typedef long long ll;
typedef long double ld;
const ll MXN=1e9;
const ll LG=max(1.,log(MXN)-2);
bitset<MXN> isc;
ll *pri,cnt;


inline ld lfabs(const ld &x){return x>0?x:-x;}
inline ld err(const ll &i,const ll &j){return lfabs(M_PI*pri[j]-i);}
int main(){
	ll start=clock();
	pri=new ll[MXN/LG];
	printf("Malloc done\n");
	re ll ind=1;
	for(re ll i=2;i<MXN;i++){
		if(!isc[i]){
			pri[++cnt]=i;
			re ld tmp=err(i,ind),nx=err(i,ind+1);
			while(ind<cnt && nx<=tmp)
				tmp=nx,nx=err(i,(++ind)+1);
			if(tmp<=1e-5)
				printf("%lld %lld %.18Lf\n",i,pri[ind],tmp);
		}
		for(re ll j=1;i*pri[j]<MXN;j++){
			isc[i*pri[j]]=1;
			if(!(i%pri[j]))break;
		}
	}
	printf("Time: %.3Lf",ld(clock()-start)/CLOCKS_PER_SEC);

	return 0;
}
