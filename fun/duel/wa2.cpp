#include <bits/stdc++.h>
using namespace std;
char s[3000];
int n, m;
struct Node {
    bitset<3000> num;
    bitset<1000> gen;
    bool operator<(const Node &rhs) const { return num.count() > rhs.num.count(); }
} a[1000];
int main() {
    scanf("%d", &n);
    m = 3 * (n - 1);
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        a[i].num = bitset<3000>(s);
        a[i].gen[i] = 1;
    }
    for (int i = 0; i < n; ++i) {
        int cur = -1;
        for (int k = 0; k < m; ++k)
            if (a[i].num.test(k)) {
                cur = k;
                break;
            }
        if (cur == -1) continue;
        for (int j = 0; j < n; ++j) {
            if (i == j || !a[j].num.test(cur)) continue;
            a[j].num ^= a[i].num;
            a[j].gen ^= a[i].gen;
        }
    }
    sort(a, a + n);
    bitset<3000> tmp;
    bitset<1000> ans;
    for (int i = 0; i < n; ++i) {
        cerr << a[i].num.count() << " ";
        tmp ^= a[i].num;
        ans ^= a[i].gen;
        int cnt = tmp.count();
        if (n <= cnt && cnt <= 2 * (n - 1)) break;
    }
    printf("%d\n", ans.count());
    for (int i = 0; i < n; ++i)
        if (ans.test(i)) printf("%d ", i + 1);
    return 0;
}
