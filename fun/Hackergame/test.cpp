#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

double rand01() { return (double)rand() / RAND_MAX; }

int main() {
    // disable buffering
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    srand((unsigned)time(0) + clock());
    int games = 5;
    int win = 0;
    int lose = 0;
    char target[20];
    char guess[2000];
    char guess1[2000];

    int t0 = time(0);
    cerr << t0 << endl;
    cerr << clock() << endl;
    cerr << CLOCKS_PER_SEC << endl;

    printf("请输入你的猜测（如 3.14159，输入后回车）：");
    fgets(guess, 2000, stdin);
    guess[7] = '\0';
    printf("请输入你的猜测（如 3.14159，输入后回车）：");
    fgets(guess1, 2000, stdin);
    guess1[7] = '\0';
    for (int i = 0; i <= 2e4; i++) {
        if (i % 1000 == 0) cerr << i << endl;
        {
            srand(t0 + i);
            int M = 0;
            int N = 400000;
            for (int j = 0; j < N; j++) {
                double x = rand01();
                double y = rand01();
                if (x * x + y * y < 1) M++;
            }
            double pi = (double)M / N * 4;
            sprintf(target, "%1.5f", pi);
            if (strcmp(target, guess) == 0) {
                int M = 0;
                int N = 400000;
                for (int j = 0; j < N; j++) {
                    double x = rand01();
                    double y = rand01();
                    if (x * x + y * y < 1) M++;
                }
                double pi = (double)M / N * 4;
                sprintf(target, "%1.5f", pi);
                if (strcmp(target, guess1) == 0) cout << i << " " << t0 + i << endl;
            }
        }
        {
            srand(t0 - i);
            int M = 0;
            int N = 400000;
            for (int j = 0; j < N; j++) {
                double x = rand01();
                double y = rand01();
                if (x * x + y * y < 1) M++;
            }
            double pi = (double)M / N * 4;
            sprintf(target, "%1.5f", pi);
            if (strcmp(target, guess) == 0) {
                int M = 0;
                int N = 400000;
                for (int j = 0; j < N; j++) {
                    double x = rand01();
                    double y = rand01();
                    if (x * x + y * y < 1) M++;
                }
                double pi = (double)M / N * 4;
                sprintf(target, "%1.5f", pi);
                if (strcmp(target, guess1) == 0) cout << i << " " << t0 - i << endl;
            }
        }
    }
    return 0;
}
