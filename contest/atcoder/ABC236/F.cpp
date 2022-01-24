#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
struct _xor{
	static const int D=63;
	ull m[D+1];
	inline bool insert(ull x){
		for(int i=D;~i;i--)
			if((x>>i)&1){
				if(m[i])x^=m[i];
				else{
					for(int j=i-1;~j;j--)
						if((x>>j)&1)
							x^=m[j];
					for(int j=i+1;j<=D;j++)
						if((m[j]>>i)&1)
							m[j]^=x;
					m[i]=x;
					return 1;
				}
			}
		return 0;
	}
}base;
pair<ull,ull> arr[1000000];
int main(){
	int n;
	scanf("%d",&n);
	n=(1<<n)-1;
	for(int i=1;i<=n;i++){
		scanf("%llu",&arr[i].first);
		arr[i].second=i;
	}
	sort(arr+1,arr+1+n);
	ull res=0;
	for(int i=1;i<=n;i++)
		if(base.insert(arr[i].second))
			res+=arr[i].first;
	printf("%llu",res);

	return 0;
}
