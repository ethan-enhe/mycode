#include <bits/stdc++.h>
#include <ctime>

#include "tp.h"
using namespace std;
typedef long long ll;
int main() {
    /* ThreadPool pool(4); */
    /* std::vector<std::future<ll>> results; */
    ll MXN = 200000000, P = 1e9 + 7;

    ll st=clock();
    /* for (int i = 0; i < 4; ++i) { */
    /*     results.emplace_back(pool.enqueue( */
    /*         [](ll l, ll r, ll P) -> ll { */
    /*             ll res = 1; */
    /*             for (int i = l; i <= r; i++) res = res * i % P; */
    /*             return res; */
    /*         }, */
    /*         MXN* i + 1, MXN * (i + 1), P)); */
    /* } */

    ll ans=1;
    for(int i=1;i<=4*MXN;i++)
        ans=ans*i%P;
    /* for (auto&& result : results) ans=ans*result.get()%P; */
    cout<<ans<<endl;
    cout<<double(clock()-st)/CLOCKS_PER_SEC;
    return 0;
}
