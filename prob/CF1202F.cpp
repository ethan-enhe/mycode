#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll MXC=26,MXS=2e5+5;
const char C0='a';
struct AC{
	struct node{
		ll son[MXC],fail,cnt;
	}t[MXS];
	ll nodec,q[MXS],ql=1,qr;
	void ins(char *tmp){
		ll len=strlen(tmp+1),p=0;
		for(ll i=1;i<=len;i++){
			ll &nx=t[p].son[tmp[i]-C0];
			if(!nx)nx=++nodec;
			p=nx;
		}
		t[p].cnt++;
	}
	void build(){
		for(ll i=0;i<MXC;i++)
			if(t[0].son[i])
				q[++qr]=t[0].son[i];
		while(ql<=qr){
			ll p=q[ql++];
			for(ll i=0;i<MXC;i++){
				ll &nx=t[p].son[i],nxf=t[t[p].fail].son[i];
				if(nx){
					t[nx].fail=nxf;
					q[++qr]=nx;
				}
				else nx=nxf;
			}
		}
		for(ll i=1;i<=nodec;i++){
			node &cur=t[q[i]];
			cur.cnt+=t[cur.fail].cnt;
		}
	}
}ori,rev;
ll n,ans,len,arr[MXS];
char str[MXS],tmp[MXS];
int main(){
	scanf("%s%lld",str+1,&n);
	len=strlen(str+1);
	while(n--){
		scanf("%s",tmp+1);
		ori.ins(tmp);
		reverse(tmp+1, tmp+1+strlen(tmp+1));
		rev.ins(tmp);
	}
	ori.build();
	rev.build();
	for(ll i=len,p=0;i;i--){
		p=rev.t[p].son[str[i]-C0];
		arr[i]=rev.t[p].cnt;
	}
	for(ll i=1,p=0;i<=len;i++){
		p=ori.t[p].son[str[i]-C0];
		ans+=ori.t[p].cnt*arr[i+1];
	}
	printf("%lld",ans);


	return 0;
}
