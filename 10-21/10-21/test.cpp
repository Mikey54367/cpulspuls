#include<iostream>
#include<vector>
using namespace std;
//两数之和
vector<int> twoSum(vector<int>& price, int target) {
    int left = 0, right = price.size() - 1;
    while (left < right)
    {
        if (price[left] + price[right] > target)
            right--;
        else if (price[left] + price[right] < target)
            left++;
        else
            return{ price[left],price[right] };
    }
    return { 1,1 };
}
int main()
{
	return 0;
}