#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(NULL));
	int x[]={1,2,3,4};
	random_shuffle(x,x+4);
	for(int i=0;i<4;i++)
		cout<<x[i];

	return 0;
}
