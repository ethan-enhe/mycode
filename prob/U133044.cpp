#include<bits/stdc++.h>
using namespace std;

#define il inline
#define fi first
#define se second


const int BS=1<<20;
char ibuf[BS],*ip1=ibuf,*ip2=ibuf;
char obuf[BS],*op=obuf;
#define gc() (ip1==ip2 && (ip2=(ip1=ibuf)+fread(ibuf,1,BS,stdin),ip1==ip2)?EOF:*ip1++)
#define flsh() (fwrite(obuf,1,op-obuf,stdout),op=obuf)
#define pc(x) (*op++=(x),op==obuf+BS && flsh())
#define isdig(x) ((x)>='0' && (x)<='9')
#define isemp(x) ((x)==' ' || (x)=='\n' || (x)=='\r' || (x)=='\t')
struct flusher{inline ~flusher(){flsh();}}tmp;

template<class T>
inline void read(T &x){
	bool f=0;x=0;char c;
	while(c=gc(),!isdig(c))if(c=='-')f=1;
	while(isdig(c))x=(x<<3)+(x<<1)+(c^48),c=gc();
	if(f)x=-x;
}
inline void read(char *x){
	while(*x=gc(),isemp(*x))if(*x==EOF)return;
	while(*++x=gc(),!isemp(*x) && *x!=EOF);
	*x=0;
}
template<class T>
inline void prt(T x){
	if(x<0)pc('-'),x=-x;
	if(x>9)prt(x/10);
	pc(x%10^48);
}
inline void prt(char *x){while(*x)pc(*x++);}
inline void prt(const char x[]){for(int i=0;x[i];i++)pc(x[i]);}

typedef long long ll;
const ll P=1e9+7,MXN=1e5+5;
ll BSZ,q,cur=1,cnt[MXN],ans[MXN],inv[MXN];
vector<pair<ll,ll>> fac[MXN];
struct que{
	ll l,r,id;
	il bool operator < (const que &b)const{
		if(l/BSZ==b.l/BSZ)return l/BSZ&1?r>b.r:r<b.r;
		return l<b.l;
	}
}ask[MXN];

il ll qpow(ll x,ll y){
    ll r=1;
    while(y){
        if(y&1)r=r*x%P;
        x=x*x%P,y>>=1;
    }
    return r;
}
il void modify(ll x,ll tp){
	for(auto f:fac[x]){
		cur=cur*inv[cnt[f.fi]]%P;
		cnt[f.fi]+=tp*f.se;
		cur=cur*cnt[f.fi]%P;
	}
}

int main(){
	inv[1]=1;
	for(int i=2;i<MXN;i++){
		inv[i]=qpow(i,P-2),cnt[i]=1;
		if(fac[i].empty()){
			fac[i].push_back({i,1});
			for(ll j=i<<1;j<MXN;j+=i){
				ll tj=j,cnt=0;
				do ++cnt,tj/=i;while(tj%i==0);
				fac[j].push_back({i,cnt});
			}
		}
	}
	read(q);
	BSZ=sqrt(q)+1;
	for(int i=1;i<=q;i++){
		read(ask[i].r),read(ask[i].l);
		ask[i].id=i;
	}
	sort(ask+1,ask+1+q);
	ll indl=1,indr=1;
	for(int i=1;i<=q;i++){
		while(indr<ask[i].r){
			++indr;
			modify(indr,1);
			modify(indr-indl,-1);
		}
		while(indl>ask[i].l){
			modify(indl,1);
			--indl;
			modify(indr-indl,-1);
		}
		while(indr>ask[i].r){
			modify(indr-indl,1);
			modify(indr,-1);
			--indr;
		}
		while(indl<ask[i].l){
			modify(indr-indl,1);
			++indl;
			modify(indl,-1);
		}
		ans[ask[i].id]=cur;
	}
	for(int i=1;i<=q;i++)
		prt(ans[i]),pc('\n');

	return 0;
}


