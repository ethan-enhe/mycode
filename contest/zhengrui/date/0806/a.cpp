#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
int T,t;
ld w0,d;
ld qpow(ld x,int y){
	ld r=1;
	while(y){
		if(y&1)r*=x;
		x*=x,y>>=1;
	}
	return r;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%Lf%Lf",&t,&w0,&d);
		printf("%.10Lf\n",w0*w0*(d*d-1)/(qpow(d,2*t)-1));
	}
	return 0;
}
