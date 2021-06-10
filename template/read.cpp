#include<bits/stdc++.h>
using namespace std;

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




int main(){
	return 0;
}
