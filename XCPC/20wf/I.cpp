#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll MXN=2005;
const ll NR=MXN*MXN;
ll n,v,c,s;
struct quest{
	ll x,d;
}arr[MXN];

bitset<NR> f,mask;

int main(){
	//freopen("test.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>v>>c;
	for(ll i=1;i<=n;i++){
		cin>>arr[i].x>>arr[i].d;
		s+=arr[i].x;
		arr[i].d=min(NR-10,(arr[i].d*v+c-1)/c);
		//cerr<<arr[i].x<<" "<<arr[i].d<<endl;
	}
	sort(arr+1,arr+1+n,[](auto x,auto y){
			return x.d+x.x<y.d+y.x;
		});
	mask.set();
#define pre(i) (mask>>(NR-(i)-1))
	f[0]=1;
	for(ll i=1;i<=n;i++){
		f|=(f&pre(arr[i].d-1))<<arr[i].x;
	}
	for(ll i=NR-1;~i;i--)
		if(f[i]){
			cout<<s+i*(c-1);
			break;
		}
	return 0;
}


