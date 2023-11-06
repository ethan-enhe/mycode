#include <bits/stdc++.h>
using namespace std;
const int MXN = 1e5 + 5;
int n;
int arr[MXN];
map<int, vector<int>> d;
vector<int> brr;
void fac(int x) {
    vector<int> tmp;
    for (int i = 1; i * i <= x; i++)
        if (x % i == 0) {
            tmp.push_back(i);
            if (i * i != x) tmp.push_back(x / i);
        }
    d[x] = tmp;
}

int tmp[100];
bool dfs(int i, int j) {
    if (i == -1) {
        return 1;
    }
    int save;
    for (int k = 1; k <= j; k++)
        for (int l : d[tmp[k]]) {
            if ((l - 1) * (tmp[k] / l - 1) != brr[i]) continue;
            save = tmp[k];
            tmp[j + 1] = tmp[k] / l;
            tmp[k] = l;
            if (dfs(i - 1, j + 1)) return 1;
            tmp[k] = save;
        }
    return 0;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        if (i > 1 && arr[i] - arr[i - 1] != -1) brr.push_back(arr[i] - arr[i - 1] + 1);
    }
    fac(arr[n]);
    for (auto &i : d[arr[n]])
        if (i != arr[n]) fac(i);

    tmp[1] = arr[n];
    cout << dfs((int)brr.size() - 1, 1);

    return 0;
}
