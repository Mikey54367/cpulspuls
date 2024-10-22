#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//四数之和
vector<vector<int>> fourSum(vector<int>& nums, int target) {

    sort(nums.begin(), nums.end());
    vector<vector<int>> vv;
    if (nums.size() <= 3)
    {
        return vv;
    }
    for (int i = 0; i < nums.size() - 3; ++i)
    {
        if (i && nums[i] == nums[i - 1])
            continue;
        for (int j = i + 1; j < nums.size() - 2; ++j)
        {
            if (j != i + 1 && nums[j] == nums[j - 1])
                continue;
            int left = j + 1, right = nums.size() - 1;
            while (left < right)
            {
                if ((long long)nums[i] + nums[j] + nums[left] + nums[right] > (long long)target)
                {
                    right--;
                    while (left < right && nums[right] == nums[right + 1])
                        right--;
                }
                else if ((long long)nums[i] + nums[j] + nums[left] + nums[right] < (long long)target)
                {
                    left++;
                    while (left < right && nums[left] == nums[left - 1])
                        left++;
                }
                else
                {
                    vv.push_back({ nums[i],nums[j],nums[left],nums[right] });
                    left++;
                    while (left < right && nums[left] == nums[left - 1])
                        left++;
                }
            }
        }
    }
    return vv;
}
//三数之和
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> vv;
    int i = 0;
    while (i < nums.size() - 2)
    {
        int left = i + 1, right = nums.size() - 1;
        if (nums[i] > 0)
            break;
        while (left < right)
        {
            if (nums[i] + nums[left] + nums[right] > 0)
            {
                --right;
                while (left < right && nums[right] == nums[right + 1])
                    --right;
            }
            else if (nums[i] + nums[left] + nums[right] < 0)
            {
                ++left;
                while (left < right && nums[left] == nums[left - 1])
                    ++left;
            }
            else
            {
                vv.push_back({ nums[i],nums[left],nums[right] });
                ++left;
                while (left < right && nums[left] == nums[left - 1])
                    ++left;
            }
        }
        ++i;
        while (i < nums.size() - 2 && nums[i] == nums[i - 1])
            ++i;
    }
    return vv;
}
//有效的三角形个数
int triangleNumber(vector<int>& nums) {
    int triangleNumber = 0;
    sort(nums.begin(), nums.end());
    int i = nums.size() - 1;
    while (i >= 2)
    {
        int left = 0, right = i - 1;
        while (left < right)
        {
            if (nums[left] + nums[right] > nums[i])
            {
                triangleNumber += right - left;
                --right;
            }
            else
            {
                left++;
            }
        }
        --i;
    }
    return triangleNumber;
}
int main()
{
    vector<int> v{ 0 };
    fourSum(v, 0);
	return 0;
}