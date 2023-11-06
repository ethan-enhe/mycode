#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

const ll MXN=5e4+5;
ll n,m,arr[MXN],cnt[MXN];
pair<ll,ll> ans[MXN];
ll lind=1,rind,res;
struct que{
	ll l,r,id;
	bool operator < (const que &b)const{
		ll ba=l>>8,bb=b.l>>8;
		return ba==bb?(ba&1?r>b.r:r<b.r):ba<bb;
	}
}ask[MXN];
inline ll gcd(ll a,ll b){return a?gcd(b%a,a):b;}
int main(){
	qio>>n>>m;
	for(int i=1;i<=n;i++)qio>>arr[i];
	for(int i=1;i<=m;i++)ask[i].id=i,qio>>ask[i].l>>ask[i].r;
	sort(ask+1,ask+1+m);
	for(int i=1;i<=m;i++){
		while(rind<ask[i].r)res+=cnt[arr[++rind]]++;
		while(lind>ask[i].l)res+=cnt[arr[--lind]]++;
		while(rind>ask[i].r)res-=--cnt[arr[rind--]];
		while(lind<ask[i].l)res-=--cnt[arr[lind++]];
		ans[ask[i].id].first=res;
		ans[ask[i].id].second=(ask[i].r-ask[i].l)*(1+ask[i].r-ask[i].l)>>1;
	}
	for(int i=1;i<=m;i++){
		if(ans[i].first){
			ll tmp=gcd(ans[i].first,ans[i].second);
			qio<<ans[i].first/tmp<<'/'<<ans[i].second/tmp<<'\n';
		}
		else qio<<"0/1\n";
	}
	return 0;
}
