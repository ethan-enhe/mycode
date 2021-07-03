#include<bits/stdc++.h>
using namespace std;
//{{{ read
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
//}}}

//{{{ def
typedef long long ll;
typedef long double ld;
template<class T1,class T2>struct pr{T1 x;T2 y;};
template<class T1,class T2>inline pr<T1,T2> mp(T1 x,T2 y){return pr<T1,T2>{x,y};}
const int MXN=1e5+5;
const int MXS=35;
int t,n,stdlen,p,len[MXN];
char str[MXN][MXS];

inline ld qpow(ld x,int y){
	ld r=1;
	while(y){
		if(y&1)r*=x;
		x*=x,y>>=1;
	}
	return r;
}
#define w(x,y) (dp[x]+qpow(abs(len[y]-len[x]-stdlen),p))
//}}}

char prompt[2][50]={
	"Too hard to arrange\n",
	"--------------------\n"
};
int ql,qr,tran[MXN];
pr<int,int> q[MXN];
ld dp[MXN];
int main(){
	read(t);
	while(t--){
		read(n),read(stdlen),read(p);stdlen++;
		q[qr=ql=1]=mp(0,1);
		for(int i=1;i<=n;i++){
			str[i][0]=0;
			read(str[i]+1);
			len[i]=strlen(str[i]+1)+len[i-1]+1;
		}
		for(int i=1;i<=n;i++){
			while(ql<qr && q[ql+1].y<=i)ql++;
			tran[i]=q[ql].x;
			dp[i]=w(tran[i],i);

			while(ql<=qr && w(i,q[qr].y)<w(q[qr].x,q[qr].y))qr--;
			if(ql>qr)q[++qr]=mp(i,i);
			else{
				int l=q[qr].y,r=n+1,mid;
				while(l<r){
					mid=(l+r)>>1;
					if(w(i,mid)<w(q[qr].x,mid))r=mid;
					else l=mid+1;
				}
				if(l<=n)q[++qr]=mp(i,l);
			}
		}
		if(dp[n]>1e18)prt(prompt[0]);
		else{
			prt((ll)dp[n]),pc('\n');
			for(int i=n;i;i=tran[i])str[i][0]=-1;
			for(int i=1;i<=n;i++)
				prt(str[i]+1),pc(str[i][0]?'\n':' ');
		}
		prt(prompt[1]);
	}
	return 0;
}
