//[SDOI2006]线性方程组
#include<bits/stdc++.h>
using namespace std;
const int MXN=52;
const double eps=1e-8;
int n;
double arr[MXN][MXN],tmp[MXN];
inline bool is0(double x){return fabs(x)<=eps;}
inline void eli(double *a,double *b,int ind){
    if(is0(a[ind]) || is0(b[ind]))return;
    double rate=a[ind]/b[ind];
    for(int i=ind;i<=n+1;i++)a[i]-=rate*b[i];
}
inline int insert(double *eq){
	for(int i=1;i<=n;i++)
		if(!is0(eq[i])){
			if(!is0(arr[i][i]))eli(eq,arr[i],i);
			else{
				for(int j=i+1;j<=n;j++)eli(eq,arr[j],j);
				for(int j=1;j<i;j++)eli(arr[j],eq,i);
				for(int j=i;j<=n+1;j++)arr[i][j]=eq[j];
				return 1;
			}
		}
	return is0(eq[n+1])?0:-1;
}

int main(){
	scanf("%d",&n);
	bool infsol=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n+1;j++)scanf("%lf",tmp+j);
		int tres=insert(tmp);
		if(tres==-1)return printf("-1"),0;
		infsol|=!tres;
	}
	if(infsol)printf("0");
	else
		for(int i=1;i<=n;i++)
			printf("x%d=%.2f\n",i,arr[i][n+1]/arr[i][i]+eps);

	return 0;
}
