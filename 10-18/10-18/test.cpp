#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//��д0
//����һ�����ȹ̶����������� arr �����㽫�������г��ֵ�ÿ���㶼��дһ�飬���������Ԫ������ƽ�ơ�
void duplicateZeros(vector<int>& arr) {
    int dest = -1, cur = 0;
    while (true)
    {
        if (arr[cur] == 0)
        {
            dest++;
            dest++;
        }
        else
        {
            dest++;
        }
        if (dest >= arr.size() - 1)
            break;
        cur++;
    }
    if (dest == arr.size())
    {
        dest--;
        arr[dest--] = 0;
        cur--;
    }
    while (cur >= 0)
    {
        if (arr[cur] == 0)
        {
            arr[dest--] = 0;
            arr[dest--] = 0;
        }
        else
        {
            arr[dest--] = arr[cur];
        }
        --cur;
    }
}
//��дһ���㷨���ж�һ���� n �ǲ��ǿ�������
//
//���������� ����Ϊ��
//
//����һ����������ÿһ�ν������滻Ϊ��ÿ��λ���ϵ����ֵ�ƽ���͡�
//Ȼ���ظ��������ֱ���������Ϊ 1��Ҳ������ ����ѭ�� ��ʼ�ձ䲻�� 1��
//���������� ���Ϊ 1����ô��������ǿ�������
int next(int n)
{
    int ret = 0;
    while (n)
    {
        ret += (n % 10) * (n % 10);
        n /= 10;
    }
    return ret;
}
bool isHappy(int n) {
    int slow = next(n);
    int fast = next(slow);
    while (fast != slow)
    {
        fast = next(next(fast));
        slow = next(slow);
    }
    if (slow == 1)
        return true;
    return false;
}
//����һ������Ϊ n ���������� height ���� n �����ߣ��� i ���ߵ������˵���(i, 0) ��(i, height[i]) ��
//
//�ҳ����е������ߣ�ʹ�������� x �Ṳͬ���ɵ�����������������ˮ��
int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int max = 0;
    while (left < right)
    {
        int area = 0;
        if (height[left] > height[right])
        {
            area = height[right] * (right - left);
            if (max < area)
                max = area;
            right--;
        }
        else
        {
            area = height[left] * (right - left);
            if (max < area)
                max = area;
            left++;
        }
    }
    return max;
}

int main()
{
    vector<int> v = { 1 };
    return 0;
}