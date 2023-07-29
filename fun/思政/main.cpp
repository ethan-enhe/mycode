#include <bits/stdc++.h>

#include <fstream>

using namespace std;
vector<string> split_on_tab(string s) {
    vector<string> res;
    string last;
    int ind = 0;
    for (; ind < (int)s.size(); ind++) {
        if (s[ind] & 0xFF00) {
            last.push_back(s[ind++]);
            last.push_back(s[ind++]);
            last.push_back(s[ind]);
        } else if (s[ind] == '\t' || s[ind] == ' ') {
            if (!last.empty()) res.push_back(last);
            last = "";
        } else
            last.push_back(s[ind]);
    }
    if (!last.empty()) res.push_back(last);
    return res;
}
string standardans(string ans) {
    for (auto &i : ans)
        if (i >= 'A' && i <= 'Z') i = i - 'A' + 'a';
    sort(ans.begin(), ans.end());
    return ans;
}
struct prob {
    string full;
    string chapt, type, que, ans;
    vector<string> choice;
    int correctafter; // 几轮之后正确
    prob(string s) {
        full = s;
        correctafter = 0;
        vector<string> res = split_on_tab(s);
        // for (auto &i : res) cout << ":" << i << ":" << endl;
        chapt = res[0];
        type = res[1];
        que = res[2];
        if (isdigit(res[4][0])) {
            ans = res[5];
        } else {
            choice.resize(atoi(res[5].c_str()));
            ans = standardans(res[3]);
            for (int i = 0; i < (int)choice.size(); i++) choice[i] = res[6 + i];
        }
        // assert(0);
    }
};
vector<prob> done, notdone;
mt19937 rnd(time(0));
void finish() {
    system("clear");
    while (1) {
        cout << "输出轮数大于等于几轮的题目？" << endl;
        int x;
        cin >> x;
        for (auto i : notdone) cout << i.full << endl;
        for (auto i : done)
            if (i.correctafter >= x) cout << i.full << endl;
    }
    exit(0);
}
int main() {
    string fn;
    cout << "输入文件名：";
    cin >> fn;
    ifstream fin(fn);
    int cnt=0;
    while (1) {
        string tmp;
        getline(fin, tmp);
        if (tmp[0] == 'q') break;
        prob p(tmp);
        notdone.push_back(p);
        cout<<++cnt<<endl;
    }
    fin.close();
    int round = 0;
    while (!notdone.empty()) {
        ++round;
        shuffle(notdone.begin(), notdone.end(), rnd);

        for (int i = 0, cor = 0; i < (int)notdone.size(); i++) {
            system("clear");
            cout << "第" << round << "轮" << endl;
            cout << "[" << notdone[i].type << "]" << endl;
            cout << notdone[i].que << endl;
            char tmp = 'A';
            for (auto &j : notdone[i].choice) cout << (tmp++) << ". " << j << endl;
            cout << "输入答案：" << endl;
            string res;
            if (!notdone[i].ans.empty()) {
                cin >> res;
            }
            if (res == "z") {
                finish();
            } else if (res == notdone[i].ans || standardans(res) == notdone[i].ans) {
                ++cor;
                notdone[i].correctafter = round;
                cout << "正确！" << endl;
            } else {
                cout << "错误的！\n正确答案：" << notdone[i].ans << endl;
            }
            cout << endl << "此轮正确：" << cor << "/" << i + 1 << endl << endl;
            getchar();
            getchar();
        }
        int ind = 0;
        while (ind < (int)notdone.size()) {
            if (notdone[ind].correctafter) {
                done.push_back(notdone[ind]);
                notdone.erase(notdone.begin() + ind);
            } else
                ++ind;
        }
    }
    finish();
    return 0;
}
