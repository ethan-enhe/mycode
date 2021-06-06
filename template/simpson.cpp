#include<bits/stdc++.h>
using namespace std;


double a;
inline double doubleabs(double x){return x<0?-x:x;}
inline double f(double x){return pow(x,a/x-x);}
inline double simpson(double l,double r,double fl,double fm,double fr){return (fl+fm*4+fr)*(r-l)/6;}
inline double cal(double l,double r,double fl,double fm,double fr,double ans,double eps){
	double mid=(l+r)/2,flm=f((l+mid)/2),frm=f((mid+r)/2);
	double il=simpson(l,mid,fl,flm,fm),ir=simpson(mid,r,fm,frm,fr);
	//据说这里*15和/15精度最高
	if(doubleabs(il+ir-ans)<=eps*15)return il+ir+(il+ir-ans)/15;
	return eps/=2,cal(l,mid,fl,flm,fm,il,eps)+cal(mid,r,fm,frm,fr,ir,eps);
}
inline double integ(double l,double r,double e){
	double fl=f(l),fm=f((l+r)/2),fr=f(r);
	return cal(l,r,fl,fm,fr,simpson(l,r,fl,fm,fr),e);
}

int main(){
	scanf("%lf",&a);
	if(a<0)printf("orz");
	else printf("%.5f",integ(1e-8,15,1e-8));
	return 0;
}
