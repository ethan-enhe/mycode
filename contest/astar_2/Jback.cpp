#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
const ll INF=1e18;
const int MXN=5e5+5;
const int NR=MXN<<2;
const ll P=998244353;
const ll HALF=499122177;
ll qpow(ll x,ll y){
        ll r=1;
        y=(y+P-1)%(P-1);
        while(y){
                if(y&1)r=r*x%P;
                x=x*x%P,y>>=1;
        }
        return r;
}
struct node{
        int pnone,peven;
        node operator + (const node &b)const{
                return node{(ll)pnone*b.pnone%P,((ll)b.peven+(ll)b.pnone*peven)%P};
        }
}t[NR];
#define ls p<<1
#define rs p<<1|1
void build(int p,int l,int r){
        if(l==r){
                t[p]={1,0};
                return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        t[p]=t[ls]+t[rs];
}
int tot[MXN];
void mdf(int p,int l,int r,int mi,int mv){
        if(mi>r || mi<l)return;
        if(l==r){
                tot[l]+=mv;
                if(tot[l]){
                        int tmp=qpow(2,-tot[l]);
                        t[p]={tmp,(HALF-tmp)%P};
                }
                else
                        t[p]={1,0};
                return;
        }
        int mid=(l+r)>>1;
        mdf(ls,l,mid,mi,mv);
        mdf(rs,mid+1,r,mi,mv);
        t[p]=t[ls]+t[rs];
}
node qry(int p,int l,int r,int ql,int qr){
        if(ql>qr || ql>r || qr<l)return node{1,0};
        if(ql<=l && r<=qr)return t[p];
        int mid=(l+r)>>1;
        return qry(ls,l,mid,ql,qr)+qry(rs,mid+1,r,ql,qr);
}


int n;
int ask[MXN][3];
int pool[MXN],m;

int main(){
       freopen("test.in","r",stdin);
       freopen("test.out","w",stdout);
        ios::sync_with_stdio(0); cin.tie(0);
        cin>>n;
        for(int i=1;i<=n;i++){
                cin>>ask[i][0]>>ask[i][1]>>ask[i][2];
                if(ask[i][0]==1)pool[++m]=ask[i][1];
        }
        sort(pool+1,pool+1+m);
        m=unique(pool+1,pool+1+m)-pool-1;
        build(1,1,m);
        for(int i=1;i<=n;i++){
               // cin>>ask[i][0]>>ask[i][1]>>ask[i][2];
                if(ask[i][0]==1){
                        int x=lower_bound(pool+1,pool+1+m,ask[i][1])-pool;
                        mdf(1,1,m,x,ask[i][2]);
                }
                else{
                        int l=lower_bound(pool+1,pool+1+m,ask[i][1])-pool;
                        int r=upper_bound(pool+1,pool+1+m,ask[i][2])-pool-1;
                        node res=qry(1,1,m,l,r);
                        int ans=((1ll-res.pnone-res.peven)%P+P)%P;
                        cout<<ans<<'\n';

                }
        }
        return 0;
}
