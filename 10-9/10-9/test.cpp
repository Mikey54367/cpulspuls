#include <iostream>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
//����
//����һ��Ӣ�ľ��ӣ��Ѿ����еĵ���(�����ִ�Сд)�����ִ������Ӷൽ�ٰѵ��ʺʹ�������Ļ�������������һ���İ��յ���Сд���ֵ������������Ҫ����ʶ��Ӣ�ĵ��ʺ;�š�
//����������
//����Ϊһ�У������ɸ����ʺ;�����
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