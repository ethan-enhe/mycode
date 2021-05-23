#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull; 
inline int popcnt(ull x){
	int res=0;
	while(x){
		res+=x&1;
		x>>=1;
	}
	return res;
}
int main(){
	srand(time(NULL));
	cout<<"{\n";
	for(int i=1;i<15;i++){
		cout<<"\t{";
		for(int i=1;i<15;i++)
			cout<<(((ull)rand()<<33)^((ull)rand()<<10)^(ull)rand())<<",";
		cout<<(((ull)rand()<<33)^((ull)rand()<<10) ^rand())<<"},\n";
	}
	cout<<"\t{";
	for(int i=1;i<15;i++)
		cout<<(((ull)rand()<<33)^((ull)rand()<<10) ^rand())<<",";
	cout<<(((ull)rand()<<33)^((ull)rand()<<10) ^rand())<<"}\n}";
	return 0;
}
