#include "graph.h"
#include <bits/stdc++.h>
using namespace std;

const int MXN=1005;
bool e[MXN][MXN];
vector<int> check_graph(int n, int limit){
	int a,b,c=-1;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			e[i][j]=e[j][i]=query_edge(i,j);
	for(int i=1;i<=n;i++){
		int cnt=0,last;
		for(int j=1;j<=n;j++)
			if(j!=i && !e[i][j]){
				cnt++;
				last=j;
			}
		if(cnt==1){
			a=last;
			c=i;
			break;
		}
	}
	for(int i=1;i<=n;i++)
		if(i!=a &&  e[a][i])
			b=i;

	for(int i=1;i<=n;i++)
		if(i!=b && e[a][i])
			return vector<int>{};
	for(int i=1;i<=n;i++)
		if(i!=a && i!=c && e[b][i])
			return vector<int>{};
	return vector<int>{a,b,c};
}
