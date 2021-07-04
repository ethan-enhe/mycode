#include<bits/stdc++.h>
using namespace std;
const int SZ=12582917;
const int DSZ=1.3e7;
template<class T>
struct hmap{
	typedef unsigned long long ull;
	int h[SZ],nx[DSZ],cnt;ull u[DSZ];T v[DSZ];
	inline hmap(){memset(h,0,sizeof(h)),cnt=0;}
	inline T &operator [] (const ull &x){
		int ind=x%SZ;
		for(int i=h[ind];i;i=nx[i])if(u[i]==x)return v[i];
		return nx[++cnt]=h[ind],h[ind]=cnt,u[cnt]=x,v[cnt];
	}
};
hmap<int> x;
inline bool chk(int x){
	int mx=sqrt(x);
	for(int i=2;i<=mx;i++)
		if(x%i==0)
			return 0;
	return 1;
}
int main(){
	int t=clock();
	for(long long i=1;i<=10000000;i++)x[i*i]=1;
	cout<<(double)(clock()-t)/CLOCKS_PER_SEC;
	return 0;
}
