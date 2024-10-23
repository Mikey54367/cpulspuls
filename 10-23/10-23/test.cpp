#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
//长度最小的子数组
int minSubArrayLen(int target, vector<int>& nums) {
    int minSubArrayLen = nums.size() + 1;
    int slow = 0, fast = 0;
    int sum = nums[slow];
    while (fast < nums.size())
    {
        if (sum >= target)
        {
            if (fast - slow + 1 < minSubArrayLen || minSubArrayLen == nums.size() + 1)
                minSubArrayLen = fast - slow + 1;
            if (minSubArrayLen == 1)
                return 1;
            sum -= nums[slow++];
            //更新
        }
        else
        {
            ++fast;
            if (fast != nums.size())
                sum += nums[fast];
        }
    }
    return minSubArrayLen == nums.size() + 1 ? 0 : minSubArrayLen;
}
//给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串的长度。
int lengthOfLongestSubstring(string s) {
    int ret = 0, left = 0, right = 0;
    unordered_set<char> us;
    while (right < s.size())
    {
        if (us.insert(s[right]).second)
        {
            //插入成功
            right++;
            ret = max(ret, right - left);
        }
        else
        {
            //插入失败  有重复元素
            us.erase(s[left]);
            left++;
        }
    }
    return ret;
}
//给定一个二进制数组 nums 和一个整数 k，如果可以翻转最多 k 个 0 ，则返回 数组中连续 1 的最大个数 。


int longestOnes(vector<int>& nums, int k) {
    int ret = 0, left = 0, right = 0, numOf0 = 0;
    while (right < nums.size())
    {
        if (nums[right] == 1)
        {
            ++right;
            ret = max(right - left, ret);
        }
        else
        {
            ++numOf0;
            while (numOf0 > k)
            {
                if (nums[left] == 0)
                {
                    numOf0--;
                }
                ++left;

            }

            if (left > right)
                right = left;
            else
                ++right;
            ret = max(right - left, ret);

        }
    }
    return ret;
}

int main()
{
    vector<int> v{ 8828,9581,49,9818,9974,9869,9991,10000,10000,10000,9999,9993,9904,8819,1231,6309 };
	return 0;
}