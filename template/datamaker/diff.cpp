#include<iostream>
#include<cstdio>
#include<windows.h>
using namespace std;
char prob[100];
int main(){
	while(1){
		system("./gen > test.in");
		system("./std < test.in > std.out");
		system("./force < test.in > force.out");
		if(system("diff force.out std.out -Z -B -q")){
			puts("\n---\ndata:");
			system("cat test.in");
			puts("\n---\nforce:");
			system("cat force.out");
			puts("\n---\nstd:");
			system("cat std.out");
			break;
		}
		else printf("AC\n");
	}
	return 0;
}
