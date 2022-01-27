#include "word.h"

#include <bits/stdc++.h>


using namespace std;
const int MXN = 10005;
int n;
char word[MXN][6], ask[6];

bool check(int id, bool *gold, bool *silver) {
    for (int i = 0; i < 5; i++) {
        if (gold[i] && ask[i] != word[id][i]) return 0;
        if (!gold[i] && ask[i] == word[id][i]) return 0;
        if (silver[i]) {
            bool f = 0;
            for (int j = 0; j < 5; j++)
                if (!gold[j] && ask[i] == word[id][j]) {
                    f = 1;
                    break;
                }
            if (!f) return 0;
        } else if (!gold[i]) {
            bool f = 0;
            for (int j = 0; j < 5; j++)
                if (!gold[j] && ask[i] == word[id][j]) {
                    f = 1;
                    break;
                }
            if (f) return 0;
        }
    }
    return 1;
}
bool possible[MXN], tg[6], ts[6];
/* double sum[6]; */

/* const char init_ask[26][6] = {"aahed", "baaed", "cabal", "daces", "eager", "fable", "gabby", "haafs", "iambi", */
/*                              "jabot", "kabab", "laari", "maars", "naans", "oaken", "pacas", "qadis", "rabat", */
/*                              "sabal", "tabby", "udder", "vacua", "wacke", "xebec", "yabby", "zaire"}; */
const char *guess(int num_testcase, int remaining_guesses, char initial_letter, bool *gold, bool *silver) {
    if (remaining_guesses == 5) {
        for (int i = 0; i < n; i++) possible[i] = (word[i][0] == initial_letter);
    } else {
        for (int i = 0; i < n; i++)
            if (possible[i]) possible[i] = check(i, gold, silver);
    }
    vector<int> pos;
    for (int i = 0; i < n; i++)
        if (possible[i]) pos.push_back(i);
    /* sum[5 - remaining_guesses] += pos.size(); */
    assert(pos.size());
    int x = rand() % pos.size();
    for (int j = 0; j < 5; j++) ask[j] = word[pos[x]][j];

    return ask; // sample: always guess "paper"
}
void init(int num_scramble, const char *scramble) {
    for (int i = 0; i < num_scramble; i++)
        for (int j = 0; j < 5; j++) {
            word[i][j] = scramble[i * 5 + j];
        }
    n = num_scramble;
}
