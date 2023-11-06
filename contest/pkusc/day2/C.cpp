#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
using pi=pair<ll,ll>;
const char nl='\n';
const ll N=9,T=3,STD=14;
struct card{
	ll cnt[T+1][N+1];
	card(string s=""){
		memset(cnt,0,sizeof(cnt));
		ll tp=1;
		for(char x:s){
			if(isdigit(x))++cnt[tp][x-'0'];
			else ++tp;
		}
	}
};

struct dp{
	bool f[2][4][4][4][4],nx[2][4][4][4][4];
	ll a[5];
	void clr(){
		memset(f,0,sizeof(f));
		f[0][0][0][0][0]=1;
	}
	inline void dfs(ll i,ll x,bool f){
		if(i==5){
			nx[a[0]][a[1]][a[2]][a[3]][a[4]]=1;
			return;
		}
		if(i==0){
			dfs(i+1,x,f);
			if(x>=2 && a[0]==0){
				a[0]=1;
				dfs(i+1,x-2,f);
				a[0]=0;
			}
		}
		else{
			if(a[i]==3)dfs(i+1,x,f);
			else if(a[i]){
				if(x){
					++a[i];
					dfs(i+1,x-1,f);
					--a[i];
				}
			}
			else{
				dfs(i+1,x,0);
				if(x && f){
					++a[i];
					dfs(i+1,x-1,f);
					--a[i];
					if(x>=3){
						a[i]=3;
						dfs(i+1,x-3,f);
						a[i]=0;
					}
				}
			}
		}
	}
	inline void add(ll x){
		memset(nx,0,sizeof(nx));
		for(a[0]=0;a[0]<=1;a[0]++)
			for(a[1]=0;a[1]<=3;a[1]++)
				for(a[2]=0;a[2]<=a[1];a[2]++)
					for(a[3]=0;a[3]<=a[2];a[3]++)
						for(a[4]=0;a[4]<=a[3];a[4]++)
							if(f[a[0]][a[1]][a[2]][a[3]][a[4]])
								dfs(0,x,1);
		memcpy(f,nx,sizeof(f));
	}
	bool ok(){
		return f[1][3][3][3][3];
	}
};

dp _tmp;
bool chk(card x){
	//法2
	ll tmp=0;
	for(ll i=1;i<=T;i++)
		for(ll j=1;j<=N;j++)
			if(x.cnt[i][j]>=2)
				tmp+=2;
	if(tmp>=STD)return 1;
	_tmp.clr();
	for(ll i=1;i<=T;i++){
		for(ll j=1;j<=N;j++)
			_tmp.add(x.cnt[i][j]);
		_tmp.add(0);
	}
	return _tmp.ok();
}


bool dfs(ll dpth,ll lasttp,ll lasti,card &x){
	if(!dpth)
		return chk(x);
	for(ll i=lasttp;i<=T;i++)
		for(ll j=(i==lasttp?lasti:1);j<=N;j++)
			if(x.cnt[i][j]<4){
				++x.cnt[i][j];
				if(dfs(dpth-1,i,j,x))return 1;
				--x.cnt[i][j];
			}
	return 0;
}

card x;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	cin>>s;
	x=card(s);
	for(ll i=0;i<=5;i++)
		if(dfs(i+1,1,1,x)){
			cout<<i;
			break;
		}
	return 0;
}

