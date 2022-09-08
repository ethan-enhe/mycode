#include <bits/stdc++.h>

#include <cstdio>
#include <iostream>
using namespace std;

long long ri(const long long &l, const long long &r) { return rand() % (r - l + 1) + l; }

string s, cho;
ifstream infile;

struct prob {
    string ask;
    char ans;
    int cnt;
    bool isfirst;
};

prob parse(string str) {
    prob ans;
    int ansind = -1;
    for (int i = 0; i < str.size(); i++) {
        if (cho == "1" && str[i] >= 'A' && str[i] <= 'Z' && i >= 1 && i < str.size() - 1 && str[i - 1] == '(' &&
            str[i + 1] == ')')
            ansind = i;
        if (cho == "2" && str[i] >= 'A' && str[i] <= 'Z' && str[i + 1] == '\n') ansind = i;
        if ((str[i] == '\n' || str[i] == '\r') && ansind != -1) break;
    }
    ans.ans = str[ansind];
    ans.ask = str.substr(0, ansind) + str.substr(ansind + 1);
    ans.cnt = 1;
    ans.isfirst = 1;
    return ans;
}
vector<prob> all;

void read_prob() {
    string tmp, str;
    while (getline(infile, tmp)) {
        if (tmp[0] == 'q') break;
        if (!tmp.empty() && isdigit(tmp[0])) {
            if (!str.empty()) all.push_back(parse(str));
            str = "";
        }
        str += tmp + "\n";
    }
    if (!str.empty()) all.push_back(parse(str));
}

int main() {
    system("chcp 65001");
    system("cls");
    srand(time(NULL));

    cout << "选择题库" << endl << "1-第二课堂" << endl << "2-校规校纪" << endl;

    cin >> cho;
    if (cho == "1")
        infile.open("2class.txt");
    else if (cho == "2")
        infile.open("rule.txt");

    read_prob();
    infile.close();

    int zhangwo = 0, zuoda = 0, zhengque = 0;
    while (all.size()) {
        system("cls");
        int ind = ri(0, all.size() - 1);
        cout << "剩余题目: " << all.size() << endl;
        cout << "已经掌握的题目：" << zhangwo << endl;
        if (zuoda) cout << "第一次作答的正确率 " << 100. * zhengque / zuoda << "%" << endl;
        cout << all[ind].ask;
        --all[ind].cnt;
        if (all[ind].isfirst) ++zuoda;
        bool f = all[ind].isfirst;
        all[ind].isfirst = 0;
        char ans = getchar();
        while (ans < 'A' || ans > 'Z') ans = getchar();
        if (ans == all[ind].ans) {
            zhengque += f;
            cout << "正确！" << endl;
            if (all[ind].cnt == 0) {
                ++zhangwo;
                all.erase(all.begin() + ind);
            }
        } else {
            cout << "错误，正确答案是: " << endl;
            cout << all[ind].ans << endl;
            all[ind].cnt = 2;
        }
        getchar();
        getchar();
    }
    cout << "Complete";
    getchar();

    return 0;
}
