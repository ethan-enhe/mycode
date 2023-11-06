#include <bits/stdc++.h>
using namespace std;
const int SZ=1024;

FILE *fp;
inline unsigned char x(int i,int j){return sin(i*M_PI/SZ)*SZ>=j?0:255;}
int main(){
	fp = fopen("pic.ppm","wb");
	fprintf(fp, "P6\n%d %d\n255\n", SZ, SZ);
	for(int j=0;j<SZ;j++)
		for(int i=0;i<SZ;i++)
			fprintf(fp,"%c%c%c",x(i,j),x(i,j),x(i,j));
	fclose(fp);
	return 0;
}
