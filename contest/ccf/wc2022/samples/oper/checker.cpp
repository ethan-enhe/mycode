/*
 * +++A-B-C-
 *  ++A-B-+C-
 *
 *
 * ++A-+B- C-
 * ++A- B-+C-
 *
 *  +A-++B- C-
 * ++A-  B-+C-
 * +A-+B-+C-
 */
#include <bits/stdc++.h>
#include <bits/types/FILE.h>

#include <cstdio>
using namespace std;
const int MXN = 5e5 + 5;
int id, t, n, k;
char s1[MXN], s2[MXN];
string x, y;
int ind;
int main() {
    FILE *in = fopen("oper2.in", "r"), *out = fopen("oper.out", "r");
    /* freopen("oper1.out","w",stdout); */
    fscanf(in, "%d%d", &id, &t);
    while (t--) {
        fscanf(in, "%d%d %s %s", &n, &k, s1, s2);
        x = y = "";
        for (int i = 0; i < n * 2; i++) {
            x += s1[i];
            y += s2[i];
        }
        /* cout<<x.substr(0,1)<<" "<<y<<endl; */
        int len;
        fscanf(out, "%d", &len);
        assert(len <= k);
        while (len--) {
            int op, l, r;
            fscanf(out, "%d%d%d", &op, &l, &r);
            if (op == 6) {
                /* cerr<<x.size()<<endl; */
                assert(x.size() == l + r + 2);
                /* cerr<<"!!!"<<l<<" "<<r<<endl; */
                assert(x[l] == '(');
                assert(x[l + 1] == ')');
                x = x.substr(0, l) + x.substr(l + 2);
            } else {
                assert(x.size() == l + r);
                x = x.substr(0, l) + "()" + x.substr(l);
            }
        }
        assert(x == y);
        cout << "AC" << endl;
    }

    return 0;
}
