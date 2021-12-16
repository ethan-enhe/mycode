#include<cstdio>
#include<vector>
#include<stack>
#include<queue>
#include<iostream>
#include<cstring>
#include<algorithm>
#define maxn 1000010
using namespace std;
struct chr{
    int to;
};
vector<chr> ve[maxn];
stack<int> st;
queue<int> q;
int num[maxn];
int znum[maxn];
int ltk[maxn];
bool sjb[maxn];
int dfn[maxn];
int low[maxn];
bool vis[maxn];
int dis[maxn];
bool zzl[maxn];
int pos=0,re=0;
void add(int from,int to){
    chr x;
    x.to=to;
    ve[from].push_back(x);
}
void tarjan(int now){
    pos++;
    low[now]=dfn[now]=pos;
    st.push(now);
    zzl[now]=1;
    int size=ve[now].size();
    for(int i=0;i<size;i++){
        int next=ve[now][i].to;
        if(!dfn[next]){
            tarjan(next);
            low[now]=min(low[now],low[next]);
        }
        else if(zzl[next])
            low[now]=min(low[now],low[next]);
    }
    if(low[now]==dfn[now]){
        re++;
        int Cnow=0;
        while(Cnow!=now){
            Cnow=st.top();
            st.pop();
            zzl[Cnow]=0;
            znum[re]+=num[Cnow];
            ltk[Cnow]=re;
        }
    }
}
void makepoint(int &n,int zn){
    n++;
    num[n]=zn;
}
void spfa(int now){
    vis[now]=true;
    q.push(now);
    dis[now]=num[now];
    while(!q.empty()){
        now=q.front();
        q.pop();
        vis[now]=0;
        int size=ve[now].size();
        for(int i=0;i<size;i++){
            int next=ve[now][i].to;
            if(dis[now]+num[next]>dis[next])
        
            {dis[next]=dis[now]+num[next];
            if(!vis[next]){
                q.push(next);
                vis[next]=1;
            }}
        }
    }
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int from,to;
        scanf("%d %d",&from,&to); 
        add(from,to);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&num[i]);
    }
    int s,p;
    cin>>s>>p;
    for(int i=1;i<=p;i++){
        int t;
        scanf("%d",&t);
        sjb[t]=true;
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i);
    }
    int pos=n;
    for(int i=1;i<=re;i++){
        makepoint(pos,znum[i]);
    }
    for(int now=1;now<=n;now++){
        int size=ve[now].size();
        if(sjb[now]){
            sjb[n+ltk[now]]=true;
        }
        for(int i=0;i<size;i++){
            int next=ve[now][i].to;
            if(ltk[now]!=ltk[next]){
                add(ltk[now]+n,ltk[next]+n);
            }
        }
        ve[now].clear();
    }
    spfa(n+ltk[s]);
    int ou=0;
    for(int i=n+1;i<=n+re;i++){
        if(sjb[i])
            ou=max(ou,dis[i]);
    }
    cout<<ou<<endl;
    return 0;
}
