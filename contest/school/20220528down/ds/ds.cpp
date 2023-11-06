#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll P=998244353;
const ll MXN=2e5+5,B=300;
ll n,b,q;
ll arr[MXN],bpw[MXN],ans[MXN];

ll cnt[MXN],b1s;

struct que{
	ll l,r,x,y,id;
	bool operator < (const que &b)const{
		if(l/B==b.l/B)return (l/B&1)?r<b.r:r>b.r;
		else return l/B<b.l/B;
	}
}ask[MXN];


ll pre[MXN];
void add(ll x,ll y){
	for(;x<=n;x+=x&(-x))
		pre[x]+=y;
}
ll sum(ll x){
	ll r=0;
	for(;x;x-=x&(-x))
		r+=pre[x];
	return r;
}

void mod(ll x,ll y){
	if(b==1 && cnt[x])add(x,-x);
	cnt[x]+=y;
	if(b==1 && cnt[x])add(x,x);
}


int main(){
	freopen("ds.in","r",stdin);
	freopen("ds.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>b>>q;
	bpw[0]=1;
	for(ll i=1;i<=n;i++){
		cin>>arr[i];
		bpw[i]=bpw[i-1]*b%P;
	}
	for(ll i=1,l,r,x,y;i<=q;i++){
		cin>>l>>r>>x>>y;
		ask[i]={l,r,x,y,i};
	}
	sort(ask+1,ask+1+q);
	for(ll i=1,l=1,r=0;i<=q;i++){
		while(r<ask[i].r)mod(arr[++r],1);
		while(l>ask[i].l)mod(arr[--l],1);
		while(r>ask[i].r)mod(arr[r--],-1);
		while(l<ask[i].l)mod(arr[l++],-1);
		ll res=0;
		if(b==1)
			res=(sum(ask[i].y)-sum(ask[i].x-1))%P;
		else 
			for(ll j=ask[i].x,rk=0;j<=ask[i].y;j++)
				if(cnt[j]){
					res=(res+j*bpw[rk])%P;
					++rk;
				}
		ans[ask[i].id]=res;
	}
	for(ll i=1;i<=q;i++)
		cout<<ans[i]<<'\n';


	return 0;
}
