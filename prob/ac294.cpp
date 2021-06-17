#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=105;
const ll LG=30;
ll n1,n2,l1,l2;
char a[MXN],b[MXN];
ll nx[MXN][26],jmp[MXN][LG+1];
inline ll mod(ll x,ll y){return x<y?x:x-y;}
int main(){
	while(scanf("%s%lld %s%lld",b,&n2,a,&n1)!=EOF){
		l1=strlen(a),l2=strlen(b);
		for(ll i=l1-1;~i;i--)
			for(ll j=0;j<26;j++)
				nx[i][j]=1e13;
		for(ll i=l1-1;~i;i--){
			for(ll j=0;j<26;j++)
				nx[i][j]=nx[mod(i+1,l1)][j]+1;
			nx[i][a[i]-'a']=1;
		}
		for(ll i=l1-1;~i;i--){
			for(ll j=0;j<26;j++)
				nx[i][j]=nx[mod(i+1,l1)][j]+1;
			nx[i][a[i]-'a']=1;
		}
		bool f=0;
		for(ll i=0;i!=l1;i++){
			jmp[i][0]=0;
			for(ll j=0;j!=l2;j++)
				jmp[i][0]+=nx[(i+jmp[i][0])%l1][b[j]-'a'];
			if(jmp[i][0]>=1e13){
				f=1;
				break;
			}
		}
		if(f){
			printf("0\n");
			continue;
		}
		for(ll j=1;j<=LG;j++)
			for(ll i=0;i!=l1;i++)
				jmp[i][j]=jmp[i][j-1]+jmp[(i+jmp[i][j-1])%l1][j-1];
		ll tot=0,cnt=0;
		for(ll i=LG;~i;i--)
			if(tot+jmp[tot%l1][i]<=l1*n1){
				tot+=jmp[tot%l1][i];
				cnt+=1ll<<i;
			}
		printf("%lld\n",cnt/n2);
	}
	return 0;
}
