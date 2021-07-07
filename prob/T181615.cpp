#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
inline int chk(ull x){
	int y;
	cout<<x<<flush;
	cin>>y;
	return y;
}
inline void work(){
	ull l=0,r=63;
	while(l<r){
		ull mid=(l+r+1)>>1;int tmp=chk((ull)1<<mid);
		if(!tmp)return;
		if(tmp==-1)r=mid-1;
		else l=mid;
	}
	if(!l){
		chk(1);
		return;
	}
	ull x=1<<l;
	for(ull i=l-1;~i;i--){
		int tmp=chk(x+((ull)1<<i));
		if(!tmp)return;
		if(tmp==1)
			x+=(ull)1<<i;
	}
}
int main(){
	int T;
	cin>>T;
	while(T--)work();


	return 0;
}
