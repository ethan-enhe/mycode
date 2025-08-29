#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll MXN=1e6+5;
int n,p[MXN];
int _p[MXN];
void mnc(string s){
	string _s="|#";
	for(int i=0;i<s.size();i++)_s+=s[i],_s+='#';
	s=_s;
	int mx=0,id=0;
	for(int i=1;i<s.size();i++){
		p[i]=mx>i?min(p[2*id-i],mx-i):1;
		while(s[i-p[i]]==s[i+p[i]])++p[i];
		if(mx<i+p[i])mx=i+p[i],id=i;
	}
}

int cr[MXN],cl[MXN];
stack<int> stk;
int main(){
	//freopen("test.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	string s;
	cin>>s;
	n=s.size();
	mnc(s);
	for(ll i=1;i<=n*2+1;i++){
		if(i&1){
			_p[i>>1]=(p[i]-1)/2;
		}
	}
	auto rng=[&](int i){
		return pair<int,int> {i-_p[i]+1,i+_p[i]};
	};
	for(int i=n;i;i--){
		stk.push(i);
		while(!stk.empty() && rng(stk.top()).first>i)stk.pop();
		cr[i]=stk.empty()? 1e9:stk.top();
	}
	while(!stk.empty())stk.pop();
	stk.push(0);
	for(int i=1;i<=n;i++){
		while(!stk.empty() && rng(stk.top()).second<i)stk.pop();
		cl[i]=stk.empty()? -1e9:stk.top();
		stk.push(i);
	}

	int l=1,r=n;

	while(1){
		if(cr[l]*2-l+1<=r)l=cr[l]+1;
		else if(cl[r]*2-r>=l)r=cl[r];
		else break;
	}
	cout<<r-l+1;

	return 0;
}

