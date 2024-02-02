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
       freopen("test.in","w",stdout);
        ios::sync_with_stdio(0); cin.tie(0);
		srand(time(0));
		n=5e5;
		cout<<n<<endl;
		while(n--){
			int op=rand()%2+1;
			int x=rand()%1000000000;
			int y=rand()%1000000000;
			if(op==2 && x>y)swap(x,y);
			cout<<op<<" "<<x<<" "<<y<<'\n';
		}
        return 0;
}

