#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXD=11;
char s1[MXD],s2[MXD];
ll pow10[MXD]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000};
inline ll cal(char *str,ll x){
	ll n=strlen(str+1),ans=0,cnt=0;
	bool f=1;
	for(ll i=1;i<=n;i++){
		ll tmp=str[i]-'0';
		if(tmp)f=0;
		ans+=cnt*tmp*pow10[n-i]+pow10[n-i-1]+(tmp>x?pow10[n-i]:0);
		cnt+=!f && tmp==x;
	}
	return ans+cnt;
}
int main(){
	while(1){
		scanf("%s %s",s1+1,s2+1);
		if(s2[1]==0 && s1[1]==0)return 0;
		ll tmp=strlen(s1+1);
		while(s1[tmp]=='0')s1[tmp--]='9';
		s1[tmp]--;
		cout<<cal(s2,0);
		//for(int i=0;i<=9;i++)printf("%lld ",cal(s2,i)-cal(s1,i));
		putchar('\n');
	}
	return 0;
}
