#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
template <typename T>
T read() {
    T x{0};
    bool neg{false};
    int ch = getchar();
    while (!isdigit(ch)) {
        neg = ch == '-';
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = 10 * x + ch - '0';
        ch = getchar();
    }
    return neg ? -x : x;
}
using namespace std;
int main() {
    int n = read<int>();
    array<bitset<3008>, 1000> l;
    array<bitset<1000>, 1000> r;
    for (int i = 0; i < n; i++) r[i][i] = 1;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < 3 * n - 3; j++) l[i][j] = s[j] == '1';
    }
    int row = -1;
    for (int col = 0; col < 3 * n - 3; col++) {
        for (int i = row + 1; i < n; i++)
            if (l[i][col]) {
                row++;
                if (i != row) {
                    swap(l[row], l[i]);
                    swap(r[row], r[i]);
                }
                for (int j = 0; j < n; j++)
                    if (j != row && l[j][col]) {
                        l[j] ^= l[row];
                        r[j] ^= r[row];
                    }
                break;
            }
    }
    bitset<3008> prex;
    bitset<1000> res;
    for (int i = n - 1; i >= 0; i--) {
        prex ^= l[i];
        res ^= r[i];
        int cnt = prex.count();
        if (cnt >= n && cnt <= 2 * n - 2) {
            cout << res.count() << '\n';
            for (int j = 0; j < n; j++)
                if (res[j]) cout << j + 1 << ' ';
            break;
        }
    }
    return 0;
}
