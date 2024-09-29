#include<iostream>
#include<map>
#include<algorithm>
#include<vector>
using namespace std;
//给定一个单词列表 words 和一个整数 k ，返回前 k 个出现次数最多的单词。
//
//返回的答案应该按单词出现频率由高到低排序。如果不同的单词有相同出现频率， 按字典顺序 排序。


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