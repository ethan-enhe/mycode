#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rd scanf
#define pt printf
#define setp(x) setprecision(x)
#define mem(x,y) memset(x,y,sizeof(x))
#define sz(x) (int)x.size()
#define umn(x,y) x=min(x,y)
#define umx(x,y) x=max(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pi;
typedef queue<ll> qi;
typedef vector<ll> vi;
typedef vector<pi> vpi;

const ll INF=1e18;
const ll P=1e9+7;
const ll MXN=1e5+5;

inline ll mod(ll x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}
// luogu-judger-enable-o2
#include<iostream>
#include<cstdio>
using namespace std;
const int NR=500000;
struct SegmentTree{
    long long t[NR],tag[NR];
    //返回左右儿子
    inline int ls(int p){return p<<1;}
    inline int rs(int p){return p<<1|1;}
    //向上更新
    inline void push_up(int p){t[p]=max(t[ls(p)],t[rs(p)]);}
    void build(int p,int l,int r){
        //区间为一个数，是叶子节点
        //叶子节点赋值
        tag[p]=0;
        if(l==r){
            t[p]=0;
            return;
        }
        int mid=l+((r-l)>>1);
        build(ls(p),l,mid);
        build(rs(p),mid+1,r);
        push_up(p);
    }
    inline void add_tag(int p,int l,int r,int k){
        tag[p]+=k;//记录懒标记，过后向下更新
        t[p]+=k;//范围l-r的每个叶子都加k
    }
    inline void push_down(int p,int l,int r){//向下更新
        int mid=l+((r-l)>>1);
        add_tag(ls(p),l,mid,tag[p]);
        add_tag(rs(p),mid+1,r,tag[p]);
        tag[p]=0;//更新完成，标签可以删了
    }
    void update(int p,int l,int r,int add_l,int add_r,int k){
        /*
         * @p当前节点
         * @l,r当前节点范围
         * @add_l,add_r操作的范围
         * @k操作的值
         */
		if(add_l>add_r)return;
        if(add_l<=l && r<=add_r){//操作范围大于该节点，说明该节点不可分解了
            add_tag(p,l,r,k);
            return;
        }
        push_down(p,l,r);
        int mid=l+((r-l)>>1);
        if(add_l<=mid)update(ls(p),l,mid,add_l,add_r,k);//更新左儿子
        if(add_r>mid)update(rs(p),mid+1,r,add_l,add_r,k);//更新右儿子
        push_up(p);
    }
    long long query(int p,int l,int r,int que_l,int que_r){
        long long res=-INF;
        if(que_l<=l && r<=que_r)return t[p];
        int mid=l+((r-l)>>1);
        //向下更新标签，避免得到的结果是未更新的
        push_down(p,l,r);
        if(que_l<=mid)umx(res,query(ls(p),l,mid,que_l,que_r));
        if(que_r>mid)umx(res,query(rs(p),mid+1,r,que_l,que_r));
        return res;
    }
};
SegmentTree v;

ll n,m,k;
ll arr[MXN],brr[MXN],pre[MXN],dp[MXN];
stack<ll> st;
inline void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>arr[i];
	for(int i=1;i<=n;i++)cin>>brr[i];
	arr[0]=-INF;
	st.push(0);
	v.build(1,0,n);
	for(int i=1;i<=n;i++){
		while(arr[st.top()]>arr[i]){
			v.update(1,0,n,pre[st.top()],st.top()-1,-brr[st.top()]);
			st.pop();
		}
		pre[i]=st.top();
		v.update(1,0,n,pre[i],i-1,brr[i]);
		st.push(i);
		dp[i]=v.query(1,0,n,0,i-1);
		v.update(1,0,n,i,i,dp[i]);
		//for(int j=0;j<=i;j++)cout<<v.query(1,0,n,j,j)<<" ";
		//cout<<endl;
	}
	cout<<dp[n];


    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios_base::sync_with_stdio(0);cin.tie(0);
	cout<<setiosflags(ios::fixed);
	srand(time(NULL));

	ll tq=1;
	//cin>>tq;
	while(tq--)solve();
	return 0;
}
