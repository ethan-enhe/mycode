#include <bits/stdc++.h>

#include "testlib.h"

using namespace std;
const int MXN = 2e7;
int arr[MXN], brr[MXN];
int main(int argc, char **argv) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    registerGen(argc, argv, 1);

    const int Q = opt<int>(1);
    const int N = 1 << Q;

    for (int i = 0; i < N; i++) arr[i] = 1 + __builtin_popcount(i) % 2;
    for (int i = 0; i < N; i++) brr[i] = 2 - __builtin_popcount(i) % 2;
    cout << N * 3 << '\n';
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    for (int i = 0; i < N; i++) {
        cout << brr[i] << " ";
    }
    for (int i = 0; i < N; i++) {
        cout << arr[i];
        if (i < N - 1) cout << " ";
    }
    cout << '\n';
    return 0;
}

