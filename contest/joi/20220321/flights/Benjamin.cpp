#include "Benjamin.h"

#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define log2(x) (63 - __builtin_clzll(x))
#define popc(x) __builtin_popcountll(x)
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
//}}}

namespace {

ll n, x, y, mrg;

}

std::string SendB(int N, int X, int Y) {
    n = N, x = X, y = Y;
    mrg = (x << 6) ^ (y >> 8);
    return bitset<20>(mrg).to_string();
}

int Answer(std::string T) {
    ll initdis = bitset<14>(T.substr(0, 14)).to_ullong();
    ll yl = (y >> 8);
    yl <<= 8;
    for (ll i = yl + 1; i <= y; i++) {
        initdis += T[14 + i - yl - 1] == '1' ? 1 : -1;
    }
    return initdis;
}
