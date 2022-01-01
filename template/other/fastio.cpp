#include<bits/stdc++.h>
using namespace std;

//{{{ Fast IO
namespace fio{
const int BS=1<<20;
char ibuf[BS],*ip1=ibuf,*ip2=ibuf;
char obuf[BS],*op=obuf;
#define gc() (ip1==ip2 && (ip2=(ip1=ibuf)+fread(ibuf,1,BS,stdin),ip1==ip2)?EOF:*ip1++)
#define flsh() (fwrite(obuf,1,op-obuf,stdout),op=obuf)
#define pc(x) (*op++=(x),op==obuf+BS && flsh())
struct flusher{inline ~flusher(){flsh();}}tmp;

template<class T>
inline void read(T &x){
	bool f=0;x=0;char c;
	while(c=gc(),!isdigit(c))if(c=='-')f=1;
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=gc();
	if(f)x=-x;
}
inline void read(char &x){while(x=gc(),isspace(x));}
inline void read(char *x){
	while(*x=gc(),isspace(*x))if(*x==EOF)return;
	while(*++x=gc(),!isspace(*x) && *x!=EOF);
	*x=0;
}
template<class T>
inline void prt(T x){
	if(x<0)pc('-'),x=-x;
	if(x>9)prt(x/10);
	pc(x%10^48);
}
inline void prt(const char x){pc(x);}
inline void prt(char *x){while(*x)pc(*x++);}
inline void prt(const char x[]){for(int i=0;x[i];i++)pc(x[i]);}
#undef gc
#undef pc
#undef flsh
}

void prt(){}
template <typename T1, typename... T2>
void prt(const T1 x,const T2... y) {
	fio::prt(x);
	prt(y...);
}
void read(){}
template <typename T1, typename... T2>
void read(T1 &x, T2 &...y) {
	fio::read(x);
	read(y...);
}
//}}}
int main(){
	int x=1,y=2,z=3;
	read(x,y,z);
	prt(x,y,z,"1231");
	return 0;
}
