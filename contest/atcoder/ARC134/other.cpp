//#pragma GCC optimize("Ofast", "unroll-loops")
//#pragma GCC target("sse", "sse2", "sse3", "ssse3", "sse4", "avx")
#include <bits/stdc++.h>
#define ll long long
#define int long long
#define ull unsigned long long
#define YES puts("YES")
#define NO puts("NO")
#define Yes puts("Yes")
#define No puts("No")
#define edl puts("")
#define mc cerr<<"qwq\n"
#define error goto gg
#define def gg:
#define rd(x) x=read()
#define opl(x) printf("%lld",x)
#define opls(x) printf("%lld ",x)
#define opd(x) printf("%d",x)
#define opds(x) printf("%d ",x)
#define ver(x) for(int i=head[x];i;i=nxt[i])
#define up(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define pu(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define ft(x) for(int i=head[x];i;i=nxt[i])
#define upn up(i,1,n)
#define upm up(j,1,m)
#define pun pu(i,n,1)
#define pum pu(j,m,1)
#define up_(x) up(i,1,x)
#define pu_(x) pu(j,x,1)
#define ep emplace_back
#define fp for(auto to:
#define pf )
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
#define mkp make_pair
#define fi first
#define se second
#define mii map<int,int>
#define mis map<int,string>
#define msi map<string,int>
#define mvi map<vector<int>,int>
#define miv map<int,vector<int>>
#define rdn rd(n)
#define rdm rd(m)
#define rdk rd(k)
using namespace std;
int n, m, k;
int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}

#define inf 1000000000000000000ll
ll Max(ll a=-inf,ll b=-inf,ll c=-inf,ll d=-inf,ll e=-inf,ll f=-inf,ll g=-inf,ll h=-inf)
{
	return max(max(max(a,b),max(c,d)),max(max(e,f),max(g,h)));
}
ll Min(ll a=inf,ll b=inf,ll c=inf,ll d=inf,ll e=inf,ll f=inf,ll g=inf,ll h=inf)
{
	return min(min(min(a,b),min(c,d)),min(min(e,f),min(g,h)));
}
#undef inf
int a[202020];
int p[202020];
struct node
{
	int l,r;
}c[202020];
int cmp(node a,node b)
{
	return a.l==b.l?a.r<b.r:a.l<b.l;
}
signed main()
{
	int T=1;
	while(T--)
	{
		rdn;
		up_(n+n)rd(a[i]);
		upn c[i]=(node){a[i],a[i+n]};
		sort(c+1,c+n+1,cmp);
		if(c[1].r<=c[1].l)
		{
			cout<<c[1].l<<" "<<c[1].r;return 0;
		}
		int mx=Min();
		upn mx=min(mx,a[i]);
		int w=Min();
		upn
		{
			if(a[i]==mx)
			{
				if(a[i+n]<a[i])
				{
					w=min(w,a[i+n]);
				}
			}
		}
		if(w!=Min())
		{
			cout<<mx<<" "<<w;return 0;
		}
		upn
		{
			if(a[i]==mx)
			{
				if(a[i+n]==a[i])
				{
					cout<<a[i]<<" "<<a[i+n];edl;
					return 0;
				}
			}
		}
		int pos=0;
		vector<int>ans;
		upn
		{
			if(a[i]==mx)
			{
				pos=i;ans.ep(i);
			}
		}
		p[n]=n;
		pu(i,n-1,1)
		{
			if(a[i]<a[p[i+1]])p[i]=i;
			else p[i]=p[i+1];

		}
		int nw=pos+1;
		while(1)
		{
			if(nw>n)break;
			if(a[p[nw]]<a[ans[0]+n])
			{
			//	mc;
				ans.ep(p[nw]);
				nw=p[nw]+1;
			}
			else if(a[p[nw]]==a[ans[0]+n])
			{
				if(ans.size()==1)
				{
					break;
				}
				else
				{
					if(a[p[nw]]<a[ans[1]+n])
					{
						ans.ep(p[nw]);
						nw=p[nw]+1;
					}
					else
					{
						break;
					}
				}
			}
			else break;
			if(nw>n)break;

		}
		fp ans pf opds(a[to]);
		fp ans pf opds(a[to+n]);
	}
}
/*
  When you are coding,remember to:
	   - clear the arrays if a problem has many tasks.
	   - pay attention to some special cases(n=0,1).
	   - Don't code before think completely.
	   - ...
*/

