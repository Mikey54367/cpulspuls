#include<iostream>
#include<vector>
using namespace std;
//����һ������ nums����дһ������������ 0 �ƶ��������ĩβ��ͬʱ���ַ���Ԫ�ص����˳��
//
//��ע�� �������ڲ���������������ԭ�ض�������в�����
//
//
//
//ʾ�� 1:
//
//����: nums = [0, 1, 0, 3, 12]
//��� : [1, 3, 12, 0, 0]
//ʾ�� 2 :
//
//    ���� : nums = [0]
//    ��� : [0]

void moveZeroes(vector<int>& nums) {
    int cur = 0;
    int dest = 0;
    //
    while (dest < nums.size())
    {
        while (dest < nums.size() && nums[dest] == 0)
        {
            dest++;
        }
        if (dest < nums.size())
            swap(nums[dest], nums[cur]);
        cur++;;
        dest++;
    }
}

int main()
{
    vector<int> v = { 1,0,2,3,0,4,5,0 };
    moveZeroes(v);
	return 0;
}