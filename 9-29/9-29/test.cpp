#include<iostream>
#include<map>
#include<algorithm>
#include<vector>
using namespace std;
//����һ�������б� words ��һ������ k ������ǰ k �����ִ������ĵ��ʡ�
//
//���صĴ�Ӧ�ð����ʳ���Ƶ���ɸߵ������������ͬ�ĵ�������ͬ����Ƶ�ʣ� ���ֵ�˳�� ����


struct Compare
{
    bool operator()(const pair<string, int>& p1, const pair<string, int>& p2)
    {
        return p1.second > p2.second;
    }
};
vector<string> topKFrequent(vector<string>& words, int k) {
    vector<string> ret;
    map<string, int> m;
    for (auto e : words)
    {
        m[e]++;
    }
    vector<pair<string, int>> v(m.begin(), m.end());

    stable_sort(v.begin(), v.end(), Compare());
    auto it = v.begin();
    while (k--)
    {
        ret.push_back(it->first);
        ++it;
    }
    return ret;
}
int main()
{
    vector<string> words = { "i", "love", "leetcode", "i", "love", "coding" };
    topKFrequent(words, 2);
    return 0;
}