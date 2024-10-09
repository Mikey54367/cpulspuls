#include <iostream>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
//描述
//输入一个英文句子，把句子中的单词(不区分大小写)按出现次数按从多到少把单词和次数在屏幕上输出来，次数一样的按照单词小写的字典序排序输出，要求能识别英文单词和句号。
//输入描述：
//输入为一行，由若干个单词和句号组成
using namespace std;
class Compare {
public:
    bool operator()(const pair<string, int>& p1, const pair<string, int>& p2) {
        return p1.second > p2.second;
    }
};
int main() {
    map<string, int> m;
    int c;
    string s;
    while (c = getchar()) {
        if ('A' <= c && c <= 'Z')
        {
            c = c + 'a' - 'A';
        }
        if (c == '.')
        {
            m[s]++;
            s = "";
            break;
        }
        if (c == ' ') {
            m[s]++;
            s = "";
        }
        else {
            s.push_back(c);
        }
    }
    vector<pair<string, int>> v(m.begin(), m.end());
    Compare com;
    stable_sort(v.begin(), v.end(), com);
    auto it = v.begin();
    while (it != v.end())
    {
        cout << it->first << ":" << it->second << endl;
        ++it;
    }

    return 0;
}