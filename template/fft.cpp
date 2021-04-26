#include<bits/stdc++.h>
using namespace std;
struct comp{
	double x,y;
	inline comp(double x=0,double y=0):x(x),y(y){}
	inline comp operator + (const comp &b)const{return comp(x+b.x,y+b.y);}
	inline comp operator - (const comp &b)const{return comp(x-b.x,y-b.y);}
	inline comp operator * (const comp &b)const{return comp(x*b.x-y*b.y,x*b.y+y*b.x);}
};
inline void fft(int len,comp *f,int tp){
	if(len==1)return;
	comp f0[len>>1],f1[len>>1],w(cos(M_PI*2/len),tp*sin(M_PI*2/len)),cur(1);
	for(int i=0;i<len;i+=2)f0[i>>1]=f[i];
	for(int i=1;i<len;i+=2)f1[i>>1]=f[i];
	fft(len>>1,f0,tp);
	fft(len>>1,f1,tp);
	for(int i=0;i<len>>1;i++){
		f[i]=f0[i]+cur*f1[i];
		f[i+(len>>1)]=f0[i]-cur*f1[i];
		cur=cur*w;
	}
}
const int MXN=4e6+5;
int n,m,mxl;
comp arr[MXN],brr[MXN];
int main(){
	scanf("%d%d",&n,&m);
	n++,m++;
	for(int i=0;i<n;i++)scanf("%lf",&arr[i].x);
	for(int i=0;i<m;i++)scanf("%lf",&brr[i].x);
	mxl=1<<(int)(log2(n+m)+1);
	fft(mxl,arr,1);
	fft(mxl,brr,1);
	for(int i=0;i<mxl;i++)arr[i]=arr[i]*brr[i];
	fft(mxl,arr,-1);
	for(int i=0;i<n+m-1;i++)printf("%d ",(int)round(arr[i].x/mxl));
	return 0;
}
