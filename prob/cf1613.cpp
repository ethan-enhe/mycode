#include <bits/stdc++.h>

using namespace std;
template <class T>
struct myvec {
    T *v;
    int sz, dsz;
    myvec() { v = NULL, sz = dsz = 0; }
    ~myvec() { free(v); }
    operator T *() const { return v; }
    void rsz(int x) { v = (T *)realloc(v, sizeof(T) * (dsz = sz = x)); }
    void pb(T x) {
        if (sz == dsz) v = (T *)realloc(v, sizeof(T) * (dsz = dsz << 1 | 1));
        v[sz++] = x;
    }
    void fill(T x) {
        for (int i = 0; i < sz; i++) v[i] = x;
    }
};
#define fi first
#define se second
typedef pair<int, int> pi;
pi operator+(const pi &x, const pi &y) { return pi{x.fi + y.fi, x.se + y.se}; }
const int MXN = 1e6 + 5;
const pi go[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
myvec<char> mp[MXN];
myvec<bool> vis[MXN];
int t, n, m;
pi l;
bool chk(pi x) {
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        pi nx = x + go[i];
        if (mp[nx.fi][nx.se] == '#') continue;
        if (!vis[nx.fi][nx.se]) cnt++;
    }
    return cnt <= 1;
}
queue<pi> q;

int main() {
    vis[0].rsz(3);
    vis[0].fill(0);
    cout << vis[0][0];
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        // for(int i=0;i<=n+1;i++){
        //	mp[i].rsz(m+5);
        //	vis[i].rsz(m+5);
        //	vis[i].fill(0);
        //}
        /*
        for(int i=1;i<=n;i++){
            scanf("%s",mp[i]+1);
            mp[i][0]=mp[i][m+1]='#';
            for(int j=1;j<=m;j++)
                if(mp[i][j]=='L')
                    l={i,j};
        }
        mp[0].fill('#');
        mp[n+1].fill('#');
        vis[l.fi][l.se]=1;
        q.push(l);
        while(!q.empty()){
            pi p=q.front();q.pop();
            for(int i=0;i<4;i++){
                pi nx=p+go[i];
                if(mp[nx.fi][nx.se]=='#' || vis[nx.fi][nx.se])continue;
                if(!chk(nx))continue;
                vis[nx.fi][nx.se]=1;
                q.push(nx);
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                if(vis[i][j]){
                    cout<<"1";
                }
                else cout<<"0";
            cout<<endl;
        }
        */
    }
    return 0;
}
