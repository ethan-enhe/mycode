#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int NMAX=3e5+5, MOD=998244353;

mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> rnd(0,LLONG_MAX);

ll fact[NMAX], invfact[NMAX], C[NMAX];

ll binPow(ll x, ll y){
    ll ans=1;
    for(;y ;y>>=1, x = x*x%MOD)
        if(y&1)
            ans = ans*x%MOD;
    return ans;
}
map<ll,ll> diff,freq;
void add_interval(ll l, ll r){
    ll Hash = rnd(gen);
    diff[l] ^= Hash, diff[r+1] ^= Hash;
}
void tc(){
    ll n,k;
    cin>>n>>k;
    diff.clear(), freq.clear();
    add_interval(1,n); /// the initial string must be an RBS

    for(ll i=0;i<k;i++){
        ll l,r;
        cin>>l>>r;
        add_interval(l,r);
    }
    ll Hash = diff[1];

    for(map<ll,ll> :: iterator it=next(diff.begin()); it!=diff.end(); it++){
        freq[Hash] += it->first - prev(it)->first;
        Hash ^= it->second;
    }

    ll ans=1;

    for(const auto& it : freq)
        ans=ans*C[it.second]%MOD;

    cout<<ans<<'\n';
}

int main()
{
    fact[0] = invfact[0] = 1;
    for(ll i=1; i<NMAX; i++){
        fact[i] = fact[i-1] * i % MOD;
        invfact[i] = binPow(fact[i], MOD - 2);
    }

    for(ll i=0; i*2<NMAX; i++) C[i*2] = fact[i*2] * invfact[i] % MOD * invfact[i+1] % MOD;

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll t;
    cin>>t;
    while(t--)
        tc();
    return 0;
}
