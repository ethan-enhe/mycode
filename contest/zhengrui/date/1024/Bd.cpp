#include<iostream>
#include<cstdio>
using namespace std;
char prob[100];
int main(){
	int t=1000;
	while(t--){
		system("./gen");
		system("./bf");
		system("./B");
		if(system("diff B.out Bf.out -Z -B -q")){
			break;
		}
		else printf("AC %d\n",t);
	}
	return 0;
}

