#include"opt.h"
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
//const ll MXN=1e10;
const ll PROG=(1ll<<30)-1;
const ll MXN=1e11;
const ll SQRT=sqrt(MXN)+5;
const ll BSZ=SQRT;
inline ld lfabs(const ld &x){return x>0?x:-x;}
inline ld err(const ll &i,const ll &j){return lfabs(M_PI*j-i);}

bool isc[SQRT];
ll pri[SQRT],cnt;
inline void init(){
	isc[1]=1;
	for(ll i=2;i<SQRT;i++)
		if(!isc[i]){
			pri[++cnt]=i;
			for(ll j=i*i;j<SQRT;j+=i)
				isc[j]=1;
		}
}
struct bpri{
	bool vis[BSZ];
	ll ind[BSZ],l,r;
	inline void cal(ll x){
		l=x,r=0;
		memset(vis,0,sizeof(vis));
		for(ll i=1;i<=cnt;i++)
			while(ind[i]-l<BSZ){
				vis[ind[i]-l]=1;
				ind[i]+=pri[i];
			}
	}
	inline void init(){for(ll i=1;i<=cnt;i++)ind[i]=pri[i]*pri[i];cal(1),vis[0]=1;}
	inline void nx(){if(++r==BSZ)cal(l+BSZ);;}
	inline void nxp(){do nx();while(vis[r]);}
	inline ll va(){return l+r;}
	inline bool ispri(){return !vis[r];}
}l,r;

int main(){
	ll start=clock();

	init();
	l.init(),r.init();
	l.nxp();
	ll cur=0,nx=l.va();
	ld mn=1e9;ll s=-1,m=-1;

	for(ll i=1;i<MXN;i++,r.nx()){
		if(!(i&PROG)){
	        printf("%.18LF\n%lld %lld %.18Lf %.18Lf\n",(ld)M_PI,s,m,(ld)s/m,mn);
            printf("%.3Lf sec %lld\%\n",ld(clock()-start)/CLOCKS_PER_SEC,i*100/MXN);
        }
		if(r.ispri()){
			while(err(i,nx)<=err(i,cur)){
				cur=nx;
				l.nxp();
				nx=l.va();
			}
			if(err(i,cur)<=1e-5 && lfabs(ld(i)/cur-M_PI)<mn){
				mn=lfabs(ld(i)/cur-M_PI);
				s=i,m=cur;
			}
		}
	}
	printf("%.18LF\n%lld %lld %.18Lf %.18Lf\n",(ld)M_PI,s,m,(ld)s/m,mn);
	printf("Time: %.3Lf",ld(clock()-start)/CLOCKS_PER_SEC);
	return 0;
}

