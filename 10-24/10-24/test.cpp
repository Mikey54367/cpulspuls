#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
//将x减到0的最小操作数
int minOperations(vector<int>& nums, int x) {
    int target = 0;
    for (auto& e : nums)
    {
        target += e;
    }
    target -= x;
    if (target < 0)
        return -1;
    int left = 0, right = 0;
    int sum = 0;
    int rRet = -1;
    while (right < nums.size())
    {
        if (sum < target)
            sum += nums[right++];
        else if (sum > target)
        {
            sum -= nums[left++];
        }
        else
        {
            rRet = max(rRet, right - left);
            if (rRet == 0)
                return nums.size();
            sum -= nums[left++];
        }
    }
    while (left < nums.size())
    {
        if (sum > target)
            sum -= nums[left++];
        else if (sum == target)
        {
            rRet = max(rRet, right - left);
            break;
        }
        else
            break;
    }

    return rRet == -1 ? -1 : nums.size() - rRet;
}
//水果成篮
int totalFruit(vector<int>& fruits) {
    int ret = 0, left = 0, right = 0;
    unordered_map<int, int> um;
    while (right < fruits.size())
    {
        if (um.size() <= 2)
        {
            um[fruits[right]]++;
        }

        while (um.size() > 2)
        {
            ret = max(ret, right - left);
            if (um[fruits[left]] > 1)
            {
                um[fruits[left]]--;
            }
            else
            {
                um.erase(fruits[left]);
            }
            left++;
        }
        right++;
    }
    if (um.size() <= 2)
        ret = max(ret, right - left);
    return ret;
}
int main()
{
    vector<int> v{ 3,3,3,1,2,1,1,2,3,3,4 };
    totalFruit(v);
	return 0;
}