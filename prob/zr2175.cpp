#include <bits/stdc++.h>

using namespace std;
const int MXS = 1e5 + 5, MXP = 1005, MXC = 26;
bitset<MXP> dp[MXS], char_mask[MXC], any_mask;
int n, m;
char str[MXS], pat[MXP];
void init() {
    m = 1;
    for (int i = 2; pat[i]; i++)
        if (pat[i] != '*' || pat[i - 1] != '*') pat[++m] = pat[i];
    if (pat[m] == '*') --m;
    pat[m + 1] = 0;
    /* cout<<(pat+1)<<endl; */
    any_mask.reset();
    for (int i = 0; i < MXC; i++) char_mask[i].reset();
    for (int i = 1; i <= m; i++) {
        if (pat[i] >= 'a' && pat[i] <= 'z')
            char_mask[pat[i] - 'a'][i] = 1;
        else {
            if (pat[i] == '*') any_mask[i] = 1;
            for (int j = 0; j < MXC; j++) char_mask[j][i] = 1;
        }
    }
}
void prt(bitset<MXP> &x) {
    for (int j = 0; j <= m; j++) cout << x[j] << " \n"[j == m];
}
pair<int, int> cal() {
    /* cout << pat + 1 << endl; */
    for (int i = 1; i <= n; i++) {
        dp[i] = (((dp[i - 1] << 2) & (any_mask << 1)) | (dp[i - 1] << 1) | (dp[i - 1] & any_mask)) &
                char_mask[str[i] - 'a'];
        dp[i][0] = 1;
        /* cout<<i<<": ";prt(dp[i]); */
        if (dp[i][m]) {
            int j = i;
            for (; m; j--) {
                if (pat[m] == '*' && dp[j - 1][m])
                    ;
                else if (dp[j - 1][m - 1])
                    --m;
                else
                    m -= 2;
            }
            return {j + 1, i};
        }
        /* prt(char_mask[str[i]-'a']); */
        /* puts("---"); */
    }
    return {0, 0};
}
int main(int argc, char *argv[]) {
    /* freopen("test.in","r",stdin); */
    /* freopen("test.out","w",stdout); */
    scanf("%s", str + 1);
    n = strlen(str + 1);
    int t;
    scanf("%d", &t);
    dp[0][0] = 1;
    while (t--) {
        scanf("%s", pat + 1);
        init();
        auto res = cal();
        printf("%d %d\n", res.first, res.second);
    }

    return 0;
}
