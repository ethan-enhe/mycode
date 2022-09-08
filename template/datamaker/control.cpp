

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
    cout << "prob name:" << endl;
    cin >> prob;
    while (1) {
        int l, r;
        cout << "case rng:" << endl;
        cin >> l >> r;
        cin.getline(args, LS - 10);
        cout << "para:" << endl;
        cin.getline(args, LS - 10);
        for (int i = l; i <= r; i++) {
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
