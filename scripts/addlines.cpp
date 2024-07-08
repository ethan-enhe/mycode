#include <bits/stdc++.h>
using namespace std;

string remove_comments(string s) {
    // remove all c style comments from s
    string ans;
    int i = 0;
    while (i < s.length()) {
        if (s[i] == '"') {
            i++;
            ans += s[i];
            while (s[i] != '"') {
                i++;
                ans += s[i];
            }
            i++;
        } else if (s[i] == '\'') {
            i++;
            ans += s[i];
            while (s[i] != '\'') {
                i++;
                ans += s[i];
            }
            i++;
        } else if (s[i] == '/' && s[i + 1] == '/') {
            while (s[i] != '\n') {
                i++;
            }
            i++;
        } else if (s[i] == '/' && s[i + 1] == '*') {
            i += 2;
            while (s[i] != '*' || s[i + 1] != '/') {
                i++;
            }
            i += 2;
        } else {
            ans += s[i];
            i++;
        }
    }
    return s;
}
vector<string> random_lines;

string add_random_lines_as_comments(string s) {
    string ans;
    int n = random_lines.size();
    int i = 0;
    while (i < s.length()) {
        ans += s[i];
        if (s[i] == '"') {
            while (s[i] != '"') {
                i++;
                ans += s[i];
            }
            i++;
            continue;
        } else if (s[i] == '\'') {
            while (s[i] != '\'') {
                i++;
                ans += s[i];
            }
            i++;
            continue;
        }
        if (s[i] == ',' || s[i] == ';' || s[i] == '(' || s[i] == ')' || s[i] == '{' || s[i] == '}') {
            if (rand() % 4 == 0) {
                ans += "//" + random_lines[rand() % n] + '\n';
            }
        }
        i++;
    }
    return ans;
}

int main(int argc, char const *argv[]) {
    srand(time(0));
    string fn = argv[1];
    string s;
    ifstream fin(fn);
    // read the complete file to s at once
    string tmp;
    while (getline(fin, tmp)) {
        s += tmp;
        s += '\n';
    }
    fin.close();

    string fn_rnd_lines = "/home/ethan/Documents/mycode/scripts/random_lines.txt";
    ifstream fin_rnd_lines(fn_rnd_lines);
    while (getline(fin_rnd_lines, tmp)) {
        random_lines.push_back(tmp);
    }
    fin_rnd_lines.close();

    cout << add_random_lines_as_comments(remove_comments(s)) << endl;
    return 0;
}
