#include <bits/stdc++.h>
using namespace std;

//{{{ Fast IO
namespace fio {
const int BS = 1 << 20;
char ibuf[BS], *ip1 = ibuf, *ip2 = ibuf;
char obuf[BS], *op = obuf;
#define gc() (ip1 == ip2 && (ip2 = (ip1 = ibuf) + fread(ibuf, 1, BS, stdin), ip1 == ip2) ? EOF : *ip1++)
#define flsh() (fwrite(obuf, 1, op - obuf, stdout), op = obuf)
#define pc(x) (*op++ = (x), op == obuf + BS && flsh())
struct flusher {
    inline ~flusher() { flsh(); }
} tmp;

template <class T>
inline void read(T &x) {
    bool f = 0;
    x = 0;
    char c;
    while (c = gc(), !isdigit(c))
        if (c == '-') f = 1;
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
    if (f) x = -x;
}
inline void read(char &x) {
    while (x = gc(), isspace(x))
        ;
}
inline void read(char *x) {
    while (*x = gc(), isspace(*x))
        if (*x == EOF) return;
    while (*++x = gc(), !isspace(*x) && *x != EOF)
        ;
    *x = 0;
}
template <class T>
inline void prt(T x) {
    if (x < 0) pc('-'), x = -x;
    if (x > 9) prt(x / 10);
    pc(x % 10 ^ 48);
}
inline void prt(const char x) { pc(x); }
inline void prt(char *x) {
    while (*x) pc(*x++);
}
inline void prt(const char x[]) {
    for (int i = 0; x[i]; i++) pc(x[i]);
}
#undef gc
#undef pc
#undef flsh
} // namespace fio

void prt() {}
template <typename T1, typename... T2>
void prt(const T1 x, const T2... y) {
    fio::prt(x);
    prt(y...);
}
void read() {}
template <typename T1, typename... T2>
void read(T1 &x, T2 &... y) {
    fio::read(x);
    read(y...);
}
//}}}

typedef pair<int, int> pi;
const int LG = 21, MXN = 1 << LG;
int n, ans, arr[MXN];
pi mxi[MXN];
void upd(pi &x, int y) {
    if (y > x.first) {
        x.second = x.first;
        x.first = y;
    } else if (y > x.second)
        x.second = y;
}
void upd(pi &x, pi &y) {
    if (y.first > x.first) {
        if (y.second > x.first)
            x = y;
        else
            x.second = x.first, x.first = y.first;
    } else if (y.first > x.second)
        x.second = y.first;
}
int main(int argc, char *argv[]) {
    read(n);
    for (int i = 1; i <= n; i++) {
        read(arr[i]);
        upd(mxi[arr[i]], i);
    }
    for (int i = 1; i < MXN; i <<= 1)
        for (int j = 0; j < MXN; j++)
            if (!(j & i)) upd(mxi[j], mxi[j ^ i]);
    for (int i = 1; i + 2 <= n; i++) {
        int mn = 0;
        for (int j = MXN >> 1; j; j >>= 1)
            if (!(arr[i] & j) && mxi[mn ^ j].second > i) mn ^= j;
        ans = max(ans, mn ^ arr[i]);
    }
    prt(ans);
    return 0;
}
