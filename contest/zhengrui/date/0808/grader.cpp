#include "graph.h"
#include <set>
#include <utility>
#include <cstdio>
#include <algorithm>

namespace grader
{

static int N, M, limit, used;
static std::set<std::pair<int, int> > edges;

static bool QUERY_EDGE(int u, int v)
{
	// printf("query %d %d\n", u, v);
	if(u < 1 || v < 1 || u > N || v > N)
	{
		puts("query out of bound.");
		exit(0);
	}
	used++;
	if(used > limit)
	{
		puts("query limit exceeded.");
		exit(0);
	}
	if(u > v) std::swap(u, v);
	
	return edges.count(std::pair<int, int>(u, v));
}

static int MAIN()
{
	scanf("%d%d%d", &N, &M, &limit);
	for(int i=1, u, v; i<=M; i++)
	{
		scanf("%d%d", &u, &v);
		if(u > v) std::swap(u, v);
		edges.emplace(u, v);
	}
	auto ans = check_graph(N, limit);
	if(ans.size() != 0 && ans.size() != 3)
	{
		puts("Wrong return format.");
	}
	else if(ans.size() == 0)
	{
		puts("Not interesting.");
	}
	else
	{
		printf("a= %d, b= %d, c= %d, number of queries= %d\n", ans[0], ans[1], ans[2], used);
	}
	return 0;
}

}

bool query_edge(int u, int v)
{
	return grader::QUERY_EDGE(u, v);
}

int main() { return grader::MAIN(); }

