#include <bits/stdc++.h>

#include <cstdio>

using namespace std;
const int MXN = 105;
const int MXK = 20;
struct cmd {
    int tp, h, x, y, z;
    cmd *quote;
};
cmd arr[MXN][MXK];
int n, m, k, h[MXN][2];
void exec(int botid, cmd c, bool is_trig);
void try_trig(int botid, cmd pre_c, bool is_trig) {
    for (int i = 1; i <= m; i++)
        if (arr[botid][i].tp == 6) {
            if (arr[botid][i].x != 6 && arr[botid][i].x == pre_c.tp) {
                exec(botid, *arr[botid][i].quote, 1);
                return;
            }
            if (arr[botid][i].x == 6 && is_trig) {
                exec(botid, *arr[botid][i].quote, 1);
                return;
            }
        }
}
void activ(int botid, bool is_trig) {
    cerr<<botid<<endl;
    for (int i = 1; i <= m; i++) exec(botid, arr[botid][i], is_trig);
}
void exec(int botid, cmd c, bool is_trig) {
    if (!k) exit(0);
    if (c.tp == 0) {
        cout << "Robot " << botid << " slacks off." << endl;
    } else if (c.tp == 1) {
        h[botid][c.h] = (h[botid][c.h] + c.z) % n;
        cout << "Robot " << botid << " moves its " << (c.h ? "right" : "left") << " hand towards Robot "
             << h[botid][c.h] << "." << endl;
    } else if (c.tp == 2) {
        swap(arr[h[botid][c.h]][c.x], arr[botid][c.y]);
        cout << "Robot " << botid << " swaps a line of command with Robot " << h[botid][c.h] << "." << endl;
    } else if (c.tp == 3) {
        arr[h[botid][c.h]][c.x].h ^= 1;
        cout << "Robot " << botid << " modifies a line of command of Robot " << h[botid][c.h] << "." << endl;
    } else if (c.tp == 4) {
        arr[h[botid][c.h]][c.x] = *c.quote;
        cout << "Robot " << botid << " replaces a line of command of Robot " << h[botid][c.h] << "." << endl;
    } else if (c.tp == 5) {
        cout << "Robot " << botid << " activates Robot " << h[botid][c.h] << "." << endl;
        activ(h[botid][c.h], is_trig);
    } else if (c.tp == 6) {
        return;
    }
    else {
        assert(0);
    }
    --k;
    if (h[botid][1] != botid) try_trig(h[botid][1], c, is_trig);
    // cerr << k << endl;
}
int cmd_type(string s) {
    if (s == "SLACKOFF") {
        return 0;
    } else if (s == "MOVE") {
        return 1;
    } else if (s == "SWAP") {
        return 2;
    } else if (s == "MIRROR") {
        return 3;
    } else if (s == "REPLACE") {
        return 4;
    } else if (s == "ACTIVATE") {
        return 5;
    } else if (s == "TRIGGER") {
        return 6;
    }
    return -1;
}
void readcmd(cmd *x) {
    string s;
    cin >> s;
    x->tp = cmd_type(s);
    if (s == "SLACKOFF") {
    } else if (s == "MOVE") {
        cin >> x->h >> x->z;
    } else if (s == "SWAP") {
        cin >> x->h >> x->x >> x->y;
    } else if (s == "MIRROR") {
        cin >> x->h >> x->x;
    } else if (s == "REPLACE") {
        cin >> x->h >> x->x;
        x->quote = new cmd;
        readcmd(x->quote);
    } else if (s == "ACTIVATE") {
        cin >> x->h;
    } else if (s == "TRIGGER") {
        string tmp;
        cin >> tmp;
        tmp = tmp.substr(0, tmp.size() - 1);
        x->x = cmd_type(tmp);
        x->quote = new cmd;
        readcmd(x->quote);
    }
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> h[i][0] >> h[i][1];
        for (int j = 1; j <= m; j++) readcmd(&arr[i][j]);
    }
    // cout<<arr[1][1].quote->h;
    int i = 0;
    while (1) {
        activ(i, 0);
        i = (i + 1) % n;
        // cerr << k << " " << i << endl;
    }
    return 0;
}
