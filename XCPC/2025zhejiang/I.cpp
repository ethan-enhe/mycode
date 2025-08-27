#include<bits/stdc++.h>
using namespace std;
int t;
int getseg(string &s){
	string tmp;
	int res=0;
	bool f=0;
	for(auto c:s){
		if(f)tmp+=c;
		else if(c>='0' && c<='9')
			res=res*10+c-'0';
		else
			f=1;
	}
	s=tmp;
	return res;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--){
		string a,b;
		cin>>a>>b;
		int diff=0;
		while(!a.empty() && !b.empty()){
			int x=getseg(a),y=getseg(b);
			if(x>y)diff=1;
			if(y>x)diff=-1;
			if(diff)break;
		}
		if(diff==1)cout<<'A'<<endl;
		else if(diff==-1)cout<<'B'<<endl;
		else cout<<"Equal"<<endl;
	}
	
	return 0;
}
