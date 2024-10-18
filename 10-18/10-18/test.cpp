#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//复写0
//给你一个长度固定的整数数组 arr ，请你将该数组中出现的每个零都复写一遍，并将其余的元素向右平移。
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
//编写一个算法来判断一个数 n 是不是快乐数。
//
//「快乐数」 定义为：
//
//对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
//然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
//如果这个过程 结果为 1，那么这个数就是快乐数。
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
//给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是(i, 0) 和(i, height[i]) 。
//
//找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
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