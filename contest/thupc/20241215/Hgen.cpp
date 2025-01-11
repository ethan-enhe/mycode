#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

const int MAX_N = 1000;
const int MAX_Q = 1000;
const int MAX_A = 998244352;
const int MAX_C = 250000;

int main() {
    srand(clock());

    ofstream outfile("test.in");

    int n = rand() % MAX_N + 1;
    int q = rand() % MAX_Q + 1;

    outfile << n << " " << q << endl;

    for (int i = 0; i < n; ++i) {
        outfile << rand() % MAX_A + 1 << " ";
    }
    outfile << endl;

    for (int i = 0; i < q; ++i) {
        int op = rand() % 2 + 1;
        outfile << op << " ";
        if (op == 1) {
            int l = rand() % n + 1;
            int r = rand() % (n - l + 1) + l;
            int c = rand() % (MAX_C - 1) + 2;
            outfile << l << " " << r << " " << c << endl;
        } else {
            int x = rand() % n + 1;
            outfile << x << endl;
        }
    }

    outfile.close();
    return 0;
}
