#include <bits/stdc++.h>
using namespace std;
const int MXN=105;
int n;
bool ok[MXN];
double m[MXN][MXN],tmp[MXN];
#define is0(x) (fabs(x)<1e-8)
inline void eli(double *x,double *y,int ind){
	double rate=x[ind]/y[ind];
	for(int i=0;i<=ind;i++)
		x[i]-=y[i]*rate;
}
inline bool insert(){
	for(int i=n;i;i--){
		if(!is0(tmp[i])){
			if(ok[i])
				eli(tmp,m[i],i);
			else{
				for(int j=i-1;j;j--)
					if(ok[j] && !is0(tmp[j]))
						eli(tmp,m[j],j);
				for(int j=i+1;j<=n;j++)
					if(!is0(m[j][i]))
						eli(m[j],tmp,i);
				ok[i]=1;
				swap(m[i],tmp);
				return 0;
			}
		}
	}
	return 1;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			scanf("%lf",tmp+j);
		scanf("%lf",tmp);
		if(insert())
			return puts("No Solution"),0;
	}
	for(int i=1;i<=n;i++)
		printf("%.2f\n",m[i][0]/m[i][i]);

	return 0;
}
