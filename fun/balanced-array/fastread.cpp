#include <bits/stdc++.h>

#include <cctype>
namespace fio {
const int BS = 1 << 20;
char ibuf[BS], *ip1 = ibuf, *ip2 = ibuf;
#define gc() (ip1 == ip2 && (ip2 = (ip1 = ibuf) + fread(ibuf, 1, BS, stdin), ip1 == ip2) ? EOF : *ip1++)

inline bool is62d(char c) { return isdigit(c) || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
inline int c2i(char c) {
    if (isdigit(c)) return c - '0';
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    return c - 'A' + 36;
}
template <class T>
inline void read(T &x) {
    x = 0;
    char c;
    while (c = gc(), !is62d(c))
        ;
    while (isdigit(c)) x = x * 62 + c2i(c), c = gc();
}
#undef gc
#undef pc
#undef flsh
} // namespace fio
int main() {}
