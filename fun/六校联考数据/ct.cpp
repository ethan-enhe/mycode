
#include <cstdio>
#include <iostream>
using namespace std;
const int LS = 10000;
char gen[LS], cal[LS];
char prob[LS], args[LS];
int main() {
    system("g++ gen.cpp -o gen -lm");
    system("g++ std.cpp -o std -lm");
    int ind = 0;
    cin >> prob;
    while (1) {
        int len;
        cin >> len;
        cin.getline(args, LS - 10);
        cin.getline(args, LS - 10);
        for (int i = 1; i <= len; i++) {
            ind++;
            cout << "gen" << ind << endl;
            sprintf(gen, "./gen %s > %s%d.in", args, prob, ind);
            sprintf(cal, "./std < %s%d.in > %s%d.out", prob, ind, prob, ind);
            system(gen);
            system(cal);
        }
    }
    return 0;
}
