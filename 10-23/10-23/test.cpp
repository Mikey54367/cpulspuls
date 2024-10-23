#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
//������С��������
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
            //����
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
//����һ���ַ��� s �������ҳ����в������ظ��ַ��� � �Ӵ��ĳ��ȡ�
int lengthOfLongestSubstring(string s) {
    int ret = 0, left = 0, right = 0;
    unordered_set<char> us;
    while (right < s.size())
    {
        if (us.insert(s[right]).second)
        {
            //����ɹ�
            right++;
            ret = max(ret, right - left);
        }
        else
        {
            //����ʧ��  ���ظ�Ԫ��
            us.erase(s[left]);
            left++;
        }
    }
    return ret;
}
//����һ������������ nums ��һ������ k��������Է�ת��� k �� 0 ���򷵻� ���������� 1 �������� ��


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