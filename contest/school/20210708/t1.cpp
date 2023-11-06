#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mp[200];
ll t;
ll op[5],len[5];
int main(){
	mp['U']=0;
	mp['R']=1;
	mp['D']=2;
	mp['L']=3;
	scanf("%lld",&t);
	while(t--){
		for(ll i=0;i<4;i++){
			char tmp;
			scanf(" %c%lld",&tmp,len+i);
			op[i]=mp[(ll)tmp];
		}
		bool f1=1,f2=1;
		for(ll i=0;i<4;i++)
			if(op[(i+1)&3]!=((op[i]+1)&3)){
				f1=0;
				break;
			}
		for(ll i=0;i<4;i++)
			if(op[(i+3)&3]!=((op[i]+1)&3)){
				f2=0;
				break;
			}
		if(f1||f2){
			if(len[3]<len[1] || len[2]>len[0])puts("0");
			else printf("%lld\n",len[2]*len[1]);
		}
		else puts("0");
	}
	return 0;
}
