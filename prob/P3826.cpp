#include<bits/stdc++.h>
using namespace std;

#define il inline
#define pb push_back
typedef long long ll;
typedef vector<ll> vi;
const char nl='\n';

//!!!
const ll MXN=2e5+5,MXM=11;
struct veg_type{
	ll pro;
	mutable ll tot,dec,sold;
	il bool operator < (const veg_type &b)const{return pro>b.pro;}
	il ll cal(ll day)const{return tot-dec*(day-1)-sold;}
}arr[MXN];
ll n,m,k,sold[MXN][MXM],sold_cnt[MXN],vegcnt;
vi new_veg[MXN];

il void add_veg(veg_type x,ll day){
	arr[++vegcnt]=x;
	new_veg[day].pb(vegcnt);
}


multiset<veg_type> avail;
il ll cal(){
	avail.clear();
	ll res=0;
	for(ll cur_day=MXN-1;cur_day;cur_day--){
		for(ll i:new_veg[cur_day])
			avail.insert(arr[i]);
		auto it=avail.begin();
		ll rem=m;
		while(rem && it!=avail.end()){
			ll delt=min(rem,it->cal(cur_day));
			res+=delt*it->pro,rem-=delt;
			it->sold+=delt;
			while(delt--)sold[cur_day][++sold_cnt[cur_day]]=it->pro;
			//if(!it->cal(cur_day) && it->dec==0)avail.erase(it++);
			it++;
		}
	}
	return res;
}
ll ans[MXN];
struct veg{
	ll pro,sold_day,sold_ind;
	il bool operator < (const veg &b)const{
		return pro>b.pro;
	}
};
priority_queue<veg> q;
il void init_ans(){

	ans[MXN-1]=cal();
	for(int i=1;i<MXN;i++){
		//cout<<endl<<i<<endl;
		for(int j=1;j<=m;j++)
			//cout<<sold[i][j]<<" ",
			q.push(veg{sold[i][j],i,j});
	}
	for(int i=MXN-1;i>=1;i--){
		ans[i-1]=ans[i];
		for(int j=1;j<=sold_cnt[i];j++){
			while(!q.empty() && (q.top().pro!=sold[q.top().sold_day][q.top().sold_ind] 
						|| q.top().sold_day>=i))
				q.pop();
			if(sold[i][j]<=q.top().pro)ans[i-1]-=sold[i][j];
			else{
				veg tmp={sold[i][j],q.top().sold_day,q.top().sold_ind};
				sold[tmp.sold_day][tmp.sold_ind]=tmp.pro;
				ans[i-1]-=q.top().pro;
				q.push(tmp);
			}
		}
	}
}



int main(){
#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		ll a,b,c,d;
		cin>>a>>b>>c>>d;
		ll end_day=d?(c+d-1)/d:MXN-1;
		add_veg({a,c-1,d,0},end_day);
		add_veg({a+b,1,0,0},end_day);
	}
	init_ans();
	while(k--){
		ll x;
		cin>>x;
		cout<<ans[x]<<nl;
	}


	return 0;
}

