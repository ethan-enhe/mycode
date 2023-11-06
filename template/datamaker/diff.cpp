#include<bits/stdc++.h>
#define sys(fmt...) (sprintf(tmp,fmt),system(tmp))
using namespace std;
const int MXS=10000;
char tmp[MXS];
int main(int argc,char *argv[]){
	if(argc<3 || argc>4){
		puts("Usage: dp <gen> <std> <force>");
		return 0;
	}
	int t=100;
	while(t--){
		cerr<<"!!!"<<endl;
		sys("./%s > test.in",argv[1]);
		cerr<<"!!!"<<endl;
		sys("./%s < test.in > std.out",argv[2]);
		cerr<<"!!!"<<endl;
		if(argc==4)sys("./%s < test.in > force.out",argv[3]);
		if(argc==4 && sys("diff force.out std.out -Z -B -q")){
			puts("\n---\ndata:");
			sys("cat test.in");
			puts("\n---\nforce:");
			sys("cat force.out");
			puts("\n---\nstd:");
			sys("cat std.out");
			break;
		}
		else puts("AC");
	}
	return 0;
}
