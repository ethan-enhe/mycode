#include <bits/stdc++.h>

using namespace std;
const int MXN = 1e6 + 5;
int n, arr[MXN], pointedby[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        pointedby[arr[i]] = i;
    }
    int last = -1;
    for (int i = 1; i <= n; i++)
        if (pointedby[i]) last = pointedby[i];
    for (int i = 1; i <= n; i++)
        if (pointedby[i]) {
            arr[pointedby[i]] = -1;
            int tmp = pointedby[i];
            pointedby[i] = last;
            if (tmp == last) {
                cerr << "invalid";
                return 0;
            }
            last = tmp;
        }
    int ind = 1;
    for (int i = 1; i <= n; i++)
        if (arr[i] != -1) {
            while (pointedby[ind]) ++ind;
            pointedby[ind] = i;
        }
    for (int i = 1; i <= n; i++) cout << pointedby[i] << "->" << i << '\n';
    return 0;
}
