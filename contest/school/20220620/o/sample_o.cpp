#include "o.h"

void solve(int task_id, int N, int K, int ans[]) {
	for (int i = 0; i < N; ++i) ans[i] = 0; 	

	if (K == 0) {
		ans[0] = ans[1] = 1;
	} else {
		int arr[5], brr[5];
		arr[0] = 0;
		brr[0] = 1;
		if (query(arr, 1, brr, 1) == 0) {
			ans[0] = 1;
		} else {
			ans[1] = 1;
		}
	}
}
