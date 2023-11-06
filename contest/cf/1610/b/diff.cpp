#include<iostream>
#include<cstdio>
using namespace std;
char prob[100];
int main(){
	int t=100;
	while(t--){
		system("./gen > test.in");
		system("./b < test.in > std.out");
		system("./bf < test.in > force.out");
		if(system("diff force.out std.out -Z -B -q")){
			puts("\n---\ndata:");
			puts("\n---\nforce:");
			puts("\n---\nstd:");
			break;
		}
		else printf("AC\n");
	}
	return 0;
}

