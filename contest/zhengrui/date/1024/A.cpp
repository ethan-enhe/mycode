#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=1e5+5,P=998244353;
struct point{
	ll id,x,y,ty;
	inline bool operator < (const point &b)const{return x<b.x;}
}arr[MXN];
ll n,pool[MXN],ans[MXN];
struct tarr{
	ll s[MXN];
	inline void clr(){memset(s,0,sizeof(s));}
	inline void mod(ll x,ll y){
		y%=P;
		for(;x<=n;x+=x&(-x))
			s[x]=(s[x]+y)%P;
	}
	inline ll sum(ll x){
		ll r=0;
		for(;x;x^=x&(-x))
			r=(r+s[x])%P;
		return r;
	}
}cnt,sx,sy,sxy;
inline void cal(){
	ll x=0,x2=0,y=0,y2=0,xy=0;
	cnt.clr(),sx.clr(),sy.clr(),sxy.clr();
	for(int i=1;i<=n;i++){

		point &cur=arr[i];

		ll tmp=0;
		//(x1-x2)^2=x1^2+x2^2-2x1*x2
		tmp=(tmp+x2+cur.x*cur.x%P*(i-1)-2*x*cur.x)%P;
		tmp=(tmp+y2+cur.y*cur.y%P*(i-1)-2*y*cur.y)%P;
		//
		//y2<y1
		//(x1-x2)(y1-y2)=x1y1-y1x2-x1y2+x2y2
		ll bcnt=cnt.sum(cur.ty),bsx=sx.sum(cur.ty),bsy=sy.sum(cur.ty),bsxy=sxy.sum(cur.ty);
		tmp=(tmp+2*(cur.x*cur.y%P*bcnt-cur.y*bsx-cur.x*bsy+bsxy))%P;
		bcnt=i-1-bcnt,bsx=x-bsx,bsy=y-bsy,bsxy=xy-bsxy;
		tmp=(tmp-2*(cur.x*cur.y%P*bcnt-cur.y*bsx-cur.x*bsy+bsxy))%P;

		ans[cur.id]=(ans[cur.id]+tmp)%P;
		x=(x+cur.x)%P;
		y=(y+cur.y)%P;
		x2=(x2+cur.x*cur.x)%P;
		y2=(y2+cur.y*cur.y)%P;
		xy=(xy+cur.x*cur.y)%P;
		sxy.mod(cur.ty,cur.x*cur.y);
		sx.mod(cur.ty,cur.x);
		sy.mod(cur.ty,cur.y);
		cnt.mod(cur.ty,1);
	}
}

int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&arr[i].x,&arr[i].y);
		pool[i]=arr[i].y;
		arr[i].id=i;
	}
	sort(arr+1,arr+1+n);
	sort(pool+1,pool+1+n);
	for(int i=1;i<=n;i++)
		arr[i].ty=lower_bound(pool+1,pool+1+n,arr[i].y)-pool;
	cal();
	for(int i=1;i<=n;i++)
		arr[i].x=-arr[i].x;
	reverse(arr+1,arr+1+n);
	cal();
	for(int i=1;i<=n;i++)
		printf("%lld\n",(ans[i]%P+P)%P);
	

	return 0;
}
