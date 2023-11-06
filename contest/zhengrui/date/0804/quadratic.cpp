#include<bits/stdc++.h>
using namespace std;
const int MXN=2005;
int n,q;
struct f{
	double a,b,c,l,x;bool del;
	inline double va(){return a*x*x+b*x+c;}
	inline double slope(){
		if(x<0 || x>l)return 0;
		return b+a*x*2;
	}
}arr[MXN];
double x[MXN];
inline void cal(double add){
	double s=0;
	for(int i=1;i<=n;i++)
		if(!arr[i].del)
			s+=arr[i].slope();
	add/=s;
	for(int i=1;i<=n;i++)
		if(!arr[i].del)
		arr[i].x-=arr[i].slope()*add;
}
inline double solve(double sum){
	for(int i=1;i<=n;i++)
		if(!arr[i].del)
			arr[i].x=0.0001;
	while(sum>=0){
		cal(0.1);
		sum-=0.1;
	}
	double res=0;
	for(int i=1;i<=n;i++)res+=arr[i].va();
	return res;
}
int main(){
	scanf("%d",&q);
	while(q--){
		int op;
		scanf("%d",&op);
		if(op==1){
			++n;
			scanf("%lf%lf%lf%lf",&arr[n].l,&arr[n].a,&arr[n].b,&arr[n].c);
		}
	}
	cout<<solve(2);

	return 0;
}
