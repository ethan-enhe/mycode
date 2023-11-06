#include <bits/stdc++.h>

using namespace std;
const int MXN = 5e4 + 5;
int n, m, t;
pair<int, int> arr[MXN];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d%d", &arr[i].second, &arr[i].first);
        sort(arr + 1, arr + 1 + n);
        bool f = 0;
        for (int i = 2; i <= n; i++)
            if (arr[i].second < arr[i - 1].second) {
                puts("-1");
                f = 1;
				break;
            }
        if (f) continue;
        while (n) printf("%d ", arr[n--].second);
		putchar('\n');
    }

    return 0;
}
